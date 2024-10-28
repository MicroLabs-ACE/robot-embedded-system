export const sendCommand = async (northSouth, eastWest) => {
  const IP_ADDRESS = "http://192.168.4.1/";
  const command = `${northSouth}${eastWest}2`;
  try {
    const response = await fetch(
      `${IP_ADDRESS}?command=${encodeURIComponent(command)}`,
      {
        method: "POST",
      }
    );

    console.log("Response:", response);
    if (response.ok) {
      console.log(`Sent command: ${command}`);
    } else {
      console.error("Failed to send command.");
    }
  } catch (error) {
    console.error("Error sending command:", error);
  }
};
