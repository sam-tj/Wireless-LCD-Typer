#include "index.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


#ifndef STASSID
#define STASSID "YOUR_SSID"
#define STAPSK  "YOUR_PASSWORD"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const long interval = 10000;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

String initailString = "Connect with me@";

bool resetVal = false;

ESP8266WebServer server(80);

const int led = 16;

void handleRoot() {
  digitalWrite(led, 0);
  server.send(200, "text/html", index_html);
  digitalWrite(led, 1);
}

void getInput() {
  for (uint8_t i = 0; i < server.args(); i++) {
    Serial.println( server.argName(i) + ": " + server.arg(i) );
  }
  previousMillis = millis();
  resetVal = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  if (server.arg(0).length() > 15) {
    lcd.setCursor(0, 0);
    lcd.print(server.arg(0).substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(server.arg(0).substring(16, 31));
  }
  else
  {
    lcd.print(server.arg(0));
  }
  server.send(200, "text/html", index_html);
}

void handleNotFound() {
  digitalWrite(led, 0);
  server.send(200, "text/plain", "Not Found");
  digitalWrite(led, 1);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  Wire.begin(D5, D6);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(initailString);
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/get", getInput);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}



void loop(void) {
  server.handleClient();
  MDNS.update();
  currentMillis = millis();  
  if (currentMillis - previousMillis >= interval && resetVal == true) {
    previousMillis = currentMillis;
    resetVal = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(initailString);
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
  }
}
