#include <Servo.h>
#include <Wire.h>

Servo myServo;


void setup()
{
    Wire.begin();
    myServo.attach(9);
}

void loop()
{
    updateServo();
}

void updateServo(int) 
{
    myServo.write(map(, 0, 1, 0, 90));
}
