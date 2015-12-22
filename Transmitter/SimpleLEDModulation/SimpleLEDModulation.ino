

int ledPin = 13;
int val = 0;
unsigned long start;
unsigned long finish;
int frequency = 1;
float period;
float pauseMilli;
int decimal;
float floating=0;
int pauseMicro;



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(ledPin, OUTPUT);
  period = (1.0/frequency * 1000.0);
  pauseMilli = period /2;
  decimal = pauseMilli;   //get decimal part
  floating = pauseMilli - decimal;  //get floating part
  pauseMicro = floating * 1000;
  
  Serial.begin(115200);
  
  Serial.print(pauseMilli);
  Serial.print(" ");
  Serial.print(decimal);
  Serial.print(" ");
  Serial.print(floating);
  Serial.print(" ");  
  Serial.print(pauseMicro);
  Serial.print("\n");
  
  
}

// the loop function runs over and over again forever
void loop() {
  
  
    digitalWrite(ledPin,HIGH);

    delay(decimal);
    //if there is a floating part then delay more in microseconds
    if(floating != 0){
        //Serial.print("!!!!!!");  
      delayMicroseconds(pauseMicro);
    }
    
    digitalWrite(ledPin,LOW);

    delay(decimal);
    //if there is a floating part then delay more in microseconds
    if(floating != 0){
        //Serial.print("!!!!!!");  
      delayMicroseconds(pauseMicro);
    }
  
}


