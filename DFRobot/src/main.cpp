#include <Arduino.h>
#include <DFRobot2WD.h>
#include <Notes.h>

DFRobot2WD robot = DFRobot2WD();

void setup() {
    Serial.begin(9600);
    Serial.println("Interfacing with NodeMCU");
}

void loop() {
    Serial.println("Sending Data");
    Serial.print("{\"light\":");
    Serial.print(robot.getLight());
    Serial.print("}");
    Serial.println();
    delay(200);
}
