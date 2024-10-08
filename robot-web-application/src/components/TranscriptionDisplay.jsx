import React from "react";

export default function TranscriptionDisplay({ transcription }) {
  return (
    <div className="mt-4">
      <h3 className="font-medium mb-2">Transcription:</h3>
      <p className="text-sm bg-gray-100 p-2 rounded">{transcription}</p>
    </div>
  );
}
