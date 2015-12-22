int ledPin = 12;

int enableTimer = 0;



int serial = 1;



char* charArray;

int* manchesterArray;

int charArraySize;

int manchesterArraySize;

int counter;

int i,j,f;

int bitsPerPacket = 8;

int preambleSize = 5;

int bitsPerCharacter = 8;

int packetDuration = 2000;

int packetSize;

int* packet;


unsigned long previousMillis = 0;        








void setup() {
  // put your setup code here, to run once:
  
    pinMode(ledPin, OUTPUT);

    Serial.begin(115200);
    
   
    initializeTimer();
    
}

void loop() {
  
  
  
    if (Serial.available() > 0) {
      
      //read serial      
      readSerial();
      
      
      Serial.print("Characters Read: ");
      Serial.println(charArraySize);
      
      Serial.println("Characters Read:");

      for (i = 0; i < charArraySize ; i++){
      
        Serial.print(charArray[i]);
      }
      
      Serial.print("\n");
      Serial.print("\n");

      //binary to Manchester encoding
      transformToBinary();
      
      

      int payloadSize = bitsPerPacket;
      packetSize = payloadSize + preambleSize; 
      packet = (int*) malloc(packetSize * sizeof(int));
      
      Serial.print(packetSize);
      Serial.print("\n");

      
      Serial.println("Machester Encoding: ");
      
      for (i = 0; i < manchesterArraySize ; i++){
      
        Serial.print(manchesterArray[i]); 
               
      }
      
      
      Serial.print("\n");
      Serial.print("\n");
      
      while(1){
        
        
        if (Serial.available() > 0)
          break;
        
        
     
        Serial.println("Packets: ");
        
        //initialize preamble
        for(j = 0; j < packetSize ; j++){
            
          if(j == 1 || j == 2 || j == 3){
             packet[j] = 1; 
          }
          else
            packet[j] = 0; 
            
          
        }
  
    
        //create every individual packet according to number of bits per packet
        for (i = 0; i < manchesterArraySize ; i = i + bitsPerPacket){
        
          //Serial.print(manchesterArray[i]); 
          
          //Serial.print("Packet ");
          //Serial.print(i);
          //Serial.print("  ");
  
          
          int k = i;
          for(j = preambleSize; j < packetSize ; j++){
            
            packet[j] = manchesterArray[k];
            k++;
            
          }
          
          /*
          packet[0] = 0;
          packet[1] = 1;
          packet[2] = 1;
          packet[3] = 1;
          packet[4] = 0;
          
          
          packet[5] = 0;
          packet[6] = 1;
          packet[7] = 0;
          packet[8] = 1;
          
          
          packet[9] = 1;
          packet[10] = 0;
          
          
          packet[11] = 0;
          packet[12] = 1;
          
          
          
          packet[13] = 0;
          packet[14] = 1;
          packet[15] = 0;
          packet[16] = 1;
          
          packet[17] = 0;
          packet[18] = 1;
          packet[19] = 0;
          packet[20] = 1;
          */
          
          
          
          for (f = 0; f < packetSize ; f++){
        
            //Serial.print(packet[f]); 
            if(f == preambleSize - 1)
              Serial.print("/");
          
          }
          
          
          
          Serial.print("\n");
           
          

          
          //enable timer
          counter = 0;
          enableTimer = 1;
          
          //delay(packetDuration);
          
          //wait for packetDuration milliseconds
          while(1){
            
             unsigned long currentMillis = millis();

            
             if (currentMillis - previousMillis >= packetDuration) {
               
                previousMillis = currentMillis;
                
                break;

               
             }

            
          }
          
          
          //disable timer
          enableTimer = 0;
  
          
          
        }
      
      
      }

      
      
      
    

      
    } 
  
  
}


void readSerial(){
  
  
  String content = "";
  char character;

  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
      delay(10);
  }


  
  charArraySize = content.length() ;
  
  charArray = (char *) malloc(charArraySize * sizeof(char));
  
  content.toCharArray(charArray, charArraySize + 1);

  
}


void transformToBinary(){
    
  
   manchesterArraySize = charArraySize * bitsPerCharacter * 2 + 16;
   
   manchesterArray = (int *) malloc(manchesterArraySize * sizeof(int));
   
   
   Serial.print("Manchester Size: ");
   Serial.println(manchesterArraySize);

  int j = 0;
  
  
  //add start text character
  int startText[8] = {0,0,0,0,0,0,1,0};
  for (int i = 0; i < 8  ; i++){
    
    if(startText[i] == 0){
       manchesterArray[j] = 0;
       manchesterArray[j + 1] = 1;      
    }
    else{
      
       manchesterArray[j] = 1;
       manchesterArray[j + 1] = 0;
      
    }
    
    j = j + 2;
  
  }

  
  j = 16;
  
  for (int i = 0; i < charArraySize  ; i++){
      
    
    //tranform to binary and add to array
    int c = bitsPerCharacter - 1;
    int k;
    for (c ; c >= 0; c--)
    {
      k = charArray[i] >> c;
   
      if (k & 1){
        Serial.print("1");
        manchesterArray[j] = 1;
        manchesterArray[j+1] = 0;
        
      }
      else{
        Serial.print("0"); 
        manchesterArray[j] = 0;
        manchesterArray[j+1] = 1;
      }
      j = j + 2;

    }
    
    
    Serial.print("/");
    
  }
  Serial.print("\n");
  
  
  
  
  
}









void initializeTimer() {

  // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;


  //frequency of preamble
  int freq = 3000;
  int value = 16000000 / 256 /  freq / 2 ;

  OCR1A = value;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler
  //TCCR1B |= (1 << CSHIGH12) | (1 << CS10); // 1024 prescaler


  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts


}



ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  
  if(enableTimer !=0 ){
      //Serial.println(binary[counter]);
      
      //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin  
      
      if(packet[counter] == 1){
        
        if(digitalRead(ledPin) == LOW){
          //Serial.println("ONE");
          digitalWrite(ledPin, HIGH);
        }  
      }
      
      if (packet[counter] == 0 ){
        if(digitalRead(ledPin) == HIGH){
          digitalWrite(ledPin, LOW); 
        }
      }
      
      counter++;
      if(counter == packetSize)
        counter = 0;
        
    
  }
   
  
}






