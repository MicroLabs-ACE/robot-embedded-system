import React, { useState, useRef, useEffect } from "react";
import { Icon } from "@iconify/react/dist/iconify.js";
import ModalWrapper from "./ModalWrapper";
import RecordingControls from "./RecordingControls";
import AudioPlayer from "./AudioPlayer";
import TranscriptionDisplay from "./TranscriptionDisplay";
import ResponseDisplay from "./ResponseDisplay";
import RecordingIndicator from "./RecordingIndicator";
import { getIntent } from "../utils/getIntent";

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
    setResponse("");
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

  return (
    <ModalWrapper open={open} onClose={onClose}>
      <div className="relative">
        <Icon icon="solar:microphone-outline" color="black" fontSize={20} />
        <div className="mt-4 space-y-4">
          <RecordingIndicator
            isRecording={isRecording}
            recordingTime={recordingTime}
          />

          {!audioURL ? (
            <RecordingControls
              isRecording={isRecording}
              startRecording={startRecording}
              stopRecording={stopRecording}
              cancelRecording={cancelRecording}
              isTranscribing={isTranscribing}
            />
          ) : (
            <div className="space-y-2">
              <AudioPlayer
                audioURL={audioURL}
                isListening={isListening}
                setIsListening={setIsListening}
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
            <TranscriptionDisplay transcription={transcription} />
          )}

          {response && <ResponseDisplay response={response} />}
        </div>
      </div>
    </ModalWrapper>
  );
}
