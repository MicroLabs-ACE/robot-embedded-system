void setup() {
  Serial.begin(115200);
  Serial.println("21 Savage.");
}

void loop() {
  Serial.println(Serial.available());
}