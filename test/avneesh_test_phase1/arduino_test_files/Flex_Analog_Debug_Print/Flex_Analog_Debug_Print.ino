/*
 * Connect sensor to A0 analog input pin
 * Open serial monitor or serial plotter to monitor the value
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  delay(250);
}
