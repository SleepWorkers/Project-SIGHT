/*
 * Author: Avneesh Mishra
 * Purpose: To generate the brightness levels of LEDs, take ADC readings and send it to serial monitor
 */

// Number of LEDs that you have
#define NUM_LEDs 5
#define PWM_val(i) int(255 - i*63.75)
// Pin numbers of each one of them
int PINs[NUM_LEDs] = {2, 1, 17, 64};
// PWMs to write
int PWMs[NUM_LEDs];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < NUM_LEDs; i++) {
    // Set pin as OUTPUTx
    pinMode(PINs[i], OUTPUT);
    // Decide their PWN values
    PWMs[i] = PWM_val(i);
    analogWrite(PINs[i], PWMs[i]);
  }
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
