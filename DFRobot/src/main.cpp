#include <Arduino.h>
#include <DFRobot2WD.h>
#include <Notes.h>

DFRobot2WD robot = DFRobot2WD();

void setup() {
    // set up Serial connection
    Serial.begin(9600);
}

void loop() {
    Serial.println(robot.getLight());
    delay(1000);
}
