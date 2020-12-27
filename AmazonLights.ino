int buttonPin = 2;
int ledPin = 3;
int ledState = 0;
int previousButtonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = not digitalRead(buttonPin);
  
  if ((previousButtonState == 0) && (buttonState == 1)) {
    if (ledState == 0) {
      ledState = 1;
    }
    if (ledState == 1) {
      ledState = 0;
    }
  }
  previousButtonState = buttonState;
  digitalWrite(ledPin, ledState);
}