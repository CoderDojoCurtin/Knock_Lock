#include <Servo.h>

Servo myServo;

// Set these to the corresponding pin numbers.
const int piezo = A0;
const int switchPin   = 3;
const int greenLED    = 4;
const int yellowLED   = 5;
const int redLED      = 6;
const int servoPin    = 9;

int knockVal;

// Set to the custom spot you consider quite or loud.
const int quietKnock = 10;
const int loudKnock = 100;

// Is the system locked?
boolean locked = false;

// Number of times you have knocked.
int numberOfKnocks = 0;

void setup() {
  myServo.attach(servoPin);

  // Sets the pins to write binary.
  pinMode(greenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(RedLED, OUTPUT);

  // Sets the switch pin to read binary.
  pinMode(switchPin, INPUT);

  // Sets up the serial communicatiton to 9600 bits/second.
  Serial.begin(9600);

  // Initializes green to high.
  digitalWrite(greenLED, HIGH);

  // Sets servo to position 0.
  myServo.write(0);

  // Prints to the serial monitor at 9600 baud.
  Serial.println("The box is unlocked!);
}







void loop() {
  // Checks if the servo is locked.
  if ( locked != false )
  {
    // Pushing the button locks the servo.
    if ( digitalRead(swichPin) == HIGH )
    {
      locked = true;
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      myServo.write(90);
      Serial.println("LOCKED");
      delay(1000);
    }
  }
  else  // If The servo is not locked.
  {
    knockVal = analogRead(piezo);
    // Checks that the number of knocks does not exceed the amount to unlock.
    if ( numberOfKnocks < 3 && knockVal > 0)
    {
      // Checks if the knock is valid.
      if ( checkForKnock(knockVal) == true )
      {
        numberOfKnocks++;
      }
      Serial.print(3 - numberOfKnocks); Serial.println(" LEFT");
    }
    // When there are enough locks, unlock the servo.
    else if ( numberOfKnocks >= 3 )
    {
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      Serial.println("UNLOCKED");
    }
  }
}











// Checks if the current knock is valid.
boolean checkForKnock ( int value )
{
  // Checks that the value is within the bounds of a knock.
  if ( value > quietKnock && value < loudKnock )
  {
    digitalWrite(yellowLED, HIGH);
    delay(1000);
    digitalWrite(yellowLED, LOW);

    Serial.print("VALID KNOCK: ");
    Serial.println(value);

    return true;
  }
  else
  {
    Serial.print("Bad knock value");
    Serial.println(value);
    return false;
  }
}
