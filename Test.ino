int buttonPin = 2;
int lastButtonState = 1;
long unsigned int lastPress;
int debounceTime = 20;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {  
  int buttonState = digitalRead(buttonPin); 
  Serial.print(lastPress);

  if((millis() - lastPress) > debounceTime)
    lastPress = millis();                            
                          
  if(buttonState == 0 && lastButtonState == 1) {  
    Serial.println("OK Boomer");
    lastButtonState = 0;   
    }

  if(buttonState == 1 && lastButtonState == 0) {
      lastButtonState = 1;    
    }
  }



 
