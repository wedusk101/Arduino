#define echoPin 2 // Echo Pin
#define trigPin 0 // Trigger Pin
 
long duration, distance; // Duration used to calculate distance
 
void setup()
{
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.println("Ready");
}
 
void loop()
{
/* The following trigPin/echoPin cycle is used to determine the
distance of the nearest object by bouncing soundwaves off of it. */
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
Serial.println(distance);
//Delay 50ms before next reading.
delay(500);
}
