
int ledPin = 13;      // LED connected to digital pin 9


void setup()

{

  pinMode(ledPin, OUTPUT);   // sets the pin as output

  int myEraser = 7;             // this is 111 in binary and is used as an eraser
  TCCR0B &= ~myEraser;   // this operation (AND plus NOT),  set the three bits in TCCR2B to 0
  
  int myPrescaler = 5;         // this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.
  TCCR0B |= myPrescaler;  //this operation (OR), replaces the last three bits in TCCR2B with our new value 011

  analogWrite(ledPin, 128);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255


}



void loop()

{



}

