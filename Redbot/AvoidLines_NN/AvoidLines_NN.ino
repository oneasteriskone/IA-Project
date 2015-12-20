#include <RedBot.h>

#define LINETHRESHOLD 800
#define SPEED 60  // sets the nominal speed. Set to any number from 0 - 255.

RedBotMotors motors;
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
  randomSeed(analogRead(A3));
  brainL.randomize();
  brainR.randomize();
  Serial.begin(9600);

}

void loop()
{


  int l = left.read();
  int r = right.read();
  int c = center.read();
  //set inputs
  brainL.inputs[0] = l;
  brainL.inputs[1] = r;
  brainR.inputs[0] = l;
  brainR.inputs[1] = r;

  //feed forward and calculate weighted sum
  int resL = brainL.feedForward();
  int resR = brainR.feedForward();

  //use this to move servos left and right
  moveLeft(resL);
  moveRight(resR);


  delay(100);//let move for some time then stop
  //train
  brainL.train(eval(l, c, r), resL);
  brainR.train(eval(r, c, l), resR);


}


//***** sensor function******

int eval(int l, int c, int r) {
   if((l > LINETHRESHOLD) && (c > LINETHRESHOLD) && (r > LINETHRESHOLD) )
	{
            return 1;
	}
  else {
    return -1;
  }
}


void moveLeft(char d) {
  if (d > 0) {
    motors.leftMotor(0);
  } else {
    motors.leftMotor(180);
  }
}

void moveRight(char d) {
  if (d > 0) {
    motors.rightMotor(180);
  } else {
   motors.rightMotor(0);
  }
}

void moveServo(char d) {
  if (d > 0) {
    motors.rightMotor(180);
    motors.leftMotor(0);
  } else {
    motors.rightMotor(0);
    motors.leftMotor(180);
  }
}

void stopServo() {
  motors.stop();

}

void turnRedbot(char d) {

    motors.rightMotor(-100);
    motors.leftMotor(-100); 

}


