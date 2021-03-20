/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino MKR 1010
  to connect your project to Blynk.

  Note: This requires WiFiNINA library
    from http://librarymanager/all#WiFiNINA

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

#include <Servo.h>

//Servo
int servoPin = 9;
int onPos = 180;
int offPos = 145;
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

int val;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "tKKft11bQWWA41axRCKo67oGV63iaCBp";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HJAY";
char pass[] = "C87e12Np$";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  myServo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  turnOff();
}

void loop()
{
  Blynk.run();

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
