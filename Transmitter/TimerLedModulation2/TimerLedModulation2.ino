#define ledPin 2

void setup()
{
  pinMode(10, OUTPUT);
  
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

}



void loop()
{
  // your program here...
}
