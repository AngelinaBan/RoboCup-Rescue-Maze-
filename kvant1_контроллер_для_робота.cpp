#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

using namespace webots;
using namespace std;
#define TIME_STEP 64
#define MAX_SPEED 6.28

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  Motor *left_motor = robot->getMotor("wheel2 motor");
  Motor *right_motor = robot->getMotor("wheel1 motor"); 
  
  left_motor->setPosition(INFINITY);
  right_motor->setPosition(INFINITY);
  
  left_motor->setVelocity(0.0);
  right_motor->setVelocity(0.0);
  
  DistanceSensor *prox_sensors[8];
  for (int ind = 0; ind < 8; ++ind){
      std::string ps_name = "ps" + std::to_string(ind);
      prox_sensors[ind] = robot->getDistanceSensor(ps_name);
      prox_sensors[ind]->enable(TIME_STEP);
  }
  
  double left_speed = MAX_SPEED;
  double right_speed = MAX_SPEED;

    while (robot->step(TIME_STEP) != -1) {
  
    bool left_wall = prox_sensors[5]->getValue() > 80;
    bool front_wall = prox_sensors[7]->getValue() > 80;
    if (front_wall == true)
    {
        left_speed = MAX_SPEED;
        right_speed = -MAX_SPEED;
    }
     else 
     {
        if (left_wall == true)
        {
            left_speed = MAX_SPEED;
            right_speed = MAX_SPEED;
        }
         else 
         {
            left_speed = MAX_SPEED/8;
            right_speed = MAX_SPEED;
        }
    }
    
    left_motor->setVelocity(left_speed);
    right_motor->setVelocity(right_speed);
  };


  delete robot;
  return 0;
}
