/* This code waits for 20 seconds and shuts itself off while blinking an LED.
 * This is used to make sure everyone washes their hands for at least 20 seconds.
 * 
 * Written for ATTiny85 without bootloader so the startup is almost instantaneous.
 * 
 * Pushing a button powers on the board which turns the power pin to
 * high during the setup stage. After 20 seconds the power pin is set to low
 * to turn off the board. Blinkin speed of the LED increases before the time
 * runs out.
 * 
 * Author: Mika Hassinen
 */

#define LED_PIN     0
#define POWER_PIN   1
#define TIME_LIMIT  20 // seconds

unsigned long previousMillis = 0;
uint16_t state;

void setup() {
  // turn on power before button is released
  pinMode(POWER_PIN , OUTPUT);
  digitalWrite(POWER_PIN , HIGH);
  // set LED pin to output and turn it on
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 255);
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis > TIME_LIMIT * 1000) {
     digitalWrite(POWER_PIN, LOW);
  }
  // increase blinking speed
  state = map(currentMillis, 0, TIME_LIMIT * 1000, 1000, 10);
  analogWrite(LED_PIN, 255);
  delay(state);
  analogWrite(LED_PIN, 80); // do not turn the LED completely off while blinking
  delay(state);
}
