/*
 * Author: Avneesh Mishra
 * Purpose: To generate the brightness levels of LEDs
 */

// Number of LEDs that you have
#define NUM_LEDs 5
// Pin numbers of each one of them
int PINs[NUM_LEDs] = {4, 5, 6, 7, 8};
int PWMs[NUM_LEDs];

void writeValuesOn(int pins[], int pwms[]) {
  for (int i = 0; i < NUM_LEDs; i++) {
    Serial.print("Writing ");
    Serial.print(pwms[i]);
    Serial.print(" to pin ");
    Serial.println(pins[i]);
    analogWrite(pins[i], pwms[i]);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < NUM_LEDs; i++) {
    // Set pin as OUTPUT
    pinMode(PINs[i], OUTPUT);
    // Decide their PWN values
    PWMs[i] = int(255 - i*63.75);
    analogWrite(PINs[i], PWMs[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  writeValuesOn(PINs, PWMs);
}
