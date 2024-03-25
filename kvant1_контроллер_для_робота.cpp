#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
//бибилиотеки


using namespace std;
using namespace webots;
//инициализация команд


#define TIME_STEP 64
#define MAX_SPEED 5.8
#define COUNTER_90_DEG 1
//константы


  Robot *robot = new Robot();
//  инициализация робота

  
double left_speed = MAX_SPEED;
double right_speed = MAX_SPEED;
// объявление переменных, хранящих значение скоростей УЗ датчиков

int counter = 0;
int programm = 1;
  
  
int main(int argc, char **argv) {
//основная программа
  
  
  Motor *left_motor = robot->getMotor("wheel2 motor");
  Motor *right_motor = robot->getMotor("wheel1 motor");
//  инициализация моторов
  
  
  
  left_motor->setPosition(INFINITY);
  right_motor->setPosition(INFINITY);
//установка моторов
  
  
  left_motor->setVelocity(0.0);
  right_motor->setVelocity(0.0);
  // моторы выкл.
  
  
 DistanceSensor *right_ds = robot->getDistanceSensor("distance sensor2");
 DistanceSensor *front_ds = robot->getDistanceSensor("distance sensor3"); 
 DistanceSensor *yama_front_ds = robot->getDistanceSensor("distance sensor4"); 
 DistanceSensor *yama_right_ds = robot->getDistanceSensor("distance sensor1");
 // инициализация УЗ датчиков
 
 
  right_ds->enable(TIME_STEP);
  front_ds->enable(TIME_STEP);
  yama_front_ds->enable(TIME_STEP);
  yama_right_ds->enable(TIME_STEP);
 // подключение УЗ датчиков
  
  
  bool right_wall=false;
  bool front_wall=false;
  // объявление переменных, хранящих данные о наличии стен в текущий момент времени
  
  
  while (robot->step(TIME_STEP) != -1) {
  // основной цикл программы
  
    
    right_wall = (right_ds->getValue() < 0.17) || (yama_right_ds->getValue() > 0.3);
    front_wall = (front_ds->getValue() < 0.16) || (yama_front_ds->getValue() > 0.2);
    //получение и запись информации о наличии стен
//*     
  if (yama_right_ds->getValue() < 0.05) {
        left_speed =  -MAX_SPEED/8;
        right_speed = -MAX_SPEED/12;
  } else {
//*/  
  if (counter == 0){

    if (front_wall == true )
    {//если спереди стена
    
        if (right_wall == true)
        {//если стена и справа и спереди
        programm = 1;
        counter = COUNTER_90_DEG;
        cout<<1<<endl;
        }
        else
        {//если спереди стена, а справа нет
        programm = 2;
        counter = COUNTER_90_DEG;    
        cout<<2<<' '<<front_ds->getValue()<<endl;
        }
    }
    else 
    {//если спереди стены нет
    
        if (right_wall == true)
        {
        //если стена только справа
        
        programm = 3;
        counter = COUNTER_90_DEG; 
        cout<<3<<endl;
         }
         else {
         //если стен нет совсем *я свободеен*
         
        programm = 4;
        counter = COUNTER_90_DEG;
        cout<<4<<endl; 
         
        }
    }
    }else{
    
    counter--;
    switch (programm){
    
    case 1:
            left_speed =  -MAX_SPEED;
            right_speed = MAX_SPEED;
    break;
    
    case 2:
            left_speed =  MAX_SPEED*0.95;
            right_speed = -MAX_SPEED;  
    break;
    
    case 3:
            left_speed =  MAX_SPEED;
            right_speed = MAX_SPEED; 
    break;
    
    case 4:
            left_speed = MAX_SPEED;
            right_speed = MAX_SPEED; 
    break;
    }
    
    }
    }
    
    left_motor->setVelocity(left_speed);
    right_motor->setVelocity(right_speed);
    //установка нужных скоростей на моторы
  }


  delete robot;
  return 0;
}


  delete robot;
  return 0;
}
