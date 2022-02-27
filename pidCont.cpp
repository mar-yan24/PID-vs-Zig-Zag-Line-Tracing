#include <webots/Robot.hpp>
#include <webots/Camera.hpp>
#include <webots/Motor.hpp>
#include <iostream>

using namespace webots;
using namespace std;


int main(int argc, char **argv) {

  Robot *robot = new Robot();
  Camera *leftColor = robot->getCamera("leftColor");
  Camera *rightColor = robot->getCamera("rightColor");
  
  Motor *leftMotor = robot->getMotor("left wheel");
  Motor *rightMotor = robot->getMotor("right wheel");

  int timeStep = (int)robot->getBasicTimeStep();
  leftColor->enable(timeStep);
  rightColor->enable(timeStep);
  
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  int height = leftColor->getHeight();
  int width = leftColor->getWidth();

  double kp = .1;
  double speed = 3.0;    

  while (robot->step(timeStep) != -1) {
    int leftVal = leftColor->imageGetGray(leftColor->getImage(), width, width/2, height/2);
    int rightVal = rightColor->imageGetGray(rightColor->getImage(), width, width/2, height/2);

    int leftRed = leftColor->imageGetRed(leftColor->getImage(), width, width/2, height/2);
    int leftGreen = leftColor->imageGetGreen(leftColor->getImage(), width, width/2, height/2);
    
    double lSpeed = 0, rSpeed = 0;
    double error = leftVal - rightVal;
    
    if(leftRed > 170 && leftGreen < 130)
    {
      leftMotor->setVelocity(0);
      rightMotor->setVelocity(0);
      cout << "stopped!" << endl;
    }
    else
    {
      if (error > 0) 
      {
        lSpeed = speed+abs(error*kp);
        rSpeed = speed-abs(error*kp);
      }
      else if (error < 0) 
      {
        lSpeed = speed-abs(error*kp);
        rSpeed = speed+abs(error*kp);
      }
      else 
      {
        lSpeed = speed;
        rSpeed = speed;
      }
    }
    
    
    
    cout << "red: " << leftRed << endl;
    cout << "green: " << leftGreen << endl;
    
    leftMotor->setVelocity(lSpeed);
    rightMotor->setVelocity(rSpeed);    
    
  };

  delete robot;
  return 0;
}
