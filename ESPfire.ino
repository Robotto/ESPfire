//ESPfire.ino
//Runs on an ESP8266 via the arduino core

#include <ESP8266WiFi.h>

const char* ssid     = "notReallyAWifi";
const char* password = "getOuttaHereYouSexyHackerYou";

const char* host = "odin.dk";

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

int value = 0;

void loop() {

  delay(60000); //every minute
  
  int linecounter=0;
  //String vindchillString;
  //float vindchill;
  //String line="";

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/RSS/RSS.aspx?beredskabsID=1110";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    line = client.readStringUntil('\r');
    linecounter++;
    serial.println(line);
    //if(linecounter==31) vindchillString=line.substring(53,58);  //magic numbers galore :P
  }

  if(line!="")
  {
  //vindchill=vindchillString.toFloat();
  //Serial.println("String: " + String(vindchillString));
  //Serial.println("float: " + String(vindchill));
  }

  Serial.println();
  Serial.println("closing connection");
}