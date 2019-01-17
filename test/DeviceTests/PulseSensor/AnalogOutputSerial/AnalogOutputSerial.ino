// Analog input terminal to which the pulse sensor is attached
#define PULSE_IN A0

void setup() {
  // Serial setup code
  Serial.begin(115200);
}

void loop() {
  // Print to serial
  Serial.println(analogRead(PULSE_IN));
}
