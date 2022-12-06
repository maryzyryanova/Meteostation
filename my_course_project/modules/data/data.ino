#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include "DHT.h"

#define DHTPIN D4

DHT dht(DHTPIN, DHT11);

const char* ssid = "pipipupu"; 
const char* password = "12345876"; 
const char* host = "http://192.168.0.100"; 
String url = "/send/"; 

float temperature, humidity;

void setup() 
{ 
  Serial.begin(9600); 
  dht.begin();

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
  temperature = dht.readTemperature(); 
  humidity = dht.readHumidity();

  Serial.print("connecting to "); 
  Serial.println(host); 

  WiFiClient client; 
  const int httpPort = 80; 

  Serial.print("Requesting URL: "); 
  Serial.println(url); 
  String postData = "Temperature: " + String(temperature) + "C\n" + "Humidity: " + String(humidity) + "%\n";
  Serial.println(postData); 
  String address = host + url; 

  HTTPClient http; 
  http.begin(client, address); 
  http.addHeader("Content-Type", "application/json"); 
  
  Serial.println("{\"humidity\":\""+String(humidity)+"\",\"temperature\":\""+String(temperature)+"\",\"pressure\":\"0\"}");

  int httpResponseCode = http.POST("{\"humidity\":\""+String(humidity)+"\",\"temperature\":\""+String(temperature)+"\",\"pressure\":\"0\"}");
   
  Serial.println(httpResponseCode);  
  String payload = http.getString(); 
  Serial.println(payload); 
  http.end(); 
  Serial.println("closing connection"); 
} 