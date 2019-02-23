/*
 * Blinks
 * 
 * Author: Avneesh Mishra
 * Basic example to show the RED, YELLOW and GREEN LEDs blink in order
 * 
 * Hardware Required:
 *     - LaunchPad with RED, YELLOW and GREEN LEDs
 * We've used the CC3220SF LAUNCHXL
 * 
 */

// Define Red, Yellow and Green as LED variables
#define LED1 RED_LED
#define LED2 YELLOW_LED
#define LED3 GREEN_LED

void setup() {
  // Set all the LEDs as OUTPUT type
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  // Setup the serial to 115200 baud rate
  Serial.begin(115200);
}

void loop() {
  // Turn ON only LED1 and notify on serial
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  Serial.println("LED1 is ON");
  delay(1000);
  // Turn ON only LED2
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  Serial.println("LED2 is ON");
  delay(1000);
  // Turn ON only LED3
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  Serial.println("LED3 is ON");
  delay(1000);
}
