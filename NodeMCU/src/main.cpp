#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

//WiFi SSID and Password
const char *ssid = "ssid";
const char *password = "pass";

WiFiClient client;
HTTPClient http;
SoftwareSerial swSer(14, 12, false, 256);

const char *host = "yourServerIP";

void setup() {
    // Set up Serial and Wifi connection
    Serial.begin(9600);
    swSer.begin(9600);
    WiFi.begin(ssid, password);
    // Let module initialize
    delay(1000);
    int retries = 0;
    // Attempt to connect to WiFi 14 times before timing out
    while ((WiFi.status() != WL_CONNECTED) && (retries < 15))
    {
        retries++;
        delay(500);
    }
}

void loop()
{
    // Clear Serial data every loop
    String inData = "";
    if (swSer.available()) // Check if new Serial data is available
    {
        inData = swSer.readStringUntil('\n'); // Reads data and terminates string at newline
        Serial.println(inData);
        http.begin(host);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpCode = http.POST("data="+inData); // Send the request
        String payload = http.getString();     // Get the response payload
        Serial.println(httpCode); // Print HTTP return code
        Serial.println(payload);  // Print request response payload
        http.end(); // close connection
    }
}
