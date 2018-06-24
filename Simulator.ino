#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);//RX/TX

int voltpot = A4;
int voltpin = 5;//fried?
int currentPot = A6;
int currentPin = 6;//fried?
int fan = 10;


void setup() {
pinMode(voltpot, INPUT_PULLUP);
pinMode(voltpin, OUTPUT);
pinMode(currentPot, INPUT_PULLUP);
pinMode(currentPin, OUTPUT);
pinMode(fan, OUTPUT);
TCCR0B = (TCCR0B & 0xF8) | 0x03;
TCCR1B = (TCCR1B & 0xF8) | 0x04;
analogWrite(voltpin, 255);
analogWrite(fan, 255);
  Serial.begin(9600);
  mySerial.begin(1200);
}

void processCMD(char a)
{
  if(a == 'A')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x11);
    mySerial.write(0X11);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Rebooting, 11");
  }
  if(a == 'B')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xAA);
    mySerial.write(0xAA);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Begin Experiment, AA");
  }
  if(a == 'C')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x86);
    mySerial.write(0x86);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Power Save, 86");
  }
  if(a == 'D')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xD2);
    mySerial.write(0xD2);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("GPIO2, D2");
  }
  if(a == 'E')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xD4);
    mySerial.write(0xD4);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("GPIO4, D4");
  }
  if(a == 'F')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xD5);
    mySerial.write(0xD5);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("GPIO5, D5");
  }
  if(a == 'G')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xD6);
    mySerial.write(0xD6);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("GPIO6 D6");
  }
  if(a == 'H')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x36);
    mySerial.write(0x36);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Heaters off 36");
  }
  if(a == 'I')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x37);
    mySerial.write(0x37);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Heaters on 37");
  }
  if(a == 'J')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xA1);
    mySerial.write(0xA1);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Light off A1");
  }
  if(a == 'K')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xA2);
    mySerial.write(0xA2);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Light on A2");
  }
  if(a == 'L')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB1);
    mySerial.write(0xB1);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Fan on B1");
  }
  if(a == 'M')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB2);
    mySerial.write(0xB2);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Fan off B2");
  }
  if(a == 'N')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB3);
    mySerial.write(0xB3);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Valve open B3");
  }
  if(a == 'O')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB4);
    mySerial.write(0xB4);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("valve closed B4");
  }
  if(a == 'P')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB5);
    mySerial.write(0xB5);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Pump on B5");
  }
  if(a == 'Q')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB6);
    mySerial.write(0xB6);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Pump off B6");
  }
  if(a == 'R')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB7);
    mySerial.write(0xB7);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Spectrometer on B7");
  }
  if(a == 'S')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB8);
    mySerial.write(0xB8);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Spectrometer off B8");
  }
  if(a == 'T')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0xB9);
    mySerial.write(0xB9);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("All systems off B9");
  }
  if(a == 'U')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x43);
    mySerial.write(0x43);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("ODS fan on");
  }
  if(a == 'V')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x44);
    mySerial.write(0x44);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("ODS fan off");
  }
  if(a == 'W')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x35);
    mySerial.write(0x35);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("Open and HVC");
  }
  if(a == 'X')
  {
    mySerial.write(0x01);
    mySerial.write(0x02);
    mySerial.write(0x36);
    mySerial.write(0x36);
    mySerial.write(0x03);
    mySerial.write(0x0D);
    mySerial.write(0x0A);
    Serial.println("close and HVC");
  }
  
}


void loop() 
{
   //put your main code here, to run repeatedly:
  while(Serial.available())
  {
    processCMD(Serial.read());
  }

//  while(mySerial.available())
//  {
//    Serial.write(mySerial.read());
//  }
}

