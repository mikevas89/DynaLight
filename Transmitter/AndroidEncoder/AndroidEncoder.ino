
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>


#define BUFFER_SIZE 5

AndroidAccessory acc("Manufacturer",
		"Model",
		"Description",
		"1.0",
		"http://yoursite.com",
                "0000000012345678");


int number = 0;   // for incoming serial data
int i,j,f;

int ledPin = 12;
int counter = 0;

char message[BUFFER_SIZE];


int mode = 0;

int numberOfBits = 0;

String content = "";



char* charArray;

int* manchesterArray;

int charArraySize;

int manchesterArraySize;


int bitsPerPacket = 8;

int preambleSize = 5;

int bitsPerCharacter = 8;

int packetDuration = 1000;

int packetSize;

int* packet;

unsigned long previousMillis = 0;   


int enableTimer = 0;








void setup() {
  // put your setup code here, to run once:
  
    pinMode(ledPin, OUTPUT);

    Serial.begin(115200);
    
    Serial.println("Run");
    
    delay(500);

    
    acc.powerOn();
    
    initializeTimer();
    
}

void loop() {
  
  
   if (acc.isConnected()) {
     
     
     byte mode[1];
     int len = acc.read(mode, sizeof(mode), 1); // read data into msg variable
     
     if (len > 0) {
       
       if (mode[0] == 1){
         
         Serial.println("Received 1");
         digitalWrite(ledPin,HIGH); // turn on light
         
         delay(500);
         
         digitalWrite(ledPin,LOW); // turn on light
         
 
       }
       else if(mode[0] == 2){
       
         delay(10);
  
         byte bits[1];
         int len = acc.read(bits, sizeof(bits), 1); // read data into msg variable
         
         if (len > 0) {
           
           
           bitsPerPacket = bits[0];
         
           Serial.println(bitsPerPacket);
  
         }
         
         delay(10);
         
         byte msg[BUFFER_SIZE];
          
      
         len = acc.read(msg, sizeof(msg), 1); // read data into msg variable
         if (len > 0) {
            
           for(int i =0 ; i < BUFFER_SIZE; i++){
              
             char c = msg[i];
              
             content.concat(c);
             delay(10);
    
              
             //Serial.println(c);
             
           }
            
         }
           //Serial.println(message);
            
           Serial.println(content);

       
       }
       else if(mode[0] == 3){
         
          charArraySize = content.length() ;
      
          charArray = (char *) malloc(charArraySize * sizeof(char));
      
          content.toCharArray(charArray, charArraySize + 1);
           
           
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
              
              packet[9] = 0;
              packet[10] = 1;
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
              
              
              
              if(previousMillis == 0)
                previousMillis = millis();
                
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
     
     
     
     
     
     
     
     
     
     
     /*
    
     else if ( mode == 3){
       
      delay(2000);
      //Serial.print(content);
      //Serial.print("\n");
      
      
       
      charArraySize = content.length() ;
  
      charArray = (char *) malloc(charArraySize * sizeof(char));
  
      content.toCharArray(charArray, charArraySize + 1);
       
       
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
          
          
          packet[0] = 0;
          packet[1] = 1;
          packet[2] = 1;
          packet[3] = 1;
          packet[4] = 0;
          
          packet[5] = 0;
          packet[6] = 1;
          packet[7] = 0;
          packet[8] = 1;
          
          packet[9] = 0;
          packet[10] = 1;
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
          
          
          
          
          for (f = 0; f < packetSize ; f++){
        
           // Serial.print(packet[f]); 
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
     


   */  
     
   } 
   
   
  

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




