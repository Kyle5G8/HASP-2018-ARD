void setup() {
    Serial.begin(9600);
}
 
void loop(){
    float pressure = readPressure(A14);
    float millibars = pressure/100;
 
    Serial.println();
    Serial.print("Pressure = ");
    Serial.print(pressure);
    Serial.println(" pascals");
    Serial.print("Pressure = ");
    Serial.print(millibars);
    Serial.println(" millibars");
    delay(1000);
}
 
/* Reads pressure from the given pin.
* Returns a value in Pascals
*/
float readPressure(int pin){
    int pressureValue = analogRead(pin);
    float pressure=((pressureValue/1024.0)+0.095)/0.000009;
    return pressure;
}
