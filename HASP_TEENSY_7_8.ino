#define COMMANDSERIAL Serial1
byte a[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int count = 0;
 
#define TEMPERATURENOMINAL 25 
#define NUMSAMPLES 5
#define BCOEFFICIENT 3892

int8_t i;
float average;
int temp;
uint16_t samples[NUMSAMPLES];
float steinhart;
int data;
//downlink variables
int counter = 0;//pass
float current = 0;//pass
double Ext_Temp = 0;//pass
double FC_Temp = 0;//pass
double EXP_Temp = 0;//pass
double SPEC_Temp = 0;//pass
double LIGHT_Temp = 0;//pass
double SOL_Temp = 0;//pass
double Chamber_hum = 0;
double PCB_hum = 0;//pass
double otherhum = 0;
double pressure = 0;
double stat = 0;
int light = 0;
int valve = 0;
int fan = 0;
int PH = 0;
int pump = 0;
char CMD1 = 'a';
char CMD2 = 'a';
int lastDisc = 0;
//current sensor
const int SENSOR_PIN = A2;
const int RS = 10;
float sensorValue;
float icurrent;
//
//Thermistors
int therm1 = A22;
int therm2 = A21;
int therm3 = A20;
int therm4 = A19;
int therm5 = A18;
int therm6 = A17;
//
//teensy link
int teensylink1 = 28;
int teensylink2 = 29;
int teensylink3 = 30;
int teensylink4 = 5;
int teensylink5 = 6;
int teensylink6 = 22;
//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  COMMANDSERIAL.begin(1200);
  analogReference(EXTERNAL);
}
int val;
void readCurrent()
{
  float inal = 0.000;
for(int i = 0; i < 1000; i++)
{ 
  analogReference(INTERNAL);
  sensorValue = analogRead(SENSOR_PIN);
  sensorValue = ((1.2*sensorValue))/1023.000;
  
  icurrent = (sensorValue*1000.000) / (.10000 * 10000.000);
  inal += icurrent*1000.000;  
}
  inal = (inal/999.000);
  
  current = inal;
  analogReference(EXTERNAL);
}
float RH = 0;
float Vo = 0;
void readHums()
{
  analogReference(EXTERNAL);
  float hum1sum = 0;
  for(int i = 0; i < 100; i++)
  {
  Vo = (analogRead(A9)*3.3)/1024;
  RH = (Vo/(5.6*0.00636) - (0.1515/0.00636));
  hum1sum += RH;
  }
  
  float TRH1 = (hum1sum/99)/(1.0546-0.00216*FC_Temp);
  Chamber_hum = TRH1;
  Vo = 0;
  RH = 0;
  hum1sum = 0;
  for(int i = 0; i < 100; i++)
  {
  Vo = (analogRead(A6)*3.3)/1024;//U36
  RH = (Vo/(5.6*0.0062) - (0.16/0.0062));
  hum1sum += RH;
  }
  
  float TRH2 = (hum1sum/99)/(1.0546-0.00216*FC_Temp);
  PCB_hum = TRH2;

  Vo = 0;
  RH = 0;
  hum1sum = 0;
  for(int i = 0; i < 100; i++)
  {
  Vo = (analogRead(A7)*3.3)/1024;//U35
  RH = (Vo/(5.6*0.0062) - (0.16/0.0062));
  hum1sum += RH;
  }
  
  float TRH3 = (hum1sum/99)/(1.0546-0.00216*FC_Temp);
  otherhum = TRH3;
}

void readTherms()
{
  for (i=0; i< NUMSAMPLES; i++) { //U22
   samples[i] = analogRead(therm1);
   
  }
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  } 
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = 5150 / average; 
  steinhart = average / 2700;     
  steinhart = log(steinhart);                  
  steinhart /= BCOEFFICIENT;                   
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;                 
  steinhart -= 273.15;                         
  temp = steinhart;
  Ext_Temp = temp;

   for (i=0; i< NUMSAMPLES; i++) { //U27
   samples[i] = analogRead(therm2);
   
  }
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  } 
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = 5150 / average; 
  steinhart = average / 2700;     
  steinhart = log(steinhart);                  
  steinhart /= BCOEFFICIENT;                   
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;                 
  steinhart -= 273.15;                         
  temp = steinhart;
  FC_Temp = temp;


   for (i=0; i< NUMSAMPLES; i++) { //U28
   samples[i] = analogRead(therm3);
   
  }
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  } 
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = 5150 / average; 
  steinhart = average / 2700;     
  steinhart = log(steinhart);                  
  steinhart /= BCOEFFICIENT;                   
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;                 
  steinhart -= 273.15;                         
  temp = steinhart;
  EXP_Temp = temp;

   for (i=0; i< NUMSAMPLES; i++) { //U21
   samples[i] = analogRead(therm4);
   
  }
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  } 
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = 5150 / average; 
  steinhart = average / 2700;     
  steinhart = log(steinhart);                  
  steinhart /= BCOEFFICIENT;                   
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;                 
  steinhart -= 273.15;                         
  temp = steinhart;
  SPEC_Temp = temp;

   for (i=0; i< NUMSAMPLES; i++) { //U24
   samples[i] = analogRead(therm5);
   
  }
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  } 
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = 5150 / average; 
  steinhart = average / 2700;     
  steinhart = log(steinhart);                  
  steinhart /= BCOEFFICIENT;                   
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;                 
  steinhart -= 273.15;                         
  temp = steinhart;
  LIGHT_Temp = temp;

   for (i=0; i< NUMSAMPLES; i++) { //U23
   samples[i] = analogRead(therm6);
   
  }
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  } 
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = 5150 / average; 
  steinhart = average / 2700;     
  steinhart = log(steinhart);                  
  steinhart /= BCOEFFICIENT;                   
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;                 
  steinhart -= 273.15;                         
  temp = steinhart;
  SOL_Temp = temp;
}

void processCMD()
{
  if(a[0] == 0x01 && a[1] == 0x02 && a[4] == 0x03 && a[5] == 0x0D && a[6] == 0x0A)
  {
    Serial.println("command recieved in the correct 12xx3DA format and processed");
    if(a[2] == 0x11 && a[3] == 0x11)//reboot
    {
      Serial.println("rebooting");
    }
    if(a[2] == 0xAA && a[3] == 0xAA)
    {
      digitalWrite(teensylink1, HIGH);
      digitalWrite(teensylink3, HIGH);
      delay(1000);
      digitalWrite(teensylink1, LOW);
      digitalWrite(teensylink3, LOW);
      Serial.println("Begin experiment");
      CMD1 = 'A';
      CMD2 = 'A';
    }
    if(a[2] == 0x86 && a[3] == 0x86)
    {
      Serial.println("shut down non experiment systems");
    }
    if(a[2] == 0xD2 && a[3] == 0xD2)
    {
      digitalWrite(teensylink2, HIGH);
      delay(1000);
      digitalWrite(teensylink2, LOW);
      Serial.println("GPIO2");
      CMD1 = 'D';
      CMD2 = '2';
    }
    if(a[2] == 0xD4 && a[3] == 0xD4)
    {
      digitalWrite(teensylink4, HIGH);
      delay(1000);
      digitalWrite(teensylink4, LOW);
      Serial.println("GPIO4");
      CMD1 = 'D';
      CMD2 = '4';
    }
    if(a[2] == 0xD5 && a[3] == 0xD5)
    {
      digitalWrite(teensylink5, HIGH);
      delay(1000);
      digitalWrite(teensylink5, LOW);
      Serial.println("GPIO5");
      CMD1 = 'D';
      CMD2 = '5';
    }
    if(a[2] == 0xD6 && a[3] == 0xD6)
    {
      digitalWrite(teensylink6, HIGH);
      delay(1000);
      digitalWrite(teensylink6, LOW);
      Serial.println("GPIO6");
      CMD1 = 'D';
      CMD2 = '6';
    }
    if(a[2] == 0x36 && a[3] == 0x36)
    {
      Serial.println("Heaters off");
    }
    if(a[2] == 0x37 && a[3] == 0x37)
    {
      Serial.println("Heaters on");
    }
    if(a[2] == 0xA1 && a[3] == 0xA1)
    {
      Serial.println("Light off");
    }
    if(a[2] == 0xA2 && a[3] == 0xA2)
    {
      Serial.println("Light on");
    }
    if(a[2] == 0xB1 && a[3] == 0xB1)
    {
      Serial.println("Fan on");
    }
    if(a[2] == 0xB2 && a[3] == 0xB2)
    {
      Serial.println("Fan off");
    }
    if(a[2] == 0xB3 && a[3] == 0xB3)
    {
      Serial.println("valve open");
    }
    if(a[2] == 0xB4 && a[3] == 0xB4)
    {
      Serial.println("valve closed");
    }
    if(a[2] == 0xB5 & a[3] == 0xB5)
    {
      Serial.println("Pump on");
    }
    if(a[2] == 0xB6 && a[3] == 0xB6)
    {
      Serial.println("Pump off");
    }
    if(a[2] == 0xB7 && a[3] == 0xB7)
    {
      Serial.println("Spectrometer on");
    }
    if(a[2] == 0xB8 && a[3] == 0xB8)
    {
      Serial.println("Spectrometer off");
    }
    if(a[2] == 0xB9 && a[3] == 0xB9)
    {
      Serial.println("All systems off");
    }
  }
}

void downlink()//need to test with emulator
{
  String a = String(counter);
  COMMANDSERIAL.write('<');
  Serial.print('<');
  for(int i = 0; i < 6; i++)//counter, overflows after 27 hours
  {
    COMMANDSERIAL.write(a.charAt(i));
    Serial.print(a.charAt(i));
  }
 COMMANDSERIAL.write(',');
 Serial.print(',');
  String b = String(current);
  for(int i = 0; i < 4; i++)
  {
    COMMANDSERIAL.write(b.charAt(i));
    Serial.print(b.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String c = String(Ext_Temp);
  
  for(int i = 0; i < 2; i++)
  {
    COMMANDSERIAL.write(c.charAt(i));
    Serial.print(c.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String d = String(FC_Temp);
  
  for(int i = 0; i < 2; i++)
  {
    COMMANDSERIAL.write(d.charAt(i));
    Serial.print(d.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String e = String(EXP_Temp);
  
  for(int i = 0; i < 2; i++)
  {
    COMMANDSERIAL.write(e.charAt(i));
    Serial.print(e.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String f = String(SPEC_Temp);
 
  for(int i = 0; i < 2; i++)
  {
    COMMANDSERIAL.write(f.charAt(i));
    Serial.print(f.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String g = String(LIGHT_Temp);
  
  for(int i = 0; i < 2; i++)
  {
    COMMANDSERIAL.write(g.charAt(i));
    Serial.print(g.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String h = String(SOL_Temp);
  
  for(int i = 0; i < 2; i++)
  {
    COMMANDSERIAL.write(h.charAt(i));
    Serial.print(h.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String i = String(Chamber_hum);
  for(int j = 0; j < 5; j++)
  {
    COMMANDSERIAL.write(i.charAt(j));
    Serial.print(i.charAt(j));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String j = String(PCB_hum);
  for(int i = 0; i < 4; i++)
  {
    COMMANDSERIAL.write(j.charAt(i));
    Serial.print(j.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String j2 = String(otherhum);
  for(int i = 0; i < 4; i++)
  {
    COMMANDSERIAL.write(j2.charAt(i));
    Serial.print(j2.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String k = String(pressure);
  for(int i = 0; i < 4; i++)
  {
    COMMANDSERIAL.write(k.charAt(i));
    Serial.print(k.charAt(i));
  }
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String l = String(stat);
  COMMANDSERIAL.write(l.charAt(0));
  Serial.print(l.charAt(0));
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String m = String(light);
  COMMANDSERIAL.write(m.charAt(0));
  Serial.print(m.charAt(0));
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String n = String(valve);
  COMMANDSERIAL.write(n.charAt(0));
  Serial.print(n.charAt(0));
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String o = String(fan);
  COMMANDSERIAL.write(o.charAt(0));
  Serial.print(o.charAt(0));
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String p = String(PH);
  COMMANDSERIAL.write(p.charAt(0));
  Serial.print(p.charAt(0));
  COMMANDSERIAL.write(p.charAt(1));
  Serial.print(p.charAt(1));
  COMMANDSERIAL.write(p.charAt(2));
  Serial.print(p.charAt(2));
  COMMANDSERIAL.write(p.charAt(3));
  Serial.print(p.charAt(3));
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String q = String(pump);
  COMMANDSERIAL.write(q.charAt(0));
  Serial.print(q.charAt(0));
  COMMANDSERIAL.write(',');
  Serial.print(',');
  COMMANDSERIAL.write(CMD1);
  Serial.print(CMD1);
  COMMANDSERIAL.write(CMD2);
  Serial.print(CMD2);
  COMMANDSERIAL.write(',');
  Serial.print(',');
  String r = String(lastDisc);
  COMMANDSERIAL.write(r.charAt(0));
  Serial.print(r.charAt(0));
  COMMANDSERIAL.write('>');
  Serial.print('>');
  Serial.println();
  //COMMANDSERIAL.println();
  //Serial.println("downlink");
  counter++;
  delay(1000);
}

void loop() {
////recieve commands from port COMMANDSERIAL (from hasp balloon to teensy)
    
    while(COMMANDSERIAL.available())
    {      
      a[count] = COMMANDSERIAL.read();
      count++;
      if(count == 7)
      {
        Serial.println("count = 7, processCMD function called");
        processCMD();      
        count = 0;//reset counter to 0
      }      
    }
//////////////////////////////////////////////////////////////////////////
readTherms();
readCurrent();
readHums();
downlink();
}

