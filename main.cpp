#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

using namespace websockets;

// Wifi Credentials
const char* ssid = "Wifi_name";
const char* password = "password";

// Websocket server
const char* websocket_server = "xxx.xxx.x.xx"; // Put PC's local IP
const int websocket_port = 8765;

WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Receieved from server: ");
  Serial.println(message.data());
  // Process message
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWifi Connected!");

  client.onMessage(onMessageCallback);

  Serial.println("Connecting to WebSocket server...");
  if (client.connect(websocket_server, websocket_port, "/")){
    Serial.println("WebSocket Connected!");
  } else{
    Serial.println("WebSocket Connection Failed!");
  }

}

void loop() {
  client.poll();

  float data = random(100,200) / 10.0;
  // String message = "{\"data\":" + String(data) + "}";
  String message = "ESP-32 says Hi";
  client.send(message);
  Serial.println("Sent: " + message);
  delay(500);

}
