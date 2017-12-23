#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

// WiFi SSID and Password
const char *ssid = "ssid";
const char *password = "password";

HTTPClient http;
WiFiServer server(80);

SoftwareSerial swSer(D0, D1, false, 256);

const char *host = "yourServerIP";

int PostData(String inData) {
    http.begin(host);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    return http.POST("data=" + inData); // Send the request
    http.end(); // close connection
}

void setup() {
    // Set up Serial and Wifi connection
    Serial.begin(9600);
    swSer.begin(9600);
    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the IP address
    Serial.println(WiFi.localIP());
}

void loop()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if(client) {
        delay(100);
        if (client.available()) {
            // Read the first line of the request
            String req = client.readStringUntil('\r');
            client.flush();
            // Match the request
            if (req.indexOf("") != -10) { //checks if you're on the main page
                if (req.indexOf("/forward") != -1) { 
                    swSer.println("forward");
                }
                if (req.indexOf("/backward") != -1) { 
                    swSer.println("backward");
                }
                if (req.indexOf("/left") != -1) { 
                    swSer.println("left");
                }
                if (req.indexOf("/right") != -1) { 
                    swSer.println("right");
                }
            }
            else {
                Serial.println("invalid request");
                client.stop();
            }
            // Prepare the response String
            String s = "HTTP/1.1 200 OK\r\n";
            s += "Content-Type: text/html\r\n\r\n";
            s += "<!DOCTYPE HTML>\r\n<html>\r\n";
            s += "<br><input type=\"button\" name=\"bl\" value=\"Forward\" onclick=\"location.href='/forward'\">"; // Forward-button
            s += "<br>";
            s += "<br><input type=\"button\" name=\"bl\" value=\"Left\" onclick=\"location.href='/left'\">"; // Left-button
            s += "<br><input type=\"button\" name=\"bl\" value=\"Right\" onclick=\"location.href='/right'\">"; // Right-button
            s += "</html>\n";
            s += "<br>";
            s += "<br><input type=\"button\" name=\"bl\" value=\"Backward\" onclick=\"location.href='/backward'\">"; // Backward-button
            client.flush();
            // Send the response to the client
            client.print(s);
        }
    }
}
