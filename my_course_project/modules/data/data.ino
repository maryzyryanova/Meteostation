#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include "DHT.h"

#define DHTPIN D4

DHT dht(DHTPIN, DHT11);

const char* ssid = "pipipupu"; 
const char* password = "12345876"; 
const char* host = "192.168.0.100"; //edit the host adress, ip address etc. 
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
  const int httpPort = 8000; 

  if (!client.connect(host, httpPort)) 
  { 
  Serial.println("connection failed"); 
  return; 
  } 
  Serial.print("Requesting URL: "); 
  Serial.println(url); //Post Data 
  String postData = "Temperature: " + String(temperature) + "C\n" + "Humidity: " + String(humidity) + "%\n";
  Serial.println(postData); 
  String address = host + url; 

  HTTPClient http; 
  http.begin(client, address); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  auto httpCode = http.POST(postData); 
  Serial.println(httpCode);  
  String payload = http.getString(); 
  Serial.println(payload); 
  http.end(); 
  Serial.println("closing connection"); 
} 