
#define numSensors 1    // Number of LED sensors - 6 is the maximum you can wire up
//variables setup

  unsigned long start;
  unsigned long finish;

  byte anodePin[] =  { 7 };
  byte cathodePin[] = { 14 }; // the analogue input pins 0 to 5 when used digitally
  int results[6];
  int refLevel[6];

//setup: declaring inputs and outputs and begin serial 
void setup() { 
    _SFR_IO8(0x35) |= 0x10;   // global disable pull up resistors
  for(int i=0; i<numSensors; i++){
  digitalWrite(anodePin[i],LOW); // ensure pins go low immediatly after initilising them to outputs
  pinMode(anodePin[i],OUTPUT);   // declare the anode pins as outputs
  pinMode(cathodePin[i],INPUT); // declare the cathode pins as inputs
  }
   //start serial with baud rate 38400
  Serial.begin(1200);          
}

//loop: light and then read LEDs 
void loop () {
  
  
  start = micros();
  
  
  // turn all LEDs on
  for(int i=0; i<numSensors; i++){
    digitalWrite(anodePin[i],HIGH);
    pinMode(cathodePin[i],OUTPUT);    // Enable cathode pins as outputs
    digitalWrite(cathodePin[i],LOW);  // Turn ON LED
  } 
   // charge up LEDs cathode = HIGH, anode = LOW
   for(int i=0; i<numSensors; i++){
    digitalWrite(cathodePin[i],HIGH); 
    digitalWrite(anodePin[i],LOW);    
  }
     // Put cathode pins into measuring state (analogue input)
    for(int i=0; i<numSensors; i++){
    pinMode(cathodePin[i],INPUT);
  }

  // Take a reading of the voltage level on the inputs to get a referance level before discharge
   for(int i=0; i<numSensors; i++){
     results[i] = analogRead(i);  // Store the referance level
  }
  //**********************************************************
  delay(40);  // LED discharge time or photon intergration time
              // The larger this is, the more sensitave is the system
  //**********************************************************

 // Read the sensors after discharge to measure the incedent light
      for(int i=numSensors-1; i>-1; i--){  // reverse order reduces start to finish cross talk
     results[i] -= analogRead(i);     // subtract current reading from the referance to give the drop
     pinMode(cathodePin[i],OUTPUT);   // by discharging the LED immediatly the charge on the A/D input is removed and
     digitalWrite(cathodePin[i],LOW); // the cross talk between sensors is reduce
  }

    // print out the results or send it to Processing
    for(int i = 0; i<numSensors; i++){
      
        float voltage = (results[i] * 5.0) / 1023.0;
        Serial.println(voltage,4);  


   // Serial.print(results[i],DEC);
    //Serial.print(" ");
  } 
  
  finish = micros();
  float time = (finish - start) /1000 ;
  Serial.println(time);  

  
    //Serial.println(" ");
    
  delay(1000);
}
