#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"
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
int debounce = 70; //(Anna Security)
int lastDebounceTime = 0;

int val; 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

String controlString;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (controlString.length() < 100) {
          // write characters to string
          controlString += c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 10");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          client.println("<html>");
          client.println("<head>");
          client.println("<title>The Geek Pub Arduino Ethernet Test Page</title>");
          client.println("</head>");
          client.println("<body>");
          /* client.println("<img src=\"https://cdn.thegeekpub.com/wp-content/uploads/2018/01/the-geek-pub-big-logo-new.jpg\") style=\"width: 55%; margin-left: auto; margin-right: auto; display: block;\" />"); */
          client.println("<h2 style=\"color: green; font-family: arial; text-align: center;\">LED ON/OFF FROM WEBPAGE</h2>");
          client.println("<hr>"); 
          client.println("<h2 style=\"color: blue; font-family: arial; text-align: center;\"><a href=\"/?GPLED2ON\"\">Turn On</a> - <a href=\"/?GPLED2OFF\"\">Turn Off</a></h2>");
          client.println("</body>");
          client.println("</html>");

          // control arduino pin
          if ((controlString.indexOf("?GPLED2ON") > -1) && ((millis() - lastDebounceTime) > debounce)) {
            turnOn();
            lastDebounceTime = millis();
          }
          else {
            if ((controlString.indexOf("?GPLED2OFF") > -1) && ((millis() - lastDebounceTime) > debounce)){
              turnOff();
              lastDebounceTime = millis();
            }
          }
                    //clearing string for next read 
          controlString="";
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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