int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() 
{
pinMode(2,OUTPUT);
Serial.begin(9600); //sets serial port for communication
}
void loop()
{
  sensorValue = analogRead(sensorPin);
  if (sensorValue < 50)
  {
    digitalWrite(2,HIGH);
    tone(2,2200,1000);
    delay(1000);
    digitalWrite(2,LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(2,LOW);
  }
}
