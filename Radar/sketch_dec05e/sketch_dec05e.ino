#include <Servo.h>. 
#include <SoftwareSerial.h>
SoftwareSerial BT(5 ,6); 
 
const int trigPin = 11;
const int echoPin = 10;
const int bluePin  = 12;

long duration;
int distance;
 
Servo myServo; 
 
void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(bluePin, OUTPUT);
  
  BT.begin(9600);
  //Serial.begin(9600); //Used for debug
  
  myServo.attach(9); // Servo pin
  myServo.write(0);

  BT.println("Hello from Arduino");
}

char b; // Stores the character for bluetooth

void loop() {
  if(BT.available()){
    b = (BT.read());
    if(b == 'r'){
      myServo.write(0);  
      BT.println("Moving right");
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
