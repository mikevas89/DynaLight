

int senRead = 0;
int val = 0;
unsigned long start;
unsigned long finish;
int frequency = 100;
float period;



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin,HIGH);
  period = 1.0/frequency * 1000.0 ;
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  
  //val= readLED(20);
  //start = micros(); 
  val = analogRead(senRead);
  
  //float voltage = (val * 5.0) / 1023.0;
  
  Serial.print(val);
  Serial.print("\n");

  
  //finish = micros();
  //float time = (finish - start) ;
  //Serial.println(time); 
  
  
  
  //Serial.println(val);
  //Serial.println(voltage,4); 
  delay(period);
  //Serial.println(period);
  
  //delay(10);
  
}


int readLED(int number) {            // Read analog value n times and avarage over those n times
  int totaal = 0;
  for(int x = 0; x < number; x++) {
    totaal += analogRead(senRead);
    delay(10);
  }
  return totaal/number;
}

