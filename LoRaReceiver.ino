#include <LoRa.h> 

const int LED1 = 3;
const int RLY1 = 4;
const int RLY2 = 5;

String inString = ""; 
int val = 0;
int SyncWord = 0x22;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(RLY1,OUTPUT);
  pinMode(RLY2,OUTPUT);
  
  digitalWrite(LED1 , LOW);
  digitalWrite(RLY1 , HIGH);
  digitalWrite(RLY2 , HIGH);
  
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
   LoRa.setSpreadingFactor(12);
   LoRa.setSignalBandwidth(62.5E3);
   LoRa.setCodingRate4(8);
   LoRa.setSyncWord(SyncWord);
}
bool i=0;
int priviousValue = 0;
int liveValue = 0;

void loop() { 
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    // read packet    
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString.toInt();  
      digitalWrite(LED1 , HIGH);
      delay(10);
      digitalWrite(LED1 , LOW);
      delay(10);     
    }
    inString = "";     
    LoRa.packetRssi();    
  }
  
  Serial.println(val);  
  liveValue = val;
    
  if(priviousValue != liveValue)
  {
    priviousValue = liveValue;
  
    if(val == 11)
    {
      digitalWrite(RLY1 , LOW);
    }
    
    if(val == 22)
    {
      digitalWrite(RLY1 , HIGH);
    }
  
    if(val == 33)
    {
      digitalWrite(RLY2 , LOW);
    }
    
    if(val == 44)
    {
      digitalWrite(RLY2 , HIGH);
    }
  }
}
