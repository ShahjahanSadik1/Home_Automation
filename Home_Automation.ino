#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <EEPROM.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>




const int ledPin1 = D4;  // Pin for LED 1
const int ledPin2 = D0;  // Pin for LED 2
const int ledPin3 = D7;  // Pin for LED 3
const int ledPin4 = D8;  // Pin for LED 4



const uint16_t kRecvPin = D5;
IRrecv irrecv(kRecvPin);
decode_results results;



ESP8266WebServer server(80);  // Web server on port 80

// Function to save LED states to EEPROM
void saveState(int ledIndex, bool state) {
  EEPROM.write(ledIndex, state);  // Save the state at the specific index
  EEPROM.commit();               // Commit changes to EEPROM
}

// Function to read LED state from EEPROM
bool readState(int ledIndex) {
  return EEPROM.read(ledIndex);
}











void setup() {
  Serial.begin(115200);
   Serial.println("IR Receiver Initialized!");

  // Initialize EEPROM with size 6 (one for each LED)
  EEPROM.begin(4);

  // Initialize LED pins
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);


    irrecv.enableIRIn();    // Start the IR receiver

  // Restore LED states from EEPROM
  digitalWrite(ledPin1, readState(0) ? LOW : HIGH);
  digitalWrite(ledPin2, readState(1) ? LOW : HIGH);
  digitalWrite(ledPin3, readState(2) ? LOW : HIGH);
  digitalWrite(ledPin4, readState(3) ? LOW : HIGH);
 











 //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
 //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
    
    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
     res = wm.autoConnect("Smart IOT"); // anonymous ap
    //res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }//WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  

  // Print the IP address
  Serial.print("NodeMCU IP address: ");
  Serial.println(WiFi.localIP());











  // Define routes for the web server
  addLEDControlRoutes();

  // Start the server
  server.begin();
  Serial.println("Web server started");
}







void loop() {
  server.handleClient();  // Handle client requests


//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
   if (irrecv.decode(&results)) {
    Serial.print("Received IR Code: ");
    Serial.println(results.value, HEX); // Display IR code in HEX format

 // Correct comparison
    if(results.value == 0xE218EF807F) { // Use HEX format, not a string
      digitalWrite(ledPin1, !digitalRead(ledPin1));  // Toggle LED state
      Serial.println("LED TOGGLED!");
    }else if(results.value == 0xE218EF40BF){
      digitalWrite(ledPin2, !digitalRead(ledPin2));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } else if(results.value == 0xE218EFC03F){
      digitalWrite(ledPin3, !digitalRead(ledPin3));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } else if(results.value == 0xE218EF20DF){
      digitalWrite(ledPin4, !digitalRead(ledPin4));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } 

    //2   E218EF40BF
    //3   E218EFC03F
    //4  E218EF20DF
    //5  E218EFA05F
    //6  E218EF10EF





    irrecv.resume(); // Prepare for the next signal
  }
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code

  
}//..............void loop








// Function to add LED control routes
void addLEDControlRoutes() {
  server.on("/led1on", HTTP_GET, []() {
    digitalWrite(ledPin1, LOW);
    saveState(0, true);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 1 is now ON");
  });

  server.on("/led1off", HTTP_GET, []() {
    digitalWrite(ledPin1, HIGH);
    saveState(0, false);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 1 is now OFF");
  });

  server.on("/led2on", HTTP_GET, []() {
    digitalWrite(ledPin2, LOW);
    saveState(1, true);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 2 is now ON");
  });

  server.on("/led2off", HTTP_GET, []() {
    digitalWrite(ledPin2, HIGH);
    saveState(1, false);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 2 is now OFF");
  });

  server.on("/led3on", HTTP_GET, []() {
    digitalWrite(ledPin3, LOW);
    saveState(2, true);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 3 is now ON");
  });

  server.on("/led3off", HTTP_GET, []() {
    digitalWrite(ledPin3, HIGH);
    saveState(2, false);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 3 is now OFF");
  });

  server.on("/led4on", HTTP_GET, []() {
    digitalWrite(ledPin4, LOW);
    saveState(3, true);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 4 is now ON");
  });

  server.on("/led4off", HTTP_GET, []() {
    digitalWrite(ledPin4, HIGH);
    saveState(3, false);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 4 is now OFF");
  });


}
