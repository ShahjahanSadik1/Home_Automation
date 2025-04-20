#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t kRecvPin = D5;
IRrecv irrecv(kRecvPin);
decode_results results;

// LED / Relay pins
const int ledPin1 = D4;
const int ledPin2 = D0;
const int ledPin3 = D7;
const int ledPin4 = D8;

// Manual push button pins
const int buttonPin1 = D1;
const int buttonPin2 = D2;
const int buttonPin3 = D3;
const int buttonPin4 = D6;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("IR Receiver Initialized!");

  // WiFiManager
  WiFiManager wm;
  bool res = wm.autoConnect("Smart IOT");
  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart(); // Optional
  } else {
    Serial.println("connected...yeey :)");
  }

  // LED pins
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // Manual button pins
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  // Initial state (OFF)
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);

  // IR
  irrecv.enableIRIn();

  // Web server routes
  addLEDControlRoutes();

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();

  // IR Remote
  if (irrecv.decode(&results)) {
    Serial.print("Received IR Code: ");
    Serial.println(results.value, HEX);

    if (results.value == 0xE218EFC837) {
      digitalWrite(ledPin1, !digitalRead(ledPin1));
      Serial.println("LED TOGGLED 1!");
    } else if (results.value == 0xE218EF40BF) {
      digitalWrite(ledPin2, !digitalRead(ledPin2));
      Serial.println("LED TOGGLED 2!");
    } else if (results.value == 0xE218EFC03F) {
      digitalWrite(ledPin3, !digitalRead(ledPin3));
      Serial.println("LED TOGGLED 3!");
    } else if (results.value == 0xE218EF20DF) {
      digitalWrite(ledPin4, !digitalRead(ledPin4));
      Serial.println("LED TOGGLED 4!");
    }

    irrecv.resume(); // Ready for next
  }

  // Manual Buttons
  static bool lastState1 = HIGH;
  static bool lastState2 = HIGH;
  static bool lastState3 = HIGH;
  static bool lastState4 = HIGH;

  bool currentState1 = digitalRead(buttonPin1);
  bool currentState2 = digitalRead(buttonPin2);
  bool currentState3 = digitalRead(buttonPin3);
  bool currentState4 = digitalRead(buttonPin4);

  if (lastState1 == HIGH && currentState1 == LOW) {
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    Serial.println("Button 1 Pressed - Toggled LED 1");
  }
  lastState1 = currentState1;

  if (lastState2 == HIGH && currentState2 == LOW) {
    digitalWrite(ledPin2, !digitalRead(ledPin2));
    Serial.println("Button 2 Pressed - Toggled LED 2");
  }
  lastState2 = currentState2;

  if (lastState3 == HIGH && currentState3 == LOW) {
    digitalWrite(ledPin3, !digitalRead(ledPin3));
    Serial.println("Button 3 Pressed - Toggled LED 3");
  }
  lastState3 = currentState3;

  if (lastState4 == HIGH && currentState4 == LOW) {
    digitalWrite(ledPin4, !digitalRead(ledPin4));
    Serial.println("Button 4 Pressed - Toggled LED 4");
  }
  lastState4 = currentState4;

  delay(100); // Short delay
}

// Web server LED routes
void addLEDControlRoutes() {
  server.on("/led1on", HTTP_GET, []() {
    digitalWrite(ledPin1, HIGH);
    Serial.println("led1on");
  });

  server.on("/led1off", HTTP_GET, []() {
    digitalWrite(ledPin1, LOW);
    Serial.println("led1off");
  });

  server.on("/led2on", HTTP_GET, []() {
    digitalWrite(ledPin2, HIGH);
    Serial.println("led2on");
  });

  server.on("/led2off", HTTP_GET, []() {
    digitalWrite(ledPin2, LOW);
    Serial.println("led2off");
  });

  server.on("/led3on", HTTP_GET, []() {
    digitalWrite(ledPin3, HIGH);
    Serial.println("led3on");
  });

  server.on("/led3off", HTTP_GET, []() {
    digitalWrite(ledPin3, LOW);
    Serial.println("led3off");
  });

  server.on("/led4on", HTTP_GET, []() {
    digitalWrite(ledPin4, HIGH);
    Serial.println("led4on");
  });

  server.on("/led4off", HTTP_GET, []() {
    digitalWrite(ledPin4, LOW);
    Serial.println("led4off");
  });
}
