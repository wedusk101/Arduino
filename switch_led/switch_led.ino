void setup() {
pinMode(2,OUTPUT);
pinMode(6,INPUT);
while (digitalRead(6) == HIGH)
;
digitalWrite(2,HIGH);
delay(1000);
digitalWrite(2,LOW);
delay(1000);
digitalWrite(2,HIGH);
delay(1000);
digitalWrite(2,LOW);
}
void loop()
{}
