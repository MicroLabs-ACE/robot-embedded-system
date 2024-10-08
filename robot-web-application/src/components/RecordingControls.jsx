import React from "react";

export default function RecordingControls({
  isRecording,
  startRecording,
  stopRecording,
  cancelRecording,
  isTranscribing,
}) {
  return (
    <div>
      {isRecording ? (
        <button
          onClick={stopRecording}
          className="w-full px-4 py-2 rounded-lg bg-red-500 hover:bg-red-600 text-white"
        >
          Stop Recording
        </button>
      ) : (
        <button
          onClick={startRecording}
          className="w-full px-4 py-2 rounded-lg bg-blue-500 hover:bg-blue-600 text-white"
        >
          Start Recording
        </button>
      )}
      {isRecording && (
        <button
          onClick={cancelRecording}
          className="mt-2 w-full px-4 py-2 rounded-lg bg-gray-200 hover:bg-gray-300"
          disabled={isTranscribing}
        >
          Cancel Recording
        </button>
      )}
    </div>
  );
}
