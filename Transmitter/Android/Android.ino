#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>
#define  LED_PIN  13
AndroidAccessory acc("Manufacturer",
		"Model",
		"Description",
		"1.0",
		"http://yoursite.com",
                "0000000012345678");

#define BUFFER_SIZE 20            
   
void setup()
{
  // set communiation speed
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  acc.powerOn();
}
 
void loop()
{
  byte msg[BUFFER_SIZE];
  String message;
  if (acc.isConnected()) {
    
    for(int i =0 ; i < BUFFER_SIZE; i++)
      msg[i] = 46;    
    message = "";  
     
    int len = acc.read(msg, sizeof(msg), 1); // read data into msg variable
    if (len > 0) {
      
      for(int i =0 ; i < BUFFER_SIZE; i++){
        
        char c = msg[i];
        message = message + c;
        
        //Serial.println(c);
        
      }
      Serial.println(message);
      /*if (msg[0] == 50) // compare received data
        digitalWrite(LED_PIN,HIGH); // turn on light
      else{
        digitalWrite(LED_PIN,LOW); // turn off light
        Serial.println("LOW");
      }*/
    }
  } 
  else
    digitalWrite(LED_PIN , LOW); // turn off light
}
