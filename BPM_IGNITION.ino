

#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>  

const int PulseWire = 0;       
          
int Threshold = 700;           
boolean stress = true;                              
                               
                               
PulseSensorPlayground pulseSensor;  


void setup() {   

  Serial.begin(9600);         
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pulseSensor.analogInput(PulseWire);          
  pulseSensor.setThreshold(Threshold);   

   
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  
  }
}



void loop() {

 int BPM = pulseSensor.getBeatsPerMinute();  

if (pulseSensor.sawStartOfBeat()) {            
 Serial.println("♥  A HeartBeat Happened ! ");
 Serial.print("BPM: ");                       
 Serial.println(BPM);
 if (BPM > 65 && BPM < 82)
 {
  stress = false;
 }
 else
 {
  stress = true;
 } 
}
while (stress == false)
{
  digitalWrite(13,HIGH); // Lights Switched on showing car is ignited.
}

  delay(20);                   

}

  
