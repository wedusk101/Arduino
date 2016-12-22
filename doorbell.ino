void setup() {
pinMode(2,OUTPUT);
pinMode(6,INPUT);
// put your setup code here, to run once:
}
void loop() {
  while(digitalRead(6) == HIGH)
{
  tone(2,2200,1000);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);}
  // put your main code here, to run repeatedly:

}
