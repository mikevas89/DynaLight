#define ledPin 13
int count = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);

  // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;


  // 2Hz = 15625 =   256
  //100Hz = 312    256
  //200Hz = 156    256
  //400Hz = 78   256
  //800Hz = 39   256
  Serial.begin(115200);


  int freq = 3000;

  int value = 16000000 / 256 /  freq / 2;
  Serial.print(value);
  Serial.print(" ");


  OCR1A = value;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler
  //TCCR1B |= (1 << CSHIGH12) | (1 << CS10); // 1024 prescaler


  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin



}

void loop()
{
  // your program here...
}
