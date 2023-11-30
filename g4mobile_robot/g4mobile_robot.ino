/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
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
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_ACCESS_PASSWORD "G40100"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 52 bytes
  { 255,4,0,0,0,45,0,16,8,0,2,0,2,1,22,11,6,27,31,31,
  79,78,0,79,70,70,0,10,49,4,45,15,15,6,26,31,90,0,31,79,
  70,70,0,5,1,61,30,30,30,6,26,31 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 
  int8_t joystick_x; // from -100 to 100  
  int8_t joystick_y; // from -100 to 100  

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 13
#define PIN_PUSHSWITCH_1 3


//define right motor control pins
#define right_motor_A 9
#define right_motor_B 10
#define right_motor_speed 7 //enable pin

//define left motor control pins
#define left_motor_A 11
#define left_motor_B 12
#define left_motor_speed 8 //enable pin

//define two arrays with a list of pins for each motor
uint8_t RightMotor[3] = {right_motor_A, right_motor_B, right_motor_speed};
uint8_t LeftMotor[3] = {left_motor_A, left_motor_B, left_motor_speed};

//speed control of motors
void Wheel (uint8_t * motor, int v) // v = motor speed, motor = pointer to an array of pins
{
    if (v > 100) v=100;
    if (v < -100) v=-100;
    if (v > 0){

        digitalWrite (motor [0], HIGH);
        digitalWrite (motor [1], LOW);
        analogWrite (motor [2], v * 2.55);
    }
    else if ( v<0 ){

        digitalWrite (motor [0], LOW);
        digitalWrite (motor [1], HIGH);
        analogWrite (motor [2], (-v) * 2.55);
    }
    else{
        digitalWrite (motor [0], LOW);
        digitalWrite (motor [1], LOW);
        analogWrite (motor [2], 0);
    }
}


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_PUSHSWITCH_1, OUTPUT);
  
  // TODO you setup code
  //initialization pins
    pinMode (right_motor_A, OUTPUT);
    pinMode (right_motor_B, OUTPUT);
    pinMode (left_motor_A, OUTPUT);
    pinMode (left_motor_B, OUTPUT);
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_1, (RemoteXY.pushSwitch_1==0)?LOW:HIGH);
  
 //manage the right motor
    Wheel (RightMotor, RemoteXY.joystick_y - RemoteXY.joystick_x);
    Wheel (LeftMotor, RemoteXY.joystick_y + RemoteXY.joystick_x);


}