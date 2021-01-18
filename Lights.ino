#include <Servo.h>

int servoPin = 9;
int buttonPin = 3;
int potPin = A0;
int toggle = 0;
int buttonState;
int previousButtonState = 1;
int time = 0;
int debounce = 20;
int buttonOn = 170;
int buttonOff = 100;
int pos;

Servo myServo;

void setup() {
    Serial.begin(9600);
    myServo.attach(servoPin);
    pinMode(potPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    turnOff();
}

void loop() {
    buttonState = digitalRead(buttonPin);
    
  if (buttonState == 0 && previousButtonState == 1 && ((millis() - time) > debounce)) {
    if (toggle == 0) {
        turnOff();
        toggle = 1;
    } else {
        turnOn();
        toggle = 0;
    }

    time = millis();
  }
  
    previousButtonState = buttonState;
}

void turnOn() {
    for (pos = 0; pos <= buttonOn; pos += 1) { // goes from 0 degrees to 180 degrees
        myServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void turnOff() {
    for (pos = 180; pos >= buttonOff; pos -= 1) { // goes from 180 degrees to 0 degrees
        myServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
