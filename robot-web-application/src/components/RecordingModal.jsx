import React, { useState, useRef, useEffect } from "react";
import { Icon } from "@iconify/react/dist/iconify.js";

export default function RecordingModal({ open, onClose }) {
  const [isRecording, setIsRecording] = useState(false);
  const [audioURL, setAudioURL] = useState(null);
  const [recordingTime, setRecordingTime] = useState(0);
  const [isListening, setIsListening] = useState(false);
  const [transcription, setTranscription] = useState("");
  const [response, setResponse] = useState("");
  const [isTranscribing, setIsTranscribing] = useState(false);
  const mediaRecorderRef = useRef(null);
  const audioChunksRef = useRef([]);
  const timerRef = useRef(null);

  useEffect(() => {
    return () => {
      if (timerRef.current) clearInterval(timerRef.current);
    };
  }, []);

  const startRecording = async () => {
    try {
      const stream = await navigator.mediaDevices.getUserMedia({ audio: true });
      mediaRecorderRef.current = new MediaRecorder(stream);

      mediaRecorderRef.current.ondataavailable = (event) => {
        if (event.data.size > 0) {
          audioChunksRef.current.push(event.data);
        }
      };

      mediaRecorderRef.current.onstop = () => {
        const audioBlob = new Blob(audioChunksRef.current, {
          type: "audio/wav",
        });
        const audioUrl = URL.createObjectURL(audioBlob);
        setAudioURL(audioUrl);
        audioChunksRef.current = [];
      };

      mediaRecorderRef.current.start();
      setIsRecording(true);
      setRecordingTime(0);
      timerRef.current = setInterval(() => {
        setRecordingTime((prevTime) => prevTime + 1);
      }, 1000);
    } catch (error) {
      console.error("Error accessing the microphone", error);
    }
  };

  const stopRecording = () => {
    if (mediaRecorderRef.current && isRecording) {
      mediaRecorderRef.current.stop();
      setIsRecording(false);
      if (timerRef.current) clearInterval(timerRef.current);
    }
  };

  const cancelRecording = () => {
    setAudioURL(null);
    setRecordingTime(0);
    setTranscription("");
  };

  const formatTime = (seconds) => {
    const mins = Math.floor(seconds / 60);
    const secs = seconds % 60;
    return `${mins.toString().padStart(2, "0")}:${secs
      .toString()
      .padStart(2, "0")}`;
  };

  const transcribeAudio = () => {
    if (!audioURL) {
      console.error("No audio available for transcription");
      return;
    }

    setIsTranscribing(true);

    const audioElement = new Audio(audioURL);
    const recognition = new (window.SpeechRecognition ||
      window.webkitSpeechRecognition)();
    recognition.lang = "en-US";
    recognition.interimResults = false;
    recognition.maxAlternatives = 1;

    recognition.onresult = (event) => {
      const transcript = event.results[0][0].transcript;
      setTranscription(transcript);
      setIsTranscribing(false);
      getIntent(transcript);
    };

    recognition.onerror = (event) => {
      console.error("Speech recognition error", event.error);
      setIsTranscribing(false);
    };

    recognition.onend = () => {
      audioElement.pause();
      setIsTranscribing(false);
    };

    audioElement.onended = () => {
      recognition.stop();
    };

    recognition.start();
    audioElement.play();
  };

  const getIntent = async (transcript) => {
    try {
      const response = await fetch(
        "https://api.groq.com/openai/v1/chat/completions",
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer <token>`,
          },
          body: JSON.stringify({
            messages: [
              {
                role: "system",
                content: `
You are a fumigation robot, with the ability to converse, deployed in hospital wards. This means you would be interacting with patients, doctors, nurses and other hospital personnel.
You are required to respond to requests by each of the these entities.
You are to first try and decipher based on the request which entity is requesting.
You are to output your response in form of JSON.

Here are example requests and their corresponding responses:

Request: "i feel like vomiting",

Response:
{
    "entity": "patient",
    "message": "Okay. I would get someone to help you.",
    "action": "contact_personnel"
}

--------------------------------------------------------------

Request: "i am feeling feverish",

Response:
{
    "entity": "patient",
    "message": "Please stand still while I take your temperature.",
    "action": "measure_temperature"
}

--------------------------------------------------------------

Request: "excuse me i am having trouble taking my drugs"

Response:
{
    "entity": "patient",
    "message": "Someone will soon be here to help you.",
    "action": "contact_personnel"
}

--------------------------------------------------------------

Request: "i feel like vomiting"

Response:

{
    "entity": "patient",
    "message": "Okay. I would get someone to help you."
    "action": "contact_personnel"
}

--------------------------------------------------------------

Request: "i am scared about the surgery"

Response:
{
    "entity": "patient",
    "message": "I understand, it's normal to feel anxious. It is a standard procedure and know that you are in the hands of capable doctors.",
    "action": ""
}
`,
              },
              {
                role: "user",
                content: JSON.stringify(transcript),
              },
            ],
            model: "llama3-8b-8192",
          }),
        }
      );
      const data = await response.json();
      setResponse(data.choices[0].message.content);
    } catch (error) {
      console.error.apply("Error: ", error);
    }
  };

  return (
    <div
      onClick={onClose}
      className={`fixed inset-0 flex justify-center items-center transition-colors ${
        open ? "visible bg-black/20" : "invisible"
      }`}
    >
      <div
        onClick={(e) => e.stopPropagation()}
        className={`
          bg-white rounded-xl shadow p-6 transition-all w-96
          ${open ? "scale-100 opacity-100" : "scale-125 opacity-0"}
        `}
      >
        <button
          onClick={onClose}
          className="absolute top-2 right-2 p-1 rounded-lg text-gray-400 bg-white hover:bg-gray-50 hover:text-gray-600"
        >
          <Icon icon="solar:close-square-bold-duotone" />
        </button>
        <Icon icon="solar:microphone-outline" color="black" fontSize={20} />
        <div className="mt-4 space-y-4">
          {isRecording ? (
            <div className="flex items-center space-x-2">
              <div className="w-3 h-3 bg-red-500 rounded-full animate-pulse"></div>
              <span className="text-red-500 font-medium">
                Recording: {formatTime(recordingTime)}
              </span>
            </div>
          ) : audioURL ? (
            <div className="flex items-center justify-between">
              <span className="font-medium">Recording complete</span>
              <span>{formatTime(recordingTime)}</span>
            </div>
          ) : null}

          {!audioURL ? (
            <button
              onClick={isRecording ? stopRecording : startRecording}
              className={`w-full px-4 py-2 rounded-lg ${
                isRecording
                  ? "bg-red-500 hover:bg-red-600 text-white"
                  : "bg-blue-500 hover:bg-blue-600 text-white"
              }`}
            >
              {isRecording ? "Stop Recording" : "Start Recording"}
            </button>
          ) : (
            <div className="space-y-2">
              <audio
                src={audioURL}
                controls
                className="w-full"
                onPlay={() => setIsListening(true)}
                onPause={() => setIsListening(false)}
                onEnded={() => setIsListening(false)}
              />
              <div className="flex space-x-2">
                <button
                  onClick={cancelRecording}
                  className="flex-1 px-4 py-2 bg-gray-200 hover:bg-gray-300 rounded-lg"
                  disabled={isListening || isTranscribing}
                >
                  Re-record
                </button>
                <button
                  onClick={transcribeAudio}
                  className="flex-1 px-4 py-2 bg-green-500 hover:bg-green-600 text-white rounded-lg"
                  disabled={isListening || isTranscribing}
                >
                  {isTranscribing ? "Transcribing..." : "Transcribe"}
                </button>
              </div>
            </div>
          )}

          {transcription && (
            <div className="mt-4">
              <h3 className="font-medium mb-2">Transcription:</h3>
              <p className="text-sm bg-gray-100 p-2 rounded">{transcription}</p>
            </div>
          )}

          {response && (
            <div className="mt-4">
              <h3 className="font-medium mb-2">Response:</h3>
              <p className="text-sm bg-gray-100 p-2 rounded">{response}</p>
            </div>
          )}
        </div>
      </div>
    </div>
  );
}
