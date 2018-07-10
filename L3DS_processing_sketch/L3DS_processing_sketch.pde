/*
Arduino to Processing 
  inspired from github location : Bitknitting/HealthypH/DataFiles/ASContinousRead/ContinousReadFromArduino/ContinousReadFromArduino.pde
*/

import processing.serial.*;  //importing serial library

int end = 10;  //end character for serial line, is copied from a code, needs to be rethought
String serial; //string for buffering dataline 
Serial port;   //instance of class serial. will designate our port, like COM5   
PrintWriter Output;  //instance of class Printwriter to assign a txt file;
float x=0,y=0,z=0;
void setup()
{
  size(1000,1000,P3D);
  background(0);
  String portName = "COM3";  //string for storing name of port used
  port = new Serial(this, portName,2400);  //attaching serial monitor to port
  port.clear();  //clearing any data taken from arduino monitor until this line
  Output = createWriter("file3.txt");  //attaching text file for output
  serial=port.readStringUntil(end);  //function reads from serial monitor and attaches it to string serial
  serial = null; //empty initialisation 
}  
 void draw()
{
  camera(mouseX, height/2, (height/2) / tan(PI/6), width/2, height/2, 0, 0, 1, 0);
  fill(127);
  while(port.available() > 0) //as long as data comes from serial monitor 
  {
    serial = port.readStringUntil(end);
    /**String[] cord = split( serial , ",");
    x=Integer.parseInt(cord[0]);
    y=Integer.parseInt(cord[1]);
    z=Integer.parseInt(cord[2]);
    point(x,y,z);*/
    if(serial!=null) //if string is not empty, write it to file;
  {
    Output.print(serial);
    println(serial);
    serial = null;
  }    
  }
}  
void keyPressed()
{
  Output.flush(); //write remaining data to file
  Output.close(); //Finish the file
  exit();
}
