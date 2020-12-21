int potPin = A0;
int buttonPin = 2;
int ledPin = 3;
int random;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potState = analogRead(potPin) / 4;
  analogWrite(ledPin, potState);
  int buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, not buttonState);
}
