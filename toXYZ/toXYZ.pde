/*
spherical to cartesian coordinate function 
*/

String toXYZ(float StepperPos, float ServoPos, float Radius)
{
  StepperPos=radians(StepperPos);
  ServoPos  =radians(ServoPos);
  String result="";
  float X=0,Y=0,Z=0;
  Z=Radius*cos(ServoPos);
  Y=Radius*sin(ServoPos)*sin(StepperPos);
  X=Radius*sin(ServoPos)*cos(StepperPos);
  X-=(X%0.01);
  Y-=(Y%0.01);
  Z-=(Z%0.01);
  result=result+X +','+Y+','+Z+'\n';
  return result;
}
void setup()
{
  size(400,400);
    print(toXYZ(90,30,100));
}
