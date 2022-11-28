#include <LoRa.h> 
const int SW1 = 3;
const int SW2 = 4;
int SyncWord = 0x22;
void setup() {
  Serial.begin(9600);
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;
                                            
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);                                        
  TIMSK1 |= (1 << OCIE1A);
  sei();
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3 );
  LoRa.setCodingRate4(8);
  LoRa.setSyncWord(SyncWord);
}
int priviousSwitchValue1 = 1;
int priviousSwitchValue2 = 1;
int liveSwitchValue1 = 0;
int liveSwitchValue2 = 0;
bool switchPressFlag1 = false;
bool switchPressFlag2 = false;
bool gLedPin = 0;
int data = 1;
void loop() {
  liveSwitchValue1 = digitalRead(SW1);
  if( (liveSwitchValue1 == 0) and (switchPressFlag1 == false) )
  {
    delay(50);
    data = 11;
    Serial.println("11");
    switchPressFlag1 = true;
    priviousSwitchValue1 = !priviousSwitchValue1;
    LoRa.beginPacket();  
    LoRa.print(data);
    LoRa.endPacket();
  }
  if( (liveSwitchValue1 == 1) and (switchPressFlag1 == true) )
  {
    delay(50);
    data = 22;
    Serial.println("22");
    switchPressFlag1 = false;
    LoRa.beginPacket();  
    LoRa.print(data);
    LoRa.endPacket();
  }
  
  liveSwitchValue2 = digitalRead(SW2);
  if( (liveSwitchValue2 == 0) and (switchPressFlag2 == false))
  {
    delay(50);
    data = 33;
    Serial.println("33");
    switchPressFlag2 = true;
    priviousSwitchValue2 = !priviousSwitchValue2;
    LoRa.beginPacket();  
    LoRa.print(data);
    LoRa.endPacket();
  }
  if( (liveSwitchValue2 == 1) and (switchPressFlag2 == true) )
  {
    delay(50);
    data = 44;
    Serial.println("44");
    switchPressFlag2 = false;
    LoRa.beginPacket();  
    LoRa.print(data);
    LoRa.endPacket();
  }
  if(gLedPin == 1)
  {
    data = 55;
    Serial.println("55");
    gLedPin = 0;
    LoRa.beginPacket();  
    LoRa.print(data);
    LoRa.endPacket();
  }
}

ISR(TIMER1_COMPA_vect){
  static volatile int ledFlag = 0;
  if(++ledFlag >= 5)
  {
    gLedPin = 1;
    ledFlag = 0;
  }
}
