#include <ESP8266WiFi.h>

const char* ssid = "MSI_XIV"; //Change to your Access Point
const char* password = "wp127001"; //Change to your Access Point PW

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  server.begin(); //Start working as a server
  Serial.println("Server starts.");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n------------- [Client connected] ------------");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.print("   * Receive from Client: ");
        Serial.println(data);          
      }
    }
    delay(10);
    client.stop();
    Serial.println("--------------- Disconnect, Wait 15 Seonds ---------------");
  }
}

