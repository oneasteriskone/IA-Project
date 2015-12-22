#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(5,6); 
 
const int trigPin = 10;
const int echoPin = 11;

long duration;
int distance;
 
Servo myServo; 
 
void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  BT.begin(9600);
  //Serial.begin(9600); //Used for debug
  
  myServo.attach(9); // Servo pin
  myServo.write(0);
  delay(3000);

//  BT.println("Hello from Arduino");
}

char b; // Stores the character for bluetooth

double DtoR(double degrees){
  return degrees * 1000 / 57296;
}

double RtoD(double radians){
  return radians * 57296 / 1000;
}

void loop() {
  if(BT.available()){
    b = (BT.read());
    if(b == 'r'){
      myServo.write(0);  
//      BT.println("DA! ");
      
      int degree = 0;
      for(double i = 0; i <= 90; i+=10){
        myServo.write(i);
        delay(50);
//        BT.println(i);
        double distance = calculateDistance();
        if(distance < 50){
          double y = distance*sin(DtoR(i));
          double xDegrees = 180 - (90 + i);
          double x = distance*sin(DtoR(xDegrees));
          
//          BT.println("!!! Colision detectada! !");  
//          BT.write(distance);
          BT.print(i);
          BT.print(','); 
          BT.print(x);
          BT.print(',');
          BT.print(y);
          BT.print('\n'); 
          break;
        }
        delay(500);
        
      }
       
      BT.println("end");
      
    }  
    if(b == 'l'){
      myServo.write(90);
      BT.println("Moving left");  
    }
    if(b == 's'){
        BT.println(calculateDistance());
    }
    if (b=='?'){
      BT.println("r = Right ; l = Left ; s = Ultrasonic BEAAAM");
    }   
  }
}
 
int calculateDistance(){ 
   
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
}
