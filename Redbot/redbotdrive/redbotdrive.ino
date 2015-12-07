// @autor Tomas de Camino BEck
// Drive redbot with commands serial-bluetooth

#include <RedBot.h>

RedBotMotors motors;
boolean s1 = true;
boolean s2 = true;
boolean s3 = true;

void setup()
{
  Serial.begin(9600);//connect to serial port
}

void loop()
{
  char inChar;
  if(Serial.available())
  {
     
     Serial.println("Goodnight moon!");
    inChar = (char)Serial.read();
    Serial.write(inChar);
    if (inChar == 'u') {
      motors.drive(-255);
      
      delay(100);
      motors.brake();
    }
    if (inChar == 'd') {
      motors.drive(255);
      delay(100);
      motors.brake();
    }
    if (inChar == 'l') {
      motors.leftDrive(-255);
      delay(50);
      motors.brake();
    }
    if (inChar == 'r') {
      motors.rightDrive(-255);
      delay(50);
      motors.brake();
    }
  }

}
