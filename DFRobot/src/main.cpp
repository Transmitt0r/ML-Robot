#include <Arduino.h>
#include <DFRobot2WD.h>
#include <Notes.h>

DFRobot2WD robot = DFRobot2WD();
int code = 0;

void setup() {
    // set up Serial connection
    Serial.begin(9600);
}

void loop() {
    // Clears inData String every loop
    String inData = "";

    // New Serial data available
    if (Serial.available())
    {
        inData = Serial.readStringUntil('\r'); // Read line
        Serial.flush();
        if (inData == "forward")
        {
            robot.motorControl(FORWARD, 100, FORWARD, 100);
            delay(250);
            robot.motorStop();
        }
        if (inData == "backward")
        {
            robot.motorControl(BACKWARD, 100, BACKWARD, 100);
            delay(250);
            robot.motorStop();
        }
        if (inData == "left")
        {
            robot.motorControl(FORWARD, 100, BACKWARD, 100);
            delay(250);
            robot.motorStop();
        }
        if (inData == "right")
        {
            robot.motorControl(BACKWARD, 100, FORWARD, 100);
            delay(250);
            robot.motorStop();
        }
    }
}
