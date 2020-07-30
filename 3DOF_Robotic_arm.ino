#include <Servo.h>
Servo motor1;
Servo motor2;
Servo motor3;

 // length of each link (arm)  
float L1;
float L2;
float L3;


float pi = 3.14159265359;


void setup() {
  motor1.attach(3);
  motor2.attach(5);
  motor3.attach(6);
  Serial.begin(9600);
  motor1.write(0);
  motor2.write(0);
  motor3.write(0);
 Serial.println("Enter the length of the first arm L1");
 while(Serial.available()==0){}
 L1=Serial.parseFloat();
 Serial.print("L1 is "); 
 Serial.println(L1);
   
 Serial.println("Enter the length of the second arm L2");
 while(Serial.available()==0){}
 L2=Serial.parseFloat();
 Serial.print("L2 is "); 
 Serial.println(L2);

 Serial.println("Enter the length of the third arm L3");
 while(Serial.available()==0){}
 L3=Serial.parseFloat();
 Serial.print("L3 is "); 
 Serial.println(L3);
 
Serial.println("Enter Number 1 for ForwardKinematics");
Serial.println("Enter Number 0 for inverseKinematics");   }

void loop() {

 if (Serial.available())  {
 
    char choice = Serial.read();
    if (choice == '1'){  

  motor1.write(0);
  motor2.write(0);
  motor3.write(0);             
    ForwardKinematics();
 }
 
else if(choice == '0')

{
  motor1.write(0);
  motor2.write(0);
  motor3.write(0);
 inverseKinematics();
 }
 

 }
 }


 void ForwardKinematics(){
         // angles between links of robot arm
float angle1 ;
float angle2;
float angle3;
float angleTotal;      
 
float radAngle1;
float radAngle2;
float radAngle3;
float radAngleTotal;

// to compute end effector
float x;      
float y;
float x1;
float x2;
float y1;
float y2;             
  Serial.println("Enter angle1 ");
  while(Serial.available()==0){}
  angle1=Serial.parseFloat();
  Serial.print("angle1 = "); 
  Serial.println(angle1);
  
  Serial.println("Enter angle2 ");
  while(Serial.available()==0){}
  angle2=Serial.parseFloat();
  Serial.print("angle2 = "); Serial.println(angle2);

  Serial.println("Enter angle3 ");
  while(Serial.available()==0){}
  angle3=Serial.parseFloat();
  Serial.print("angle3 = "); Serial.println(angle3);

  radAngle1 = (angle1*pi)/180;    
  radAngle2 = (angle2*pi)/180;
  radAngle3 = (angle3*pi)/180;
  radAngleTotal = (angleTotal*pi)/180;
  
  motor1.write(angle1); 
  motor2.write(angle2);
  motor3.write(angle3);
  
  x = L1 * cos(radAngle1) +L2 * cos(radAngle1 + radAngle2) + L3 * cos(radAngle1 + radAngle2 + radAngle3);
  y = L1 * sin(radAngle1) +L2 * sin (radAngle1 + radAngle2)+ L3 * sin (radAngle1 + radAngle2 + radAngle3);
  angleTotal = angle1 + angle2 + angle3;
   delay(1000);    

  
 Serial.print("x is "); Serial.println(x);
 Serial.print("y is = "); Serial.println(y); 
 Serial.print("Total angle is "); Serial.println(angleTotal);
 Serial.print("angle1 "); Serial.println(angle1);
 Serial.print("angle2 "); Serial.println(angle2);
 Serial.print("angle3 "); Serial.println(angle3);
Serial.println("Enter Number 1 for ForwardKinematics");
Serial.println("Enter Number 0 for inverseKinematics");


 }

 void inverseKinematics(){
     // angles between links of robot arm
float angle1 ;
float angle2;
float angle3;
float angleTotal;      
 
float radAngle1;
float radAngle2;
float radAngle3;
float radAngleTotal;

// to compute end effector
float x;      
float y;
float x1;
float x2;
float y1;
float y2; 
Serial.println("Enter the value x ");
      while(Serial.available()==0){}
      x=Serial.parseFloat();
      Serial.print("x is "); Serial.println(x);
      
      Serial.println("Enter the value y ");
      while(Serial.available()==0){}
      y=Serial.parseFloat();
      Serial.print("y is "); Serial.println(y);

      Serial.println("Enter the Total Angle");
      while(Serial.available()==0){}
      angleTotal=Serial.parseFloat();
      Serial.print("total angle is  ");Serial.println(angleTotal);
      
  radAngleTotal = (angleTotal*pi)/180;
  x2=x-L3*cos(radAngleTotal);
  y2=y-L3*sin(radAngleTotal);   
  radAngle2 = acos((sq(x2)+ sq(y2) - sq(L1) - sq(L2)) / (2*L1*L2));
  radAngle1= acos(((L1 + L2 * cos(radAngle2))*x2+(L2 * y2 * sin(radAngle2))) / (sq(x2)+ sq(y2)));

      angle1= (radAngle1*180)/pi;
      angle2= (radAngle2*180)/pi;
      angle3= angleTotal-angle1-angle2;
       delay(1000);    

      motor1.write(angle1); 
      motor2.write(angle2);
      motor3.write(angle3);
      x1 = L1 * cos(radAngle1) ;
      y1 = L1 * sin(radAngle1) ;
  
 Serial.print("angle1 is "); Serial.println(angle1);
 Serial.print("angle2 is "); Serial.println(angle2);
 Serial.print("angle3 is "); Serial.println(angle3);
 
 
Serial.println("Enter Number 1 for ForwardKinematics");
Serial.println("Enter Number 0 for inverseKinematics");
 }