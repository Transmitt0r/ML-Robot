#include <Arduino.h>
#include <DFRobot2WD.h>
#include <Notes.h>

DFRobot2WD robot = DFRobot2WD();
const byte numChars = 32; // Use this to set the size of the received serial Data
char receivedChars[numChars];
boolean newData = false;

String obstacle2string(obs_t obstacle) // This simply takes the provided obstacle object and outputs a string
{
    String obstacle_mask = "";
    if (obstacle == BOTH)
    {
        obstacle_mask = "both";
    }
    else if (obstacle == LEFT)
    {
        obstacle_mask = "left";
    }
    else if (obstacle == RIGHT)
    {
        obstacle_mask = "right";
    }
    else
    {
        obstacle_mask = "none";
    }
    return obstacle_mask;
}

String buildJson(String dir, float light, obs_t obstacle) // This makes json out of our sensor-data
{
    String json;

    json = "<{";

    json += "\"direction\"=";
    json += "\"" + dir + "\"";
    json += ",";

    json += "\"obstacle\"=";
    json += "\"" + obstacle2string(obstacle) + "\"";
    json += ",";

    json += "\"light\"=";
    json += light;

    json += "}>";
    return json;
}

void recvWithStartEndMarkers() // A custom function to received serial communication
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false)
    {
        rc = Serial.read();

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
}

void loop()
{
    recvWithStartEndMarkers(); // Checks and gets new serial communication
    if (newData == true)
    {
        float light = robot.getLight(); // Gets data from light-sensor
        obs_t obstacle = robot.obstacleDetect(NULL, NULL); // Gets obstacle-data
        newData = false;
        if (!strcmp(receivedChars, "f")) // Drives Forward
        {
            String res = buildJson("f", light, obstacle);
            robot.motorControl(FORWARD, 100, FORWARD, 100);
            delay(250);
            robot.motorStop();
            Serial.print(res);
        }
        if (!strcmp(receivedChars, "b")) // Drives Backward
        {
            String res = buildJson("b", light, obstacle);
            robot.motorControl(BACKWARD, 100, BACKWARD, 100);
            delay(250);
            robot.motorStop();
            Serial.print(res);
        }
        if (!strcmp(receivedChars, "l")) // Drives Left
        {
            String res = buildJson("l", light, obstacle);
            robot.motorControl(FORWARD, 100, BACKWARD, 100);
            delay(250);
            robot.motorStop();
            Serial.print(res);
        }
        if (!strcmp(receivedChars, "r")) // Drives Right
        {
            String res = buildJson("r", light, obstacle);
            robot.motorControl(BACKWARD, 100, FORWARD, 100);
            delay(250);
            robot.motorStop();
            Serial.print(res);
        }
    }
}
