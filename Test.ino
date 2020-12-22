int potPin = A0;
int buttonPin = 2;
int ledPin = 3;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potState = analogRead(potPin); 
  int buttonState = digitalRead(buttonPin);
  Serial.print("Button: ");
  Serial.print(buttonState);
  Serial.println("");
  Serial.print("Pot: ");
  Serial.print(potState);
  Serial.println("");
}
