#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600); // Initialize hardware serial for debugging
  mySerial.begin(9600); // Initialize software serial for communication with the sender
}

void loop() {
  if (mySerial.available()) { // Check if data is available to read
    String receivedData = mySerial.readString(); // Read the incoming data into a String
    Serial.print("Received: ");
    Serial.println(receivedData); // Print the received data
  }
  delay(100);
}


