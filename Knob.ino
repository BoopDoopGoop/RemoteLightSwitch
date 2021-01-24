#include <Servo.h>

int servoPin = 9;
int potPin = A0;
int pos;
int val;

Servo myServo;

void setup() {
    Serial.begin(9600);
    myServo.attach(servoPin);
    pinMode(potPin, INPUT);

}

void loop() {
    val = analogRead(potPin);
    val = map(val, 0, 1023, 0, 180);
    myServo.write(val);
    delay(15);

}