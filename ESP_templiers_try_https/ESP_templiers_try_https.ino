/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid     = "HighGrid";
const char* password = "sophiagrid";

const char* host = "api.powervas.com";
const int httpPort = 443;
const char* accessToken   = "9c870d30-cf74-4d20-b15d-000731534a8c";
//const String url = "/users/current/sites/templiers/variables/esp_test_2";
const String url = "/users/current/sites/gridpocket_1/variables/testPapa";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void request() {
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String data = "{\"value\":\"Test ESP8266 \"}";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.println(String("POST ") + url + " HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  //client.println("Connection: keep-alive");
  //client.println("Cache-Control: no-cache");
  //client.println("Accept: */*");
  //client.println("Accept-Encoding: gzip, deflate");
  //client.println("Accept-Language: fr-FR,fr;q=0.8,en-US;q=0.6,en;q=0.4");
  client.println("Content-Type: application/json");
  client.print("Authorization: Bearer ");//4d3829b6-5688-4ebe-886b-a18230b3ac5b");
  client.println(accessToken);
  client.print("Content-Length: ");
  client.println(data.length());
  client.println();
  client.println(data);
  
  delay(50);
  
  // Read all the lines of the reply from server and print them to Serial
  //while(client.available()){
  //  String line = client.readStringUntil('\r');
  //  Serial.print(line);
  //}
  if(client.connected()){
    client.stop();
  }
  
  Serial.println();
  Serial.println("closing connection");
  //ESP.deepSleep(60 * 1000000);//Sleep for 60 seconds
  delay(60000);
}

void loop(){
  request();
}
