#include <Servo.h>
#include <Stepper.h>
#include <LIDARLite.h>
#include <math.h>

/****************************************/
//Pin Connections on Arduino Uno Board   /
//Pin 9,10,11,12 : Stepper Motor output  /
//Pin A0,A1,A2   : Test Led(G,B,R) Resp. /
//Pin 6          : Servo data output     /
//Pin A4, A5     : Lidar data input      /
/****************************************/

//constant definitions
#define Steps 200

//component initialisation
Servo myservo;
Stepper myStepper(Steps,9,10,11,12);
LIDARLite myLidar;

//variable definitions
int servo_position =0; 
int Lidar_reading_count =0;
int timedelay = 50; //to be decided (in ms)
int servo_direction = 0;
int Stepper_position = 0; // 0=top, 180=bottom
String serial;
float dist;
int readingSum;
//function definitions

String toXYZ (float StepperPos, float ServoPos, float Radius, float Xinit, float Yinit,float Zinit )
{
  StepperPos=radians(StepperPos*1.8); //each step of stepper motor is 1.8deg
  ServoPos  =radians(ServoPos);
  String result="";
  float X=0,Y=0,Z=0,precision=0.01;
  Z=Radius*cos(ServoPos)+Zinit;
  Y=Radius*sin(ServoPos)*sin(StepperPos)+Xinit;
  X=Radius*sin(ServoPos)*cos(StepperPos)+Yinit;
  X-=fmod(X,precision);
  Y-=fmod(Y,precision);
  Z-=fmod(Z,precision);
  result=result+X +','+Y+','+Z;
  return result;
}

void led(void) 
{
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                       // wait for a 10 milliseconds
  digitalWrite(LED_BUILTIN, LOW);    
}

void setup() {
myservo.attach(6);
pinMode(LED_BUILTIN, OUTPUT); 
pinMode(12,OUTPUT);
pinMode(11,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9, OUTPUT);
Serial.begin(9600);
myLidar.reset();
myLidar.begin(0,true);//Sets configuration mode to 0:default (refer LIDARlite library), I2C speed to 400 kHz
myLidar.configure(2); //for checking alternate configurations
myStepper.step(1);
myStepper.step(1);
myStepper.step(1);
}

void loop() {
  //Todo : create Data input loops (most probably three : Rotating the stepper first, then sservo then input from lidar)
  //Todo : add stepper loop (Done)
  if(servo_position==-1){
    myStepper.step(1);
    Stepper_position++;
    servo_direction++;
    servo_position+=1;
    }
  if(servo_position==181){
    myStepper.step(1);
    Stepper_position++;
    servo_direction++;
    servo_position-=1;
    }
  //Todo : add servo loop (Done) 
 if(servo_direction%2==0){
    myservo.write(servo_position);
    delay(timedelay);
    servo_position ++;  
    }
  else{
    myservo.write(servo_position);
    delay(timedelay);
    servo_position--;
  }
  readingSum=0;
  for( int i=0; i<10;i++)
  {
    readingSum+=myLidar.distance();
  }
  dist=readingSum/10;
  serial=toXYZ(Stepper_position,servo_position,dist,0,0,0);
  Serial.println(serial); //Take a reading without bias correction
  Lidar_reading_count++;
  //Todo : add Lidar input loop (done) 
}
