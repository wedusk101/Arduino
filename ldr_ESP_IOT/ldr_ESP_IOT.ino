#include <SoftwareSerial.h>

SoftwareSerial esp8266(10, 11); // RX, TX

const int LDR = A2;
int ldr_status = 0;
String cmd = "";

void fireWebRequest(){
  // cmd = "GET /trigger/motion_detected/with/key/cgSqIa1NrlKwEtyZi5SA07 HTTP/1.1\r\n";
  // cmd += "Host: maker.ifttt.com\r\n\\r\n";
  // cmd += "User-Agent: ESP8266\r\n\\r\n";
  // cmd += "Accept: */*\r\n";
  cmd = "GET /trigger/motion_detected/with/key/cgSqIa1NrlKwEtyZi5SA07 HTTP/1.1\\r\\nHost: maker.ifttt.com\\r\\nUser-agent: curl/7.47.0\\r\\nAccept: */*\\r\\n\\r\\n";
  String conntype = "AT+CIPMUX=1\\r\\n";
  String startconn = "AT+CIPSTART=4,\"TCP\",\"maker.ifttt.com\",80\\r\\n";
  esp8266.print(conntype);
  esp8266.print(startconn);
  esp8266.print(cmd);
  esp8266.print("AT+CIPCLOSE\\r\\n"); 
}

void sendCmd(String msg)
{
  int i = 0;
  i += 64;
  while(i < cmd.length()){
    esp8266.write(cmd[i]);
    i++;
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Started");
  pinMode(LDR, INPUT);
  // set the data rate for the SoftwareSerial port
  esp8266.begin(9600);
  esp8266.write("AT\r\n");
}

void loop() {
  ldr_status = analogRead(LDR);
  // Serial.println(ldr_status);
  if (ldr_status < 500){
    fireWebRequest();
    delay(20000);
  }
  
  if (esp8266.available()) {
    Serial.write(esp8266.read());
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}
