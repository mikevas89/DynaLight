

int ledPin = 4;
int senRead = 0;
int val = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin,HIGH);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  val= readLED(20);
  //val = analogRead(senRead);
  
  float voltage = (val * 5.0) / 1023.0;
  
  
  Serial.println(val);
  Serial.println(voltage,4);  
  delay(500);
  
}


int readLED(int number) {            // Read analog value n times and avarage over those n times
  int totaal = 0;
  for(int x = 0; x < number; x++) {
    totaal += analogRead(senRead);
    delay(10);
  }
  return totaal/number;
}

