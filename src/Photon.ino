/*
 * Project Report Activity
 * Description:
 * Author: Jeffrey Williams
 * Date: March 11, 2022
 */

#define myStatus D5
#define myCircleStatus D6
#define deviceStatus D7
#define newReport D0
#define freePass D1
#define motivation D2

bool statusLED = LOW;  // onboard device LED
int b0State;           // the current reading from the input pin
int b0LastState = LOW; // the previous reading from the input pin
int b1State;           // the current reading from the input pin
int b1LastState = LOW; // the previous reading from the input pin
int b2State;           // the current reading from the input pin
int b2LastState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

int myStatusLED(String command);

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  pinMode(newReport, INPUT_PULLDOWN);
  pinMode(freePass, INPUT_PULLDOWN);
  pinMode(motivation, INPUT_PULLDOWN);
  pinMode(myStatus, OUTPUT);
  pinMode(myCircleStatus, OUTPUT);
  pinMode(deviceStatus, OUTPUT);

  Particle.function("myStatus", myStatusLED);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // read the state of the switch into a local variable:
  int b0Reading = digitalRead(newReport);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (b0Reading != b0LastState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (b0Reading != b0State)
    {
      b0State = b0Reading;
      if (b0State == HIGH)
      {
        // publish event
        bool success;
        success = Particle.publish("Report");
        if (!success)
        {
          for (int i = 0; i < 6; i++)
          {
            statusLED = !statusLED;
            digitalWrite(deviceStatus, statusLED);
            delay(250);
          }
        }
      }
    }
  }

  // subscribe to status of active report conversation
  // ledState to be HIGH until conversation completed then to be LOW until next attempt to report activity
  // set the LED:
  // digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the b0LastState:
  b0LastState = b0Reading;

  // read the state of the switch into a local variable:
  int b1Reading = digitalRead(freePass);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (b1Reading != b1LastState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (b1Reading != b1State)
    {
      b1State = b1Reading;
      if (b1State == HIGH)
      {
        // publish event
        bool success;
        success = Particle.publish("Free-pass");
        if (!success)
        {
          for (int i = 0; i < 6; i++)
          {
            statusLED = !statusLED;
            digitalWrite(deviceStatus, statusLED);
            delay(250);
          }
        }
      }
    }
  }

  // subscribe to status of active report conversation
  // ledState to be HIGH until conversation completed then to be LOW until next attempt to report activity
  // set the LED:
  // digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the b0LastState:
  b1LastState = b1Reading;

  // read the state of the switch into a local variable:
  int b2Reading = digitalRead(motivation);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (b2Reading != b2LastState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (b2Reading != b2State)
    {
      b2State = b2Reading;
      if (b2State == HIGH)
      {
        // publish event
        bool success;
        success = Particle.publish("Motivation");
        if (!success)
        {
          for (int i = 0; i < 6; i++)
          {
            statusLED = !statusLED;
            digitalWrite(deviceStatus, statusLED);
            delay(250);
          }
        }
      }
    }
  }

  // subscribe to status of active report conversation
  // ledState to be HIGH until conversation completed then to be LOW until next attempt to report activity
  // set the LED:
  // digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the b0LastState:
  b2LastState = b2Reading;

  digitalWrite(deviceStatus, LOW);
}

// this function automagically gets called upon a matching POST request
int myStatusLED(String command)
{
  // look for the matching argument "coffee" <-- max of 64 characters long
  if (command == "complete")
  {
    digitalWrite(myStatus, HIGH);
    return 1;
  }
  else if (command == "reset")
  {
    digitalWrite(myStatus, LOW);
    return 1;
  }
  else
    return -1;
}