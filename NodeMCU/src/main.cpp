#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

// WiFi SSID and Password
const char *ssid = "ssid";
const char *password = "password";

WiFiServer server(80);

SoftwareSerial swSer(D5, D6, false, 256);
const byte numChars = 64;
char receivedChars[numChars];
boolean newData = false;

const char *host = "yourServerIP";

void recvWithStartEndMarkers() // A custom function to received serial communication
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (swSer.available() > 0 && newData == false)
    {
        rc = swSer.read();

        if (recvInProgress == true)
        {
            if (rc != endMarker) // checks if we reached our endmarker
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars)
                {
                    ndx = numChars - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) // sets bool true if we reached our startmarker
        {
            recvInProgress = true;
        }
    }
}

void setup()
{
    Serial.begin(9600);
    swSer.begin(9600);
    // Connect to WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    // Start the server
    server.begin();
}

void loop()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (client)
    {
        delay(1);
        if (client.available())
        {
            // Read the first line of the request
            String req = client.readStringUntil('\n');
            // Match the request
            if (req.indexOf("") != -10)
            { // prints commands to software serial according to request
                if (req.indexOf("/forward") != -1)
                {
                    swSer.print("<f>");
                }
                if (req.indexOf("/backward") != -1)
                {
                    swSer.print("<b>");
                }
                if (req.indexOf("/left") != -1)
                {
                    swSer.print("<l>");
                }
                if (req.indexOf("/right") != -1)
                {
                    swSer.print("<r>");
                }
                while (!newData) // waits for new data to be received
                {
                    recvWithStartEndMarkers();
                }
                // Prepare the response String
                String s = "HTTP/1.1 200 OK\r\n";
                s += "Content-Type: application/json\r\n\r\n";
                s += receivedChars;

                // Send the response to the client
                client.print(s);
                newData = false;
            }
            else
            {
                Serial.println("invalid request");
                client.stop();
            }
        }
    }
}
