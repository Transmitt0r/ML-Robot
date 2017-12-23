#include <Arduino.h>
#include <DFRobot2WD.h>
#include <Notes.h>

DFRobot2WD robot = DFRobot2WD();
int code = 0;

String buildString(String dir, int light, obs_t obstacle) {
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
    dir += ",";
    dir += obstacle;
    dir += ",";
    dir += light;
    return dir;
}

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
        int light = robot.getLight();
        obs_t obstacle = robot.obstacleDetect(NULL, NULL);
        
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
