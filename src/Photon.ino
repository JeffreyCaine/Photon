/*
 * Project Photon
 * Description:
 * Author:
 * Date:
 */

#define ledpin D7
#define buttonpin D0
int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.

  // alternate the PIN between high and low
  // digitalWrite(PIN, (state) ? HIGH : LOW);

  // invert the state
  // state = !state;

  // publish event
  Particle.publish("Report", "new-report", PRIVATE);

  // wait
  // delay(10000);
}