/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/me/Code/Particle/Photon/src/Photon.ino"
/*
 * Project Report Activity
 * Description:
 * Author: Jeffrey Williams
 * Date: March 11, 2022
 */

void setup();
void loop();
#line 8 "c:/Users/me/Code/Particle/Photon/src/Photon.ino"
#define ledPin D7
#define buttonPin D0
int ledState = LOW;       // the current state of the output pin
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
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH && ledState == LOW)
      {
        // publish event
        bool published;
        ledState = HIGH; //might subscribe to conversation status for local feedback. 
        published = Particle.publish("Report", "new-report");
        if (!published) {
          // handle publishing error locally
        }
      }
    }
  }
  // subscribe to status of active report conversation
  // ledState to be HIGH until conversation completed then to be LOW until next attempt to report activity

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  // wait
  // delay(10000);
}