int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0;
void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(9600);  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(2,HIGH);
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);// put your main code here, to run repeatedly:
  delay(1000);
}
