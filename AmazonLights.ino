int buttonPin = 2;
int ledPin = 3;
int lastButtonState = 1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {  
  int buttonState = digitalRead(buttonPin); // 1 when unpressed, 0 pressed

  if(buttonState == 0 && lastButtonState == 1) {
    digitalWrite(ledPin,not buttonState);
    lastButtonState = 0;
  }
  else if (buttonState == 1 && lastButtonState == 0) {
    lastButtonState = 1;
  }
    
}


 
