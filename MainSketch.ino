String SerialIn;
void setup() 
{
Serial.begin(9600);
}
 
void loop()
{
    
    Serial.println(readHumidity());
    delay(1000);
}
 


 
 
 
 
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

void checkCommands
{
 while(Serial.available())
 {
 SerialIn = Serial.ReadString();
 }
 if(filterCommand(SerialIn))
 {
  //command actions
 }
 else if(!filterCommand(SerialIn))
 {
 return;
 }
}

bool filterCommand(String a)
{
 if(a.charAt(0) == '2' && a.charAt(2) == '2')
 {
   return true;
 }
 else return false;
}
