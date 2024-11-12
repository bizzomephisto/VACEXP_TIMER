//
//    Timer Control Code for ESP8266
//    Author: Benjamin Beaugh
//    Created: 11/10/2024
//    This code is free to use, modify, and distribute, provided that the following conditions are met:
//    - The original author (Benjamin Beaugh) must be credited in all copies or substantial portions of the code.
//    - This code is provided "as-is," without warranty of any kind, express or implied.
//
//    You are free to:
//    - Use this code for personal or commercial purposes.
//    - Modify and share this code, as long as this license header is retained.
//
//    No liability:
//    - The author is not liable for any damage or loss resulting from the use of this code.
//
//    This project aims to foster learning and creativity by making software freely available.
//




#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Define pins for relays
#define VAC_RELAY_PIN 16  // GPIO 16 (VAC relay pin)
#define EXP_RELAY_PIN 4   // GPIO 4 (EXP relay pin)

// WiFi settings
const char* ssid = "vactimer";
const char* password = "11082024VACexp";

// Web server setup
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600); // Initialize Serial for debugging

  pinMode(VAC_RELAY_PIN, OUTPUT);
  pinMode(EXP_RELAY_PIN, OUTPUT);
  digitalWrite(VAC_RELAY_PIN, LOW);
  digitalWrite(EXP_RELAY_PIN, LOW);

  // Set up WiFi as an access point
  WiFi.softAP(ssid, password);
  Serial.print("Access Point " );
  Serial.print(ssid);
  Serial.println(" started" );
  Serial.print("IP address: " );
  Serial.println(WiFi.softAPIP());

  // Define server routes
  server.on("/toggleVac", []() {
    Serial.println("Toggling VAC relay");
    digitalWrite(VAC_RELAY_PIN, !digitalRead(VAC_RELAY_PIN));
    server.send(200, "text/plain", "VAC relay toggled");
  });

  server.on("/toggleExp", []() {
    Serial.println("Toggling EXP relay");
    digitalWrite(EXP_RELAY_PIN, !digitalRead(EXP_RELAY_PIN));
    server.send(200, "text/plain", "EXP relay toggled");
  });

  server.on("/unlatchAll", []() {
    Serial.println("Unlatching all relays");
    digitalWrite(VAC_RELAY_PIN, LOW);
    digitalWrite(EXP_RELAY_PIN, LOW);
    server.send(200, "text/plain", "All relays unlatched");
  });

  server.on("/", []() {
    Serial.println("Client connected");
    server.send(200, "text/plain", "You shouldn't be seeing this. The fact that you are means it's working");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
