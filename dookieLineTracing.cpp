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
  

  while (robot->step(timeStep) != -1) {
    int leftVal = leftColor->imageGetGray(leftColor->getImage(), width, width/2, height/2);
    int rightVal = rightColor->imageGetGray(rightColor->getImage(), width, width/2, height/2);

    int leftRed = leftColor->imageGetRed(leftColor->getImage(), width, width/2, height/2);
    int leftGreen = leftColor->imageGetGreen(leftColor->getImage(), width, width/2, height/2);
    
    
    if(leftRed > 170 && leftGreen < 130)
    {
      leftMotor->setVelocity(0);
      rightMotor->setVelocity(0);
      cout << "stopped!" << endl;
    }
    else
    {
      if(leftVal > 150 && rightVal < 100)
      {
        leftMotor->setVelocity(3);
        rightMotor->setVelocity(0);  
      }
      else if (rightVal > 150 && leftVal < 100)
      {
        leftMotor->setVelocity(0);
        rightMotor->setVelocity(3);
      }
      else
      {
        leftMotor->setVelocity(3);
        rightMotor->setVelocity(3); 
      }
    }
    
    
    
    cout << "red: " << leftRed << endl;
    cout << "green: " << leftGreen << endl;

  };

  delete robot;
  return 0;
}
