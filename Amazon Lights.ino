#include <Servo.h>

//Servo
int servoPin = 9;
int onPos = 180;
int offPos = 150;
int pos;

Servo myServo;

//Button
int buttonPin = 3;
int buttonState;
int previousButtonState = 1;
int toggle = 0; //0 = off, 1 = on

//Debounce
int debounce = 60;
int lastDebounceTime = 0;

void setup() {
  myServo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  turnOff();

}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (((buttonState == 0) && (previousButtonState == 1)) && ((millis() - lastDebounceTime) > debounce)) {
    if (toggle == 0) {
        turnOn();
        toggle = 1;
    }
    else if (toggle == 1) {
        turnOff();
        toggle = 0;
    }
    lastDebounceTime =  millis();
  }

  previousButtonState =  buttonState;
  testServoPos();
}

void turnOn() {
  for (pos = 150; pos <= onPos; pos += 1) {
        myServo.write(pos);
        delay(25);

  }
}

void turnOff() {
  for (pos = 180; pos >= offPos; pos -= 1) {
        myServo.write(pos);
        delay(25);

  }
}

void testServoPos() {
    Serial.print("Pos:");
    Serial.print(val);
    Serial.println("");
}