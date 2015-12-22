#include "TimerOne.h"
 
void setup()
{
  pinMode(10, OUTPUT);
  Timer1.initialize(50000);         // initialize timer1, and set a 1/2 second period
  Timer1.pwm(9, 128);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}
 
void callback()
{
  //digitalWrite(10, digitalRead(10) ^ 1);
}
 
void loop()
{
  // your program here...
}
