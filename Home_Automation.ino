#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

//ir Receiver signal pin>>>>>>>>>>>>>>>>
const uint16_t kRecvPin = D5;

//ir Pin for LED 
const int led_1 = D4;  // Pin for LED 1
const int led_2 = D0;  // Pin for LED 2
const int led_3 = D1;  // Pin for LED 3
const int led_4 = D2;  // Pin for LED 4
const int led_5 = D3;  // Pin for LED 5
const int led_6 = D6;  // Pin for LED 6





IRrecv irrecv(kRecvPin);
decode_results results;
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code












const int ledPin1 = D4;  // Pin for LED 1
const int ledPin2 = D0;  // Pin for LED 2
const int ledPin3 = D1;  // Pin for LED 3
const int ledPin4 = D2;  // Pin for LED 4
const int ledPin5 = D3;  // Pin for LED 5
const int ledPin6 = D6;  // Pin for LED 6

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

  // Initialize EEPROM with size 6 (one for each LED)
  EEPROM.begin(6);




// put your setup code here, to run once:
   
    
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
    }








  





//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
Serial.begin(115200);
  Serial.println("IR Receiver Initialized!");

  pinMode(led_1,OUTPUT); // Set LED pin as OUTPUT
  pinMode(led_2,OUTPUT); // Set LED pin as OUTPUT
  pinMode(led_3,OUTPUT); // Set LED pin as OUTPUT
  pinMode(led_4,OUTPUT); // Set LED pin as OUTPUT
  pinMode(led_5,OUTPUT); // Set LED pin as OUTPUT
  pinMode(led_6,OUTPUT); // Set LED pin as OUTPUT

  
  irrecv.enableIRIn();    // Start the IR receiver
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code
//IR Receiver>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Code











  

  // Initialize LED pins
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

  // Restore LED states from EEPROM
  digitalWrite(ledPin1, readState(0) ? LOW : HIGH);
  digitalWrite(ledPin2, readState(1) ? LOW : HIGH);
  digitalWrite(ledPin3, readState(2) ? LOW : HIGH);
  digitalWrite(ledPin4, readState(3) ? LOW : HIGH);
  digitalWrite(ledPin5, readState(4) ? LOW : HIGH);
  digitalWrite(ledPin6, readState(5) ? LOW : HIGH);

  

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
      digitalWrite(led_1, !digitalRead(led_1));  // Toggle LED state
      Serial.println("LED TOGGLED!");
    }else if(results.value == 0xE218EF40BF){
      digitalWrite(led_2, !digitalRead(led_2));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } else if(results.value == 0xE218EFC03F){
      digitalWrite(led_3, !digitalRead(led_3));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } else if(results.value == 0xE218EF20DF){
      digitalWrite(led_4, !digitalRead(led_4));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } else if(results.value == 0xE218EFA05F){
      digitalWrite(led_5, !digitalRead(led_5));  // Toggle LED state
      Serial.println("LED TOGGLED!");
     } else if(results.value == 0xE218EF10EF){
      digitalWrite(led_6, !digitalRead(led_6));  // Toggle LED state
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







  
}

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

  server.on("/led5on", HTTP_GET, []() {
    digitalWrite(ledPin5, LOW);
    saveState(4, true);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 5 is now ON");
  });

  server.on("/led5off", HTTP_GET, []() {
    digitalWrite(ledPin5, HIGH);
    saveState(4, false);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 5 is now OFF");
  });

  server.on("/led6on", HTTP_GET, []() {
    digitalWrite(ledPin6, LOW);
    saveState(5, true);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 6 is now ON");
  });

  server.on("/led6off", HTTP_GET, []() {
    digitalWrite(ledPin6, HIGH);
    saveState(5, false);  // Save state to EEPROM
    server.send(200, "text/plain", "LED 6 is now OFF");
  });
}
