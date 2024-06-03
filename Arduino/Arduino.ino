#include <Servo.h>

// Create a Servo object to control a servo
Servo myServo;

// Define the pin for the servo signal
const int servoPin = 11;

const byte numChars = 3;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  recvWithStartEndMarkers();

  if (newData == true) {
      newData = false;

      Serial.println(getDesiredAngle());
      myServo.write(getDesiredAngle());
  }
}


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

int getDesiredAngle() {
  return receivedChars[0] == 'C' ? 2 : 90;
}