/* The sketch below is for controlling a Orrery that was deisgned for the Otago Museum by the students of Otago Polytechnic.
 *  This project was done in the second semester of 2022 and was part of the mechanical design 2 paper.
 *  The sketch uses if statements and interrupt commands and also uses an app to control the variable used in the sketch.
 * Please refer the below link which has the data sheet of the parallax 360 servo which will help to understand the coding used to do the feedback part of the servo
 * https://www.pololu.com/file/0J1395/900-00360-Feedback-360-HS-Servo-v1.2.pdf
 * Other references 
 * https://github.com/HyodaKazuaki/Parallax-FeedBack-360-Servo-Control-Library-4-Arduino/releases

 created 21st November 2022
 by Lakshminarayanan Kuruchi Venkatachalam (Lux)

   -- Orrery 4 --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 432 bytes
  { 255,16,0,11,0,169,1,16,31,5,4,144,14,47,37,10,1,2,26,1,
  0,42,49,10,10,2,2,31,0,3,131,15,19,33,12,0,2,26,67,4,
  29,11,24,7,0,2,26,11,129,0,11,12,16,5,0,17,77,79,68,69,
  58,0,7,52,30,40,20,5,2,2,26,2,1,0,12,49,10,10,2,2,
  31,0,131,1,36,80,24,7,1,2,31,65,117,116,111,0,131,0,3,80,
  27,7,2,2,16,83,101,109,105,32,65,117,116,111,0,131,0,17,90,32,
  7,3,2,31,77,97,110,117,97,108,32,74,111,103,0,1,0,3,40,12,
  12,3,2,31,0,1,0,18,40,12,12,3,2,31,0,1,0,33,40,12,
  12,3,2,31,0,1,0,4,56,12,12,3,2,31,0,1,0,35,56,12,
  12,3,2,31,0,1,0,20,56,12,12,3,2,31,0,129,0,3,36,10,
  4,3,17,69,97,114,116,104,0,129,0,18,35,10,4,3,17,77,111,111,
  110,0,129,0,31,35,15,4,3,17,77,101,114,99,117,114,121,0,129,0,
  4,69,12,4,3,17,86,101,110,117,115,0,129,0,21,69,9,4,3,17,
  77,97,114,115,0,129,0,37,69,7,4,3,17,83,117,110,0,129,0,9,
  62,19,3,2,17,76,117,110,97,114,32,69,99,108,105,112,115,101,0,129,
  0,37,62,18,3,2,17,83,111,108,97,114,32,69,99,108,105,112,115,101,
  0,1,0,49,40,12,12,3,2,31,0,1,0,49,56,12,12,3,2,31,
  0,129,0,52,69,5,4,3,17,65,108,108,0,129,0,50,35,11,4,3,
  17,69,115,112,105,110,0,129,0,14,38,35,6,1,17,83,112,101,101,100,
  32,83,108,105,100,101,114,0,130,1,0,249,63,16,0,17,129,0,3,2,
  57,5,0,31,79,82,82,69,82,89,32,67,79,78,84,82,79,76,76,69,
  82,0,7,53,22,74,20,5,3,2,26,2 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t Speed_var; // =0..100 slider position 
  uint8_t position_SolarEclipse; // =1 if button pressed, else =0 
  uint8_t modeSelector; // =0 if select position A, =1 if position B, =2 if position C, ... 
  int16_t Target_Angle;  // 32767.. +32767 
  uint8_t position_LunarEclipse; // =1 if button pressed, else =0 
  uint8_t EarthServo; // =1 if button pressed, else =0 
  uint8_t MoonServo; // =1 if button pressed, else =0 
  uint8_t MercuryServo; // =1 if button pressed, else =0 
  uint8_t VenusServo; // =1 if button pressed, else =0 
  uint8_t SunServo; // =1 if button pressed, else =0 
  uint8_t MarsServo; // =1 if button pressed, else =0 
  uint8_t earthSpinServo; // =1 if button pressed, else =0 
  uint8_t All; // =1 if button pressed, else =0 
  int16_t ManualSpeed;  // 32767.. +32767 

    // output variables
  char mode[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#include <Servo.h>
//declaring all servos
Servo earthArm;
Servo earthSpin;
Servo mercury;
Servo venus;
Servo moon;
Servo mars;
Servo sun;
int modeSelector;
int SpeedValue;
int lastSpeedValue;
volatile float angle, targetAngle;
volatile float angle2, targetAngle2;
volatile float angle3, targetAngle3;
int theta = 0, thetaP = 0;
int theta2 = 0, thetaP2 = 0;
int theta3 = 0, thetaP3 = 0;
volatile unsigned long tHigh = 0, tLow = 0;
volatile unsigned long tHigh2 = 0, tLow2 = 0;
volatile unsigned long tHigh3 = 0, tLow3 = 0;
volatile unsigned long rise = 0, fall = 0;
volatile unsigned long rise2 = 0, fall2 = 0;
volatile unsigned long rise3 = 0, fall3 = 0;
volatile float dc;
volatile float dc2;
volatile float dc3;
volatile int tCycle;
volatile int tCycle2;
volatile int tCycle3;
int turns = 0;
int turns2 = 0;
int turns3 = 0;
int Kp = 0.1;
int Kp2 = 0.1;
int Kp3 = 0.1;
int unitsFC = 360;
int unitsFC2 = 360;
int unitsFC3 = 360;
float dcMin = 0.029;
float dcMin2 = 0.029;
float dcMin3 = 0.029;
float dcMax = 0.971;
float dcMax2 = 0.971;
float dcMax3 = 0.971;
float dutyScale = 1.0;
float dutyScale2 = 1.0;
float dutyScale3 = 1.0;
float q2min = unitsFC / 4.0;
float q2min2 = unitsFC / 4.0;
float q2min3 = unitsFC / 4.0;
float q3max = q2min * 3.0;
float q3max2 = q2min * 3.0;
float q3max3 = q2min * 3.0;





void setup() 
{
  RemoteXY_Init (); 
  // put your setup code here, to run once:
    
  earthArm.attach(5);
  earthSpin.attach(6);
  moon.attach(7);
  venus.attach(8);
  mercury.attach(9);
  mars.attach(10);
  sun.attach(11);
  RemoteXY.modeSelector=0; // making sure it goes into manual mode when it starts up
  RemoteXY.ManualSpeed=1400;// setting the manual speed. the number starts from 1490. 1490 the servo will be statiionery.
  Serial.begin(115200);
   Serial.print(" Mode : ");
  Serial.println(modeSelector); //this allows the mode to be seen in the app.
    delay(1000);  
}

void loop() 
// put your main code here, to run repeatedly:

{ RemoteXY_Handler ();                    // this is to start the loop of the remote xy app which works through the wifi module       
    if (RemoteXY.modeSelector == 2){     // from sketch line 183 to 267, the code between these lines is executed only when it is semi auto mode in the app  
      strcpy (RemoteXY.mode,"Semi-Auto"); // if the mode selector value is 2 it displays Semi-Auto in the app
      /* declaring attach interrupt
      interrupt pin o is digital pin 2 
      interrupt pin 1 is digital pin 3 
      interrupt pin 2 is digital pin 18
      interrupt feature works in a way in which when it notices a change it instantaneously gets out of the void loop and reads the assosciated ISR (Interrupt service routine).
      In this sketch, the ISR are named as feedbackEarth, feedbackMoon and feedbackEarthAxis those assosciated loop function is written in the later part of the sketch.
      If there is a change detected in the interrupt pin the processor will jump out of the void loop and will execute the code in the assosciated ISR.
      For example if there is a change detected in interrupt pin which is digital pin 2 instantaneously it will jump out of the void loop and will execute the feedbackEarth(see sketch line 376)
      function from this setch, once it finishes executing that it will comeback and continue the void loop. 
       */
    attachInterrupt(0,feedbackEarth, CHANGE);
  attachInterrupt(1, feedbackMoon, CHANGE);
  
  /* these are variables used for doing the feeback control. Target angle value is the commanded value that you command the servo to go to. 
   *  error angle is the difference between the current value and commanded value
   */ 
  int errorAngle, output, offset, value;
  targetAngle = 5000;
  int errorAngle2, output2, offset2, value2;
  targetAngle2 = 5000;
  int errorAngle3, output3, offset3, value3;
  targetAngle3 = 2500;


  Serial.print(" Angle: ");
  Serial.println(angle);
  Serial.print(" Angle2: ");
  Serial.println(angle2);
   Serial.print(" Angle3: ");
  Serial.println(angle3);
   Serial.print(" Turn Count1: ");
  Serial.println(turns);
  Serial.print(" Turn Count 2: ");
  Serial.println(turns2);
   Serial.print(" Turn Count 3: ");
  Serial.println(turns3);


  errorAngle = targetAngle - angle;
  output = errorAngle * Kp;
  if(output > 200)
    output = 200;
  if(output < -200)
    output = -200;
  if(errorAngle > 0)
    offset = 30;
  else if(errorAngle < 0)
    offset = -30;
  else
    offset = 0;
  value = (abs(errorAngle) < 4) ? 0 : output + offset;
  earthArm.writeMicroseconds(1490 - value);
  
  errorAngle2 = targetAngle2 - angle2;
  output2 = errorAngle2 * Kp2;
  if(output2 > 200)
    output2 = 200;
  if(output2 < -200)
    output2 = -200;
  if(errorAngle2 > 0)
    offset2 = 30;
  else if(errorAngle2 < 0)
    offset2 = -30;
  else
    offset2 = 0;
  value2 = (abs(errorAngle2) < 4) ? 0 : output2 + offset2;
  earthSpin.writeMicroseconds(1490 - value2);

   errorAngle3 = targetAngle3 - angle3;
  output3 = errorAngle3 * Kp3;
  if(output3 > 200)
    output3 = 200;
  if(output3 < -200)
    output3 = -200;
  if(errorAngle3 > 0)
    offset3 = 30;
  else if(errorAngle3 < 0)
    offset3 = -30;
  else
    offset3 = 0;
  value3 = (abs(errorAngle3) < 4) ? 0 : output3 + offset3;
  moon.writeMicroseconds(1490 - value3);
  
  }
 else if (RemoteXY.modeSelector==1){ // the following code is for the Auto mode in which the planets will continously move like the solar system the only thing that will be controllable in this mode will be the speed.
  strcpy (RemoteXY.mode,"Auto"); 
 RemoteXY.Speed_var = SpeedValue;
 //mapping the Speed_var variable from the app which is in the range of 0 to 100 to the fast and slow speed range of the servos. the fast and slow speed value were obtained through testing. 
int Speed_Mercury = map(SpeedValue,0,100,1432,1395);
int Speed_Venus = map(SpeedValue,0,100,1456,1436);
int Speed_EarthArm = map(SpeedValue,0,100,1472,1460);
int Speed_Mars = map(SpeedValue,0,100,1475,1469);
int Speed_Sun = map(SpeedValue,0,100,1300,1150);
int Speed_Moon = map(SpeedValue,0,100,1518,1525);
int Speed_Espin = map(SpeedValue,0,100,1550,1570);

 
 earthArm.writeMicroseconds( Speed_EarthArm ); // writing the speed value to the servos 
 earthSpin.writeMicroseconds(Speed_Espin);
 moon.writeMicroseconds(Speed_Moon);
 mercury.writeMicroseconds(Speed_Mercury);
 venus.writeMicroseconds(Speed_Venus);
 mars.writeMicroseconds(Speed_Mars);
 sun.writeMicroseconds(Speed_Sun);
 
}
else if (RemoteXY.modeSelector==0){ // the following code is for the manual mode.
  /*In this mode everything will remain stationery until the assosciated button is pressed and once the assosciated button is pressed, 
   * it will generate a pulse to move the servo addressed in the code 
   */
  strcpy (RemoteXY.mode,"Manual"); // displays manual 

   if(RemoteXY.All==1){
    earthSpin.writeMicroseconds(RemoteXY.ManualSpeed);
    earthArm.writeMicroseconds(RemoteXY.ManualSpeed);
    moon.writeMicroseconds(RemoteXY.ManualSpeed);
    mercury.writeMicroseconds(RemoteXY.ManualSpeed);
    venus.writeMicroseconds(RemoteXY.ManualSpeed);
    sun.writeMicroseconds(RemoteXY.ManualSpeed);
    mars.writeMicroseconds(RemoteXY.ManualSpeed);}
    else {earthSpin.writeMicroseconds(1490);   // 1490 value means it wont move as it is like 0.
          earthArm.writeMicroseconds(1490);
          moon.writeMicroseconds(1490);
          mercury.writeMicroseconds(1490);
          venus.writeMicroseconds(1490);
          sun.writeMicroseconds(1490);
          mars.writeMicroseconds(1490);}
 
  if(RemoteXY.earthSpinServo==1){
    earthSpin.writeMicroseconds(RemoteXY.ManualSpeed); }
    else {earthSpin.writeMicroseconds(1490);}
    
  if(RemoteXY.EarthServo==1){
    earthArm.writeMicroseconds(RemoteXY.ManualSpeed); }
    else {earthArm.writeMicroseconds(1490);}
  
  if (RemoteXY.MoonServo==1) {
   moon.writeMicroseconds(1400);}
   else {moon.writeMicroseconds(1490);}
   
   if(RemoteXY.MercuryServo==1) {
  mercury.writeMicroseconds(RemoteXY.ManualSpeed);}
  else {mercury.writeMicroseconds(1490);}
   
   if(RemoteXY.VenusServo==1) {
   venus.writeMicroseconds(RemoteXY.ManualSpeed);}
   else {venus.writeMicroseconds(1490);}
   
   if(RemoteXY.SunServo==1) {
   sun.writeMicroseconds(RemoteXY.ManualSpeed);}
   else {sun.writeMicroseconds(1490);}
   
   if (RemoteXY.MarsServo==1) {
   mars.writeMicroseconds(RemoteXY.ManualSpeed);}
   else {mars.writeMicroseconds(1490);}

 
}
}
/* the following function loops named as feedbackMoon, feedbackEarth and feedbackEarthAxis are Interrupt Service Routine that are used for interrupt command to do its function
 *  the entire coding is just a technique to calculate the current position of the servo from its hall sensor.  
 *  Please refer the parallax 360 servo data sheet to properly understand the following code. 
 */
 void feedbackMoon() {
  if(digitalRead(3)) {
    // rise
    rise2 = micros();
    tLow2 = rise2 - fall2;

    // Calcuate duty
    tCycle2 = tHigh2 + tLow2;
    if((tCycle2 < 1000) && (tCycle2 > 1200))
      return;
    
    dc2 = (dutyScale2 * tHigh2) / (float)tCycle2;
    theta2 = ((dc2 - dcMin2) * unitsFC2) / (dcMax2 - dcMin2);
  
    if(theta2 < 0)
      theta2 = 0;
    else if(theta2 > (unitsFC2 - 1))
      theta2 = unitsFC2 - 1;
  
    if((theta2 < q2min2) && (thetaP2 > q3max2))
      turns2++;
    else if((thetaP2< q2min2) && (theta2 > q3max2))
      turns2--;
  
    if(turns2 >= 0)
      angle2 = (turns2 * unitsFC2) + theta2;
    else if(turns2 < 0)
      angle2 = ((turns2 + 1) * unitsFC2) - (unitsFC2 - theta2);
  
    thetaP2 = theta2;
  
  } else {
    // fall
    fall2 = micros();
    tHigh2 = fall2 - rise2;
  }
}
void feedbackEarth() {
  if(digitalRead(2)) {
    // rise
    rise = micros();
    tLow = rise - fall;

    // Calcuate duty
    tCycle = tHigh + tLow;
    if((tCycle < 1000) && (tCycle > 1200))
      return;
    
    dc = (dutyScale * tHigh) / (float)tCycle;
    theta = ((dc - dcMin) * unitsFC) / (dcMax - dcMin);
  
    if(theta < 0)
      theta = 0;
    else if(theta > (unitsFC - 1))
      theta = unitsFC - 1;
  
    if((theta < q2min) && (thetaP > q3max))
      turns++;
    else if((thetaP < q2min) && (theta > q3max))
      turns--;
  
    if(turns >= 0)
      angle = (turns * unitsFC) + theta;
    else if(turns < 0)
      angle = ((turns + 1) * unitsFC) - (unitsFC - theta);
  
    thetaP = theta;
  
  } else {
    // fall
    fall = micros();
    tHigh = fall - rise;
  }
  
  
}
