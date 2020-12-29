#include <Servo.h>

int servoPin = 9;
int servoPos;
int potPin = A0;
Servo myServo;

void setup() {
    Serial.begin(9600);
    myServo.attach(servoPin);
    pinMode(potPin, INPUT);
}

void loop() {
    int potState = analogRead(potPin)/4;
    servoPos = potState;
    myServo.write(servoPos);

}
