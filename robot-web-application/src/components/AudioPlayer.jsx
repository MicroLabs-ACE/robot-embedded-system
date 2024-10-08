import React from "react";

export default function AudioPlayer({ audioURL, isListening, setIsListening }) {
  return (
    <audio
      src={audioURL}
      controls
      className="w-full"
      onPlay={() => setIsListening(true)}
      onPause={() => setIsListening(false)}
      onEnded={() => setIsListening(false)}
    />
  );
}
