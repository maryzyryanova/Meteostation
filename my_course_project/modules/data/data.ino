#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <Adafruit_BMP280.h>
#include "DHT.h"
#include <Wire.h> 

#define DHTPIN D4
#define BMP280_I2C_ADDRESS  0x76

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

DHT dht(DHTPIN, DHT11);
Adafruit_BMP280 bmp280;

const char* ssid = "pipipupu"; 
const char* password = "12345876"; 
const char* host = "http://192.168.0.100"; 
String url = "/send/"; 

int temperature, humidity, pressure;

void setup() 
{ 
  Serial.begin(9600); 
  dht.begin();
  bmp280.begin(BMP280_I2C_ADDRESS);

  delay(10); 
  Serial.println(); 
  Serial.println(); 
  Serial.print("Connecting to "); 
  Serial.println(ssid); 

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP()); 
} 
 

void loop() 
{ 
  delay(5000); 
  temperature = (int)dht.readTemperature(); 
  humidity = (int)dht.readHumidity();
  pressure = (int)(bmp280.readPressure()*0.007501);

  Serial.print("connecting to "); 
  Serial.println(host); 

  WiFiClient client; 
  const int httpPort = 80; 

  Serial.print("Requesting URL: "); 
  Serial.println(url); 
  String postData = "Temperature: " + String(temperature) + "C\n" + "Humidity: " + String(humidity) + "%\n" + "Pressure: " + String(pressure) + " mmhg\n";
  Serial.println(postData); 
  String address = host + url; 

  HTTPClient http; 
  http.begin(client, address); 
  http.addHeader("Content-Type", "application/json"); 

  int httpResponseCode = http.POST("{\"humidity\":\""+String(humidity)+"\",\"temperature\":\""+String(temperature)+"\",\"pressure\":\""+String(pressure)+"\"}");
   
  Serial.println(httpResponseCode);  
  String payload = http.getString(); 
  Serial.println(payload); 
  http.end(); 
  Serial.println("closing connection"); 
}
 