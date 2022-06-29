#include <SoftwareSerial.h>
#include <DHT.h>

#define SIM800_TX_PIN 11
 
#define SIM800_RX_PIN 10
 
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
#define DHTPIN 2  
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);
int analogMQ7 = A5;
int val = 0;

void setup() {
  
  Serial.begin(9600);
  while(!Serial);
  serialSIM800.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
  Serial.println("Warming-UP");  
  delay(6000);                   
  Serial.println("Measurement"); 

dht.begin();

 delay(6000);
}

void loop() {
  delay(2000);
  float hum = dht.readHumidity();
  float tempC = dht.readTemperature();
  if (isnan(hum) || isnan(tempC)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }     

printing( hum,tempC);
sendmessage (hum,tempC,val);
}
void sendmessage (float hum, float tempC,int val ){
    Serial.println("Sending SMS...");
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  serialSIM800.write("AT+CMGS=\"+380664807735\"\r\n");
  delay(1000);
   
  serialSIM800.write("Humidity: ");
  serialSIM800.print(hum);
  serialSIM800.write("%\n");
  serialSIM800.write("Temperature: ");
  serialSIM800.print(tempC);
  serialSIM800.write("*C\n");
  serialSIM800.write("CO: ");
  serialSIM800.print(val);
  delay(1000);

  serialSIM800.write((char)26);
  delay(10000000);
     
  Serial.println("SMS Sent!");
  }

void printing(float hum, float tempC){
  Serial.print("Humidity: "); 
  Serial.print(hum);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(tempC);
  Serial.println(" *C "); 
  val = analogRead(analogMQ7);   
  Serial.print("CO = " );     
  Serial.println(val); 
}