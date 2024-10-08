import React from "react";

export default function ResponseDisplay({ response }) {
  return (
    <div className="mt-4">
      <h3 className="font-medium mb-2">Response:</h3>
      <p className="text-sm bg-gray-100 p-2 rounded">{response}</p>
    </div>
  );
}
