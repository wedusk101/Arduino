int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() 
{
	pinMode(3,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(4,OUTPUT);
	Serial.begin(9600); //sets serial port for communication
}
void loop()
{
  sensorValue = analogRead(sensorPin);
  if (sensorValue < 20)
  {
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(3,HIGH);
    tone(3,2200,1000);
    delay(1000);
    digitalWrite(3,LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(3,LOW);
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
  }
}
