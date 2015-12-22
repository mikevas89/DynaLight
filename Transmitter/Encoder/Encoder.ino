int incomingByte = 0;   // for incoming serial data
int createCode = 0;
int interruptCounter = 0;
int toogleCounter = 0;
int ledPin = 13;
int count = 0;

int bit0ON;
int bit0OFF;
int bit1ON;
int bit1OFF;

void setup() {

  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  initializeTimer();


}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if (createCode == 0) {
    if (digitalRead(ledPin == HIGH))
    {
      digitalWrite(ledPin, LOW);
    } else {
      digitalWrite(ledPin, HIGH);
    }

  }
  else {
    count++;
    if (count == 13) {
      count = 1;
    }

    if (count == 1 || count == 3 || count == bit0ON || count == bit1ON ) {

      digitalWrite(ledPin, HIGH);   // toggle LED pin
    }
    else if (count == 2 || count == 4 || count == bit0OFF || count == bit1OFF) {
      digitalWrite(ledPin, LOW);   // toggle LED pin
    }

  }

}


void loop() {


  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read() - '0';

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);


    //create bits
    switch (incomingByte) {
      case 0:
        createCode = 0;
        count = 0;
        break;
      case 1:
        bit0ON = 5;
        bit0OFF = 8;
        bit1ON = 9;
        bit1OFF = 12;
        createCode = 1;

        break;
      case 2:
        bit0ON = 5;
        bit0OFF = 8;
        bit1ON = 9;
        bit1OFF = 10;
        createCode = 1;
        break;
      case 3:
        bit0ON = 5;
        bit0OFF = 6;
        bit1ON = 9;
        bit1OFF = 12;
        createCode = 1;
        break;
      case 4:
        bit0ON = 5;
        bit0OFF = 6;
        bit1ON = 9;
        bit1OFF = 10;
        createCode = 1;
        break;
    }


  }

}



void initializeTimer() {

  // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;


  //frequency of preamble
  int freq = 3750;
  int value = 16000000 / 256 /  freq /2;

  OCR1A = value;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler
  //TCCR1B |= (1 << CSHIGH12) | (1 << CS10); // 1024 prescaler


  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts


}
