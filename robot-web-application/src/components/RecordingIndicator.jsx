import React from "react";

export default function RecordingIndicator({ isRecording, recordingTime }) {
  const formatTime = (seconds) => {
    const mins = Math.floor(seconds / 60);
    const secs = seconds % 60;
    return `${mins.toString().padStart(2, "0")}:${secs
      .toString()
      .padStart(2, "0")}`;
  };

  return isRecording ? (
    <div className="flex items-center space-x-2">
      <div className="w-3 h-3 bg-red-500 rounded-full animate-pulse"></div>
      <span className="text-red-500 font-medium">
        Recording: {formatTime(recordingTime)}
      </span>
    </div>
  ) : null;
}
