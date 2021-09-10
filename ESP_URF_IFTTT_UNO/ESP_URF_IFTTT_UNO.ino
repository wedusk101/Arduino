#include <SoftwareSerial.h>

//SoftwareSerial esp8266(10, 11); //RX, TX
// Pins
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;

//Anything over 400 cm (23200 us pulse) is "out of range"
//const unsigned int MAX_DIST = 23200;
String cmd = "";

void setup() {
  // put your setup code here, to run once:
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(3,OUTPUT); // buzzer
  pinMode(2,OUTPUT); // green LED
  pinMode(4,OUTPUT); // red LED
  pinMode(5,OUTPUT); // ESP INPUT
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //esp8266.begin(9600);
  //esp8266.write("AT\r\n");
  //delay(2000);
  Serial.println("SYSTEM READY");
  //esp8266.write("AT+CIPMUX=1\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if (esp8266.available()) {
    Serial.write(esp8266.read());
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }*/
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float dist_cm;
  

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while(digitalRead(ECHO_PIN) == 0);

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while(digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  // of sound in air at sea level (~340 m/s).
  dist_cm = pulse_width / 58.0;
  // Serial.print(dist_cm);
  // Serial.print(" cm \n");
  // cmd = "GET /trigger/motion_detected/with/key/cgSqIa1NrlKwEtyZi5SA07 HTTP/1.1\r\n";
  // cmd += "Host: maker.ifttt.com\r\n\r\n";
  // String startconn = "AT+CIPSTART=4,\"TCP\",\"maker.ifttt.com\",80\r\n";
  if(dist_cm < 30) // esp8266 should send an HTTP request to maker.ifttt.com
  {
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(3,HIGH);
    tone(3,2200,1000);
    delay(1000);
    digitalWrite(3,LOW);
    delay(1000);
    //esp8266.print(startconn);
    Serial.print("448\r\n"); // sends this number to the shell script monitoring the serial output
    //esp8266.write("AT+CIPSEND=4,93\r\n");
    //sendCmd(cmd);
    /*esp8266.write(cmd.length()-6);
    esp8266.write("\r\n");    
        if(Serial.find(">")){
          sendCmd(cmd);
        }*/
        //esp8266.write("AT+CIPCLOSE");    
  }
  else{
    digitalWrite(3,LOW);
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  delay(100);  
}

/*void sendCmd(String msg)
{
  int i = 0;
  //i += 64;
  while(i < cmd.length()){
        esp8266.write(cmd[i]);
        i++;}
}*/
