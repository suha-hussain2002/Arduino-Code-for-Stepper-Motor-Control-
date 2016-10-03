/**************************************************************************************************************
 * Libraries
 **************************************************************************************************************/
#include <LiquidCrystal.h>
//Libraries for the ID Chips
#include <Usb.h>
/**************************************************************************************************************
 * Definitions
 **************************************************************************************************************/
//Define Motor Specs
#define MOTOR_SPEED .05 //0.05 max // speed is any number from .01 -> 0.1 with 1 being fastest; Slower is stronger 
#define NEMA23 -1    //degrees per step 0.9
#define NEMA17 -1    //degrees per step 1.8
#define START_PREAMBLE 0x31   // '1'
#define END_PREAMBLE 0x5B     //  '['
#define CLOCKWISE_CMD 0X43 //C
#define COUNTERCLOCKWISE_CMD 0X52 //R

/**************************************************************************************************************
 * TXC Pin Mapping 
 **************************************************************************************************************/

//Stepper Controllers

int sleep_pin= 29;
int step_pin = 23;
int dir_pin = 22;
int reset_pin = 24;
int enable_pin = 28;
int MS1_pin = 27;
int MS3_pin = 25;
int MS2_pin = 26;
int switch_pin = 42; 

// defines pins
   
char rcvmsg[10]; 
// creates a reciever array
  
/*******************************************************
 * Loop through the drivers to initialize the pins
 * and set to sleep
 *******************************************************/
void initialize()
{
   // intializing the pins (input/output vs high/low) 
    pinMode(sleep_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(reset_pin,OUTPUT);
    pinMode(enable_pin, OUTPUT);
    pinMode(MS1_pin, OUTPUT);
    pinMode(MS3_pin, OUTPUT);
    pinMode(MS2_pin, OUTPUT);
    pinMode(step_pin, OUTPUT);
    pinMode (switch_pin, INPUT); 
    
    digitalWrite(reset_pin,HIGH);
    digitalWrite(sleep_pin, LOW); 
    digitalWrite(MS1_pin,LOW);
    digitalWrite(MS3_pin,LOW);
    digitalWrite(MS2_pin,LOW);
    digitalWrite(enable_pin, LOW);
    
   //Delay 50 microsecond
    delay(50);
    Serial.setTimeout(200);
}
/***********************************************************************************************************
 * Initialization
 ***********************************************************************************************************/
void setup()  
{
  Serial.begin(9600);  
  // sets up serial ports
  initialize();
}

/************************************************************************************************************
 * Main Loop
 *   
 *************************************************************************************************************/
void loop() 
{
   boolean x;
   int steps=2000;
   int len = 10; 
   int i;
   char command; 
 
   while (Serial.readBytes(rcvmsg,4) <2)
   {
   // defines variables/data // 
     if (len >= 2)
     {
     if (rcvmsg[0] == START_PREAMBLE)
        {
          Serial.println("Test1");  
          if (rcvmsg[1] == END_PREAMBLE)
            {
                Serial.println("Test2");  
                command = rcvmsg[2];
                for (i=0; i<10; i++)
                {
                  Serial.println(rcvmsg[i]);  
                }
            }
        }  
        Serial.print("COMMAND IS: ");  
        Serial.print(command);   
        Serial.println(" meow");      
       
        switch (command)
            {
            case CLOCKWISE_CMD:
               rotate_clockwise(steps);
              break;
            case COUNTERCLOCKWISE_CMD:
                rotate_counterclockwise(steps);
              break;      
             }
     }
   }
}
// picks the direction of movement 
// defines each direction
void rotate_clockwise(int steps) 
{
   int i;
   int y=70;
   float usDelay;  
    digitalWrite(sleep_pin, HIGH); 
    digitalWrite(dir_pin, HIGH);

   for (i=0; i<steps ; i++) 
   {
     usDelay = (1/MOTOR_SPEED)*y; 
     digitalWrite(step_pin,HIGH);
     delayMicroseconds(usDelay);

     digitalWrite(step_pin,LOW);
     delayMicroseconds(usDelay);  
 //     y=y-1;
   } 
}

void rotate_counterclockwise(int steps) 
{
   int i;
   float usDelay;
   int y=70;
   
     digitalWrite(sleep_pin, HIGH); 
     digitalWrite(dir_pin, LOW);

   for (i=0; i<steps; i++) 
   {
     usDelay = (1/MOTOR_SPEED)*y; 
     digitalWrite(step_pin,HIGH);
     delayMicroseconds(usDelay);

     digitalWrite(step_pin,LOW);
     delayMicroseconds(usDelay);
//    y=y-1;
}
}
