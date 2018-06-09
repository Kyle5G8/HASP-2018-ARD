String SerialIn;
String MostRecentCommand;
String ProcessedCommand;
int a = 0;//looping variables
int b = 0;//looping variables
int c = 0;//looping variables
int time = 42;//time(updating)//////CHANGE//////
x = 60;// how many seconds the loop should last


int valveHTR = 24; 
int ATCMISC = 25;
int GPIO13 = 28;
int GPIO19 = 29;
int GPIO26 = 30;
int GPIO16 = 5;
int GPIO18 = 6;
int GPIO21 = 22;


void setup() 
{
Serial.begin(9600);
pinMode(13, OUTPUT);
}
 
void loop()
{    
    checkCommands();  
}
 


 
 
 
///////////////////////////////////////////////////////////////Sensor Functions
float readtherm(int thermID)
{
  while (a < 0)
  {
    float temp = 0;
    return temp;
    Serial.println("T:" + String(temp) + ":" + String(time));//uploads data
  	Serial.flush();
  	delay(1000);//1 second buffer
  	a += 1;
  }
  a = 0
} 

void flashOnce()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

void flashTwice()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

void dimUpDown()
{
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(13, i);
    delay(10);
  }
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(13, i);
    delay(10);
  }
}
float readPressure() //Pa
{
  while (b < x)
  {
    int pressureValue = analogRead(A14);
    float pressure=((pressureValue/1024.0)+0.095)/0.000009;
    float millibars = pressure/100;
    float Pa = millibars/0.01;
    return pressure;
    Serial.println("P:" + String(Pa) + ":" + String(time));//uploads data
  	Serial.flush();
  	delay(1000);//1 second buffer
  	b += 1;
  }
  b = 0;
}

float readHumidity() //RH
{
  while (c < x)
  {
    float rhRead = analogRead(A0); 
    float RH = rhRead/(1.0546-0.00216*23);// replace 23 with thermistor value for temperature compensation
    float rhvoltage = (5*(0.00636*RH+0.1515));
    return rhvoltage*3;
    Serial.println("H:" + String(rhvoltage*3) + ":" String(time));//uploads data
  	Serial.flush();
  	delay(1000);//1 second buffer
  	c += 1;
  }
  c = 0;
}
//////////////////////////////////////////////////////////////////Command actions (methods to be called within each command if statement)

/////////////////////////////////////////////////////////////////Command Processing 
void checkCommands()//check for commands and call their methods
{
 while(Serial.available())
 {
 SerialIn = Serial.readString();
 }
  ProcessedCommand = SerialIn.charAt(2);
  ProcessedCommand += SerialIn.charAt(3);
  if(ProcessedCommand == "20" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2020"; // update most recent command (troubleshooting)
    Serial.println(ProcessedCommand + ProcessedCommand);
    flashOnce();    
  }
  if(ProcessedCommand == "21" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2121";
    Serial.println(ProcessedCommand + ProcessedCommand);
    flashTwice();
   
  }
  if(ProcessedCommand == "22" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2222";
    Serial.println(ProcessedCommand + ProcessedCommand);
    dimUpDown();
  }
  if(ProcessedCommand == "23" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2323";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 4
  }
  if(ProcessedCommand == "24" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2424";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 5
  }
  if(ProcessedCommand == "25" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2525";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 6
  }
  if(ProcessedCommand == "26" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2626";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 7
  }
  if(ProcessedCommand == "27" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2727";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 8
  }
  if(ProcessedCommand == "28" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2828";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 9
  }
  if(ProcessedCommand == "29" && (SerialIn.charAt(4) == 'A' && SerialIn.charAt(5) == '3' && SerialIn.charAt(6) == 'D'))
  {
    MostRecentCommand = "2929";
    Serial.println(ProcessedCommand + ProcessedCommand);
    //command 10
  }
  ProcessedCommand = ""; //this and the next line prevent a command from executing endlessly
  SerialIn = "";
  }
