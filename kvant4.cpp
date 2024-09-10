#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <webots/Camera.hpp>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
//бибилиотеки


using namespace std;
using namespace webots;
using namespace cv;
//инициализация команд


#define TIME_STEP 64
#define MAX_SPEED 5.8
#define COUNTER_90_DEG 3
//константы
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int areaSize = 800;
using namespace cv;
using namespace std;
Mat img;
Mat imgHSV, mask;
VideoCapture cap(0);
char c;

//Import IMG
/*Mat img;
Mat imgHSV,mask;
int hmin=33, smin=86, vmin=0;
int hmax=97, smax=166, vmax=76;
*/

  Robot *robot = new Robot();
//  инициализация робота
 
  
double left_speed = MAX_SPEED;
double right_speed = MAX_SPEED;
// объявление переменных, хранящих значение скоростей УЗ датчиков

int counter = 0;
int programm = 1;
  
  
int main(int argc, char **argv) {

Camera* camera = robot->getCamera("camera1");
camera->enable(TIME_STEP);

//основная программа
  
/*VideoCapture cap(2);
cap.read(img);
	

cvtColor(img,imgHSV,COLOR_BGR2HSV);

namedWindow("Trackbars", (640,200));
createTrackbar("Hue Min", "Trackbars", &hmin, 179);
createTrackbar("Hue Max", "Trackbars", &hmax, 179);
createTrackbar("Saturation Min", "Trackbars", &smin, 255);
createTrackbar("Saturation", "Trackbars", &smax, 255);
createTrackbar("Value Min", "Trackbars", &vmin, 255);
createTrackbar("Value Max", "Trackbars", &vmax, 255);
char c;*/
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
  
  img(camera->getHeight(), camera->getWidth(), CV_8UC4, (void*)camera->getImage());
    
    imshow("frame", img);
    
    cvtColor(img,img,COLOR_BGR2GRAY); // grayscale
    imshow("grayScale", img);
    
/*    cap.read(img);
	GaussianBlur(img, img, Size(9,9), 5.0);
	img = 255 - img;
Scalar lower(hmin, smin, vmin);
Scalar upper(hmax, smax, vmax);
inRange(img,lower,upper,mask);
	
	imshow("Image",img);
	imshow("Image HSV",imgHSV);
	imshow("Image Mask", mask); 
	c = waitKey(1);*/
	
    right_wall = (right_ds->getValue() < 0.1) || (yama_right_ds->getValue() > 0.3);
    front_wall = (front_ds->getValue() < 0.1) || (yama_front_ds->getValue() > 0.3);
    //получение и запись информации о наличии стен
//*     6
  if (yama_right_ds->getValue() < 0.05) {
        left_speed =  -MAX_SPEED/8;
        right_speed = -MAX_SPEED/12;
  } else {
          cout<<2<<' '<<yama_right_ds->getValue()<<endl;
//*/  
  if (counter == 0){

    if (front_wall == true )
    {//если спереди стена
    
        if (right_wall == true)
        {//если стена и справа и спереди
        programm = 1;
        counter = 8;
        cout<<1<<endl;
        }
        else
        {//если спереди стена, а справа нет
        programm = 2;
        counter = COUNTER_90_DEG;    

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
    waitKey(1);
  }


  delete robot;
  return 0;
}