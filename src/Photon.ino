/*
 * Project: Accountability
 * Description:
 * Author: Jeffrey Williams
 * Date: March 11, 2022
 */

#define myStatusGreen D0  // myStatus due
#define myStatusBlue D1   // myStatus complete
#define myStatusYellow D2 // myStatus lapsed
#define circleStatusGreen D3
#define circleStatusBlue RX
#define circleStatusYellow TX
#define connect D4
#define help D5
#define human D6  // publish human
#define report D7 // publish report

int b0State;           // the current reading from the input pin
int b0LastState = LOW; // the previous reading from the input pin
int b1State;           // the current reading from the input pin
int b1LastState = LOW; // the previous reading from the input pin
int b2State;           // the current reading from the input pin
int b2LastState = LOW; // the previous reading from the input pin
int b3State;           // the current reading from the input pin
int b3LastState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

int myStatusCommand(String command);
int circleStatusCommand(String command);

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  pinMode(myStatusGreen, OUTPUT);
  pinMode(myStatusBlue, OUTPUT);
  pinMode(myStatusYellow, OUTPUT);
  pinMode(circleStatusGreen, OUTPUT);
  pinMode(circleStatusBlue, OUTPUT);
  pinMode(circleStatusYellow, OUTPUT);
  pinMode(report, INPUT_PULLDOWN);
  pinMode(human, INPUT_PULLDOWN);
  pinMode(help, INPUT_PULLDOWN);
  pinMode(connect, INPUT_PULLDOWN);

  Particle.function("myStatus", myStatusCommand);
  Particle.function("circleStatus", circleStatusCommand);
}

void loop()
{
  // report button
  int b0Reading = digitalRead(report);
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
        bool success = Particle.publish("Hook", "report");
        if (!success)
        {
          // error handling
        }
      }
    }
  }
  // subscribe to status of active report conversation
  // ledState to be HIGH until conversation completed then to be LOW until next attempt to report activity

  // save the reading. Next time through the loop, it'll be the LastState:
  b0LastState = b0Reading;

  // human button
  int b1Reading = digitalRead(human);
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
        bool success = Particle.publish("Hook", "human");
        if (!success)
        {
          // error handling
        }
      }
    }
  }
  // subscribe to status of active human conversation
  // ledState to be HIGH until conversation completed then to be LOW until next attempt

  // save the reading. Next time through the loop, it'll be the LastState:
  b1LastState = b1Reading;
} // end loop()

// this function automagically gets called upon a matching POST request
int myStatusCommand(String command)
{
  if (command == "complete")
  {
    analogWrite(myStatusBlue, 255);
    return 1;
  }
  else if (command == "due")
  {
    analogWrite(myStatusGreen, 255);
    return 1;
  }
  else if (command == "lapsed")
  {
    analogWrite(myStatusYellow, 255);
    return 1;
  }
  else if (command == "reporting")
  {
    analogWrite(myStatusBlue, 125);
    return 1;
  }
  else if (command == "dropped")
  {
    analogWrite(myStatusYellow, 125);
    return 1;
  }
  else
    return -1;
}

// this function automagically gets called upon a matching POST request
int circleStatusCommand(String command)
{
  if (command == "complete")
  {
    analogWrite(circleStatusBlue, 255);
    return 1;
  }
  else if (command == "due")
  {
    analogWrite(circleStatusGreen, 255);
    return 1;
  }
  else if (command == "lapsed")
  {
    analogWrite(circleStatusYellow, 255);
    return 1;
  }
  else if (command == "reporting")
  {
    analogWrite(circleStatusBlue, 125);
    return 1;
  }
  else if (command == "dropped")
  {
    analogWrite(circleStatusYellow, 125);
    return 1;
  }
  else
    return -1;
}