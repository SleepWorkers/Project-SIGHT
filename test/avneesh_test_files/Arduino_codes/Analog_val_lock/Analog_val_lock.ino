void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    // Read A0 and send it to the serial
    String command = Serial.readStringUntil(' ');
    command.toUpperCase();
    if (command.startsWith("READ")) {
      int num = Serial.parseInt();
      Serial.print("A");
      Serial.print(num);
      Serial.print(": ");
      Serial.println(analogRead(num));
    }
  }
}
