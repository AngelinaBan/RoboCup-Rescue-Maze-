#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Gyro.hpp>
#include <math.h>


using namespace std;
using namespace webots;

#define TIME_STEP 128
#define MAX_SPEED 4.71 
  
 /* void updateGyro() {
      angle += (TIME_STEP / 1000.0) * (gyro->getValues())[1];
  } 
  
  double getAngle() {
      return angle * 180 / 3.1415;
  } */

int main(int argc, char **argv) {

  Robot *robot = new Robot();
  
  Gyro *gyro = robot->getGyro("gyro");
  
  double angle = 0;
  double a = 0;
  int anglegrad = 0;

  Motor *left_motor = robot->getMotor("wheel2 motor");
  Motor *right_motor = robot->getMotor("wheel1 motor");
  
  left_motor->setPosition(INFINITY);
  right_motor->setPosition(INFINITY);
  
  left_motor->setVelocity(0.0);
  right_motor->setVelocity(0.0);
  
  
  
  
//DistanceSensor* distanceSensors[8]; // Create an array containing 8 distance sensors

 // int timeStep = (int)robot->getBasicTimeStep();
  
  /* for(int i = 0; i < 8; i++) 
  
    // Retrieve an enable the distance sensors named ps0, ps1, ps2, etc...
    distanceSensors[i] = robot->getDistanceSensor("ps" + to_string(i));
    distanceSensors[i]->enable(timeStep);  */
  
 DistanceSensor *right_ds = robot->getDistanceSensor("distance sensor2");
 DistanceSensor *front_ds = robot->getDistanceSensor("distance sensor3"); 
 DistanceSensor *yama_front_ds = robot->getDistanceSensor("distance sensor4"); 
 DistanceSensor *yama_right_ds = robot->getDistanceSensor("distance sensor1");
 // инициализация УЗ датчиков
 

  right_ds->enable(TIME_STEP);
  front_ds->enable(TIME_STEP);
  yama_front_ds->enable(TIME_STEP);
  yama_right_ds->enable(TIME_STEP);
  
  gyro->enable(TIME_STEP);
 /* DistanceSensor* distanceSensors[4];
  
for (int ind = 1;ind < 5; ++ind){
      std::string ds_name = "distance_sensor" + std::to_string(ind);
      distanceSensors[ind] = robot->getDistanceSensor(ds_name);
      distanceSensors[ind]->enable(TIME_STEP);
  } */
  
  double right_speed = MAX_SPEED;
  double left_speed = MAX_SPEED;
  
  bool right_wall=false;
  bool front_wall=false;

  while (robot->step(TIME_STEP) != -1) {
  
    right_wall = (right_ds->getValue() < 0.34) || (yama_right_ds->getValue() > 0.4);
    front_wall = (front_ds->getValue() < 0.37) || (yama_front_ds->getValue() > 0.37);
    angle += (TIME_STEP / 1000.0) * (gyro->getValues())[1];
    a = ceil(angle * 180 / 3.1415);
    anglegrad = (int)a;

    if (front_wall == true)
    {
        if (anglegrad%90<=1) {
        left_speed = -MAX_SPEED;
        right_speed = MAX_SPEED;
        //cout<<1<<" "<<front_ds->getValue()<<endl;
        cout<<anglegrad<<" "<<1<<endl;
        }
    }
     else 
     {
        if (right_wall == true)
        {
            left_speed = MAX_SPEED;
            right_speed = MAX_SPEED;
          //  cout<<2<<" "<<front_ds->getValue()<<endl;
          cout<<anglegrad<<" "<<2<<" "<<front_ds->getValue()<<endl;
        }
         else 
         {
            if (anglegrad%90<=1) {
            left_speed = -MAX_SPEED;
            right_speed = MAX_SPEED;
            //cout<<3<<endl;
            cout<<anglegrad<<" "<<3<<endl;
            
        }
    }
    
    left_motor->setVelocity(left_speed);
    right_motor->setVelocity(right_speed);
  }
  
}

  delete robot;
  return 0;
}