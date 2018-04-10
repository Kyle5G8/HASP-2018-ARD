String SerialIn;
String MostRecentCommand;
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
bool filterCommand(String a)//check if the command is for the arduino or the RPI
{
 if(a.charAt(0) == '2' && a.charAt(2) == '2')
 {
   return true;
 }
 else return false;
}




void checkCommands()//check for commands and call their methods
{
 while(Serial.available())
 {
 SerialIn = Serial.readString();
 }
 if(filterCommand(SerialIn))
 {
  if(SerialIn == "2020")
  {
    MostRecentCommand = "2020"; // update most recent command (troubleshooting)
    //command 1
  }
  if(SerialIn == "2121")
  {
    MostRecentCommand = "2121";
    //command 2
  }
  if(SerialIn == "2222")
  {
    MostRecentCommand = "2222";
    //command 3
  }
  if(SerialIn == "2323")
  {
    MostRecentCommand = "2323";
    //command 4
  }
  if(SerialIn == "2424")
  {
    MostRecentCommand = "2424";
    //command 5
  }
  if(SerialIn == "2525")
  {
    MostRecentCommand = "2525";
    //command 6
  }
  if(SerialIn == "2626")
  {
    MostRecentCommand = "2626";
    //command 7
  }
  if(SerialIn == "2727")
  {
    MostRecentCommand = "2727";
    //command 8
  }
  if(SerialIn == "2828")
  {
    MostRecentCommand = "2828";
    //command 9
  }
  if(SerialIn == "2929")
  {
    MostRecentCommand = "2929";
    //command 10
  }
  }
 
 else if(!filterCommand(SerialIn))
 {
 return;
 }
}
