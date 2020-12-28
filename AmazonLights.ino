int LEDState = 0;
int LEDpin = 3;
int buttonPin = 2;
int buttonNew;
int buttonOld = 1;
int time = 0;
int debounce = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonNew = digitalRead(buttonPin);

  if (buttonOld == 0 && buttonNew == 1 && ((millis() - time) > debounce)) {
    if (LEDState == 0) {
      digitalWrite(LEDpin, HIGH);
      LEDState = 1;
    } else {
        digitalWrite(LEDpin, LOW);
        LEDState = 0;
    }

    time = millis();
  }
  
  buttonOld = buttonNew;
}