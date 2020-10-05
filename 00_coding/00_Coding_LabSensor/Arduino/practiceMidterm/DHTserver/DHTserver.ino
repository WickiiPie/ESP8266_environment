#include <ESP8266WiFi.h>
#include <DHT.h>
DHT dht(D2, DHT11);
int red = D0;
int green = D1;
int buzzer = D3;
int poten = A0;
const char* ssid = "-XIV-5s"; //Access Point SSID
const char* password = "wp127001"; //Access Point Password
WiFiServer server(80);
unsigned char status_green = 0;
unsigned char status_red = 0;
unsigned char status_buzzer = 0;


void setup() {
  dht.begin();
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,HIGH);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)

  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/green") != -1)
  {

    if (status_green == 0) {
      digitalWrite(green, LOW);
    } else if (status_green == 1) {
      digitalWrite(green, HIGH);

    } status_green = !status_green;


  } else if (req.indexOf("/red") != -1)
  {

    if (status_red == 0) {
      digitalWrite(red, LOW);
    } else if (status_red == 1) {
      digitalWrite(red, HIGH);

    } status_red = !status_red;


  } else if (req.indexOf("/buzzer") != -1)
  {

    digitalWrite(buzzer, LOW);
    delay(3000);
    digitalWrite(buzzer, HIGH);
  }
 //Keep the HTML in to the String variable named "web"
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>Sensor Monitor</h1>\r\n";
  web += "<p>\r\n";
  web += "Temperature = ";
  web += String(dht.readTemperature());
  //web += " C";
  web += "<p>\r\n";
  web += "Humidity = ";
  web += String(dht.readHumidity());
  //web += " %";
  web += "</p>\r\n";
  web += "Light = ";
  web += String(analogRead(A0));
  web += "<p>\r\n";
  //========================================
  web += "<h1>Controller</h1>\r\n";
  web += "<p>\r\n";

  if (status_red == 0)
    web += "RED ON\r\n";
  else if (status_red == 1)
    web += "RED OFF\r\n";

 // if (status_buzzer == 0)
  //  web += "buzzer ON\r\n";
  //else if (status_buzzer == 1)
   // web += "buzzer OFF\r\n";

  web += "</p>\r\n";
  web += "<br>\r\n";
  if (status_green == 0)
    web += "Green ON\r\n";
  else if (status_green == 1)
    web += "Green OFF\r\n";


  web += "</p>\r\n";
  web += "<p>\r\n";


  web += "<a href=\"/green\">\r\n";
  web += "<button>Green</button>\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  //=========================
  web += "<a href=\"/red\">\r\n";
  web += "<button>Red</button>\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/buzzer\">\r\n";
  web += "<button>buzzer</button>\r\n";
  web += "</a>\r\n";

  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}

