/* int LEDState = 0;
int LEDpin = 12;
int buttonPin = 2;
int buttonState;
int previousButtonState = 1;
int time = 0;
int debounce = 80;

void setup() {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == 0 && previousButtonState == 1 && ((millis() - time) > debounce)) {
    if (LEDState == 0) {
      digitalWrite(LEDpin, HIGH);
      LEDState = 1;
    } else {
        digitalWrite(LEDpin, LOW);
        LEDState = 0;
    }

    time = millis();
  }
  
  previousButtonState = buttonState;
} */