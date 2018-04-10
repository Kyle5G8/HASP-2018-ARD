String SerialIn;
String MostRecentCommand;
String ProcessedCommand;
void setup() 
{
Serial.begin(9600);
}
 
void loop()
{    
    checkCommands();  
    
}
 


 
 
 
///////////////////////////////////////////////////////////////Sensor Functions
float readPressure() //Pa
{
  int pressureValue = analogRead(A14);
  float pressure=((pressureValue/1024.0)+0.095)/0.000009;
  float millibars = pressure/100;
  float Pa = millibars/0.01;
  return pressure;
}

float readHumidity() //RH
{ 
 float rhRead = analogRead(A0); 
 float RH = rhRead/(1.0546-0.00216*23);// replace 23 with thermistor value for temperature compensation
 float rhvoltage = (5*(0.00636*RH+0.1515));
 return rhvoltage*3;
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
  if(ProcessedCommand == "20")
  {
    MostRecentCommand = "2020"; // update most recent command (troubleshooting)
    Serial.println(readPressure());
  }
  if(ProcessedCommand == "21")
  {
    MostRecentCommand = "2121";
    //command 2
   
  }
  if(ProcessedCommand == "22")
  {
    MostRecentCommand = "2222";
    //command 3
  }
  if(ProcessedCommand == "23")
  {
    MostRecentCommand = "2323";
    //command 4
  }
  if(ProcessedCommand == "24")
  {
    MostRecentCommand = "2424";
    //command 5
  }
  if(ProcessedCommand == "25")
  {
    MostRecentCommand = "2525";
    //command 6
  }
  if(ProcessedCommand == "26")
  {
    MostRecentCommand = "2626";
    //command 7
  }
  if(ProcessedCommand == "27")
  {
    MostRecentCommand = "2727";
    //command 8
  }
  if(ProcessedCommand == "28")
  {
    MostRecentCommand = "2828";
    //command 9
  }
  if(ProcessedCommand == "29")
  {
    MostRecentCommand = "2929";
    //command 10
  }
  ProcessedCommand = "";
  SerialIn = "";
  }
 
