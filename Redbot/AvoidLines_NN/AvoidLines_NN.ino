#include <RedBot.h>

#define LINETHRESHOLD 800
#define SPEED 60  // sets the nominal speed. Set to any number from 0 - 255.

RedBotMotors motors;
boolean s1 = true;
boolean s2 = true;
boolean s3 = true;
int leftSpeed;   // variable used to store the leftMotor speed
int rightSpeed;  // variable used to store the rightMotor speed
RedBotSensor left = RedBotSensor(A3);   // initialize a left sensor object on A3
RedBotSensor center = RedBotSensor(A6); // initialize a center sensor object on A6
RedBotSensor right = RedBotSensor(A7);  // initialize a right sensor object on A7

class perceptron
{

    const float c = 0.0001;


  public:
    //arrays that hold inputs and weights
    float* inputs;
    float* weights;
    int n;

    perceptron(int ninputs) {
      n = ninputs;
      inputs = new float[n];
      weights = new float[n];
      inputs[n - 1] = 1;
      for (int i = 0; i < n; i++) {
        // The weights are picked randomly to start.
        //a trick to get values from -1 to 1
        weights[i] = (float)random(-1000, 1000) / 1000;
      }
    }

    //reset weights to random values
    void randomize() {
      for (int i = 0; i < n; i++) {
        // The weights are picked randomly to start.
        weights[i] = (float)random(-1000, 1000) / 1000;
      }
    }

    //training function
    void train(int desired, float f) {
      int guess = f;
      float error = desired - guess;
      for (int i = 0; i < n; i++) {
        weights[i] += c * error * inputs[i];
      }
    }

    //forward function
    float feedForward() {
      float sum = 0;
      for (int i = 0; i < n; i++) {
        sum += inputs[i] * weights[i];
      }
      return activate(sum);
    }


  private:
    //activation function
    int activate(float sum) {
      //regresa 1 si es positivo, -1 si negativo.
      if (sum > 0) {
        return 1;
      }
      else {
        return -1;
      }
    }



};

//*************main code***************

perceptron brainL(3);
perceptron brainR(3);


void setup()
{
    Serial.begin(9600);
  randomSeed(analogRead(A3));
  brainL.randomize();
  brainR.randomize();



}

void loop()
{


 
// if(Serial.available())
 //{
  //Serial.println("Goodnight moon!");
  int l = left.read();
  int r = right.read();
  int c = center.read();
  //set inputs
  brainL.inputs[0] = l;
  brainR.inputs[1] = c;
  brainL.inputs[2] = r;
  brainR.inputs[0] = l;
  brainR.inputs[1] = c;
  brainR.inputs[2] = r;

  //feed forward and calculate weighted sum
  int resL = brainL.feedForward();
  int resR = brainR.feedForward();

  //use this to move servos left and right
  moveLeft(resL);
  moveRight(resR);
  Serial.println(resL);
  //Serial.println(resR);


  delay(100);//let move for some time then stop
  stopRedbot();
  delay(10);
  //train
  brainL.train(eval(l, c, r), resL);
  brainR.train(eval(r, c, l), resR);

 //}
}


//***** sensor function******

int eval(int l, int c, int r) {
   if ((l > LINETHRESHOLD) && (c > LINETHRESHOLD) && (r > LINETHRESHOLD) )
	{
            return 1;
	}
  else {
    return -1;
  }
}


void moveLeft(char d) {
  leftSpeed = -(SPEED - 50);
  if (d > 0) {
    //Serial.println(d);
    motors.drive(-80);
    
  delay(1000);       // for 1000 ms.
  } else {
    //motors.leftMotor(100);//180
    //motors.rightMotor(150); // Turn on right motor clockwise medium power (motorPower = 150) 
    motors.leftDrive(-255);
    motors.leftMotor(80); // Turn on left motor counter clockwise medium power (motorPower = 150) 
  }
}

void moveRight(char d) {
   rightSpeed = SPEED - 50;
  if (d > 0) {
    //motors.rightMotor(-100);//180
    //motors.drive(-255);
    motors.rightDrive(-255);
    motors.rightMotor(80); // Turn on right motor clockwise medium power (motorPower = 150) 
    //motors.leftMotor(-150); // Turn on left motor counter clockwise medium power (motorPower = 150) 
  } else {
   motors.drive(80);
  }
}


void stopRedbot() {
  motors.brake();

}
