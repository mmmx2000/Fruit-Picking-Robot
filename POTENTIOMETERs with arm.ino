#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;


 
 // Define Potentiometer Inputs

 #define controlShoulder  A0
 #define controlBase  A1
 #define controlElbow  A2
 #define controlWrist  A3
 #define controlPivot  A4
 #define controlJaws  A5

 // Define Motor Outputs on PCA9665 board

 int motorShoulder = 5;
 int motorBase = 3;
 int motorElbow = 6;
 int motorWrist = 9;
 int motorPivot = 10;
 int motorJaws = 11;

 // Define Motor position variables
 int mtrDegreeShoulder;
 int mtrDegreeBase;

 int mtrDegreeElbow;
 int mtrDegreeWrist;
 int mtrDegreePivot;
 int mtrDegreeJaws;

 void setup()
 {
  Serial.begin(9600);

  myservo1.attach(motorShoulder);  // (pin)
  myservo2.attach(motorBase);  // (pin)
  myservo3.attach(motorElbow);  // (pin)
  myservo1.attach(motorWrist);  // (pin)
  myservo2.attach(motorPivot);  // (pin)
  myservo3.attach(motorJaws);  // (pin)
 
 }
 void loop() {


  Serial.print("A0:");
  Serial.println(analogRead(controlShoulder));

  Serial.print("A1:");
  Serial.println(analogRead(controlBase));

  Serial.print("A2:");
  Serial.println(analogRead(controlElbow));

  Serial.print("A3:");
  Serial.println(analogRead(controlWrist));

  Serial.print("A4:");
  Serial.println(analogRead(controlPivot));

  Serial.print("A5:");
  Serial.println(analogRead(controlJaws));
 //Control Shoulder Motor

 // Get desired position
 mtrDegreeShoulder = getDegree(analogRead(controlShoulder));
 // Move motor
 myservo1.write(mtrDegreeShoulder);

//Control Base Motor

 // Get desired position
 mtrDegreeBase = getDegree(analogRead(controlBase));
 // Move motor

 myservo2.write(mtrDegreeBase);


 //Control Elbow Motor

 // Get desired position
 mtrDegreeElbow = getDegree(analogRead(controlElbow));
 // Move motor
 
 myservo3.write(mtrDegreeElbow);



 //Control Wrist Motor

 // Get desired position
 mtrDegreeWrist = getDegree(analogRead(controlWrist));
 // Move motor
 
 myservo4.write(mtrDegreeWrist);


 //Control Pivot Motor

 // Get desired position
 mtrDegreePivot = getDegree(analogRead(controlPivot));
 // Move motor
 
 myservo5.write(mtrDegreePivot);


 //Control Jaws Motor

 // Get desired position
 mtrDegreeJaws = getDegree(analogRead(controlJaws));
 // Move motor
 
 myservo6.write(mtrDegreeJaws);


 // Add short delay
 delay(5);

 }


 // Function to convert potentiometer position into servo angle
 int getDegree(int potVal)
 {
 int srvDegree;

 // Read values from potentiometer
 //potVal = analogRead(controlIn);

 // Calculate angle in degrees
 srvDegree = map(potVal, 0, 1023, 0, 180);

 // Return angle in degrees
 return srvDegree;

 }
