//ESPfire.ino
//Runs on an ESP8266 via the arduino core

#include <ESP8266WiFi.h>

void getIt();

const char* ssid     = "ddlabwifi";
const char* password = "balddbaldd";

const char* host = "bropdox.moore.dk";

void setup() {

  WiFi.persistent(false); //avoid weirdness
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

	getIt(); //første gang er gratis

}

unsigned long lastGet = 0;
unsigned long loopDelay = 30000; //every minute
void loop() {

  if(millis()>lastGet+loopDelay)
  	{
  		getIt();
  		lastGet = millis();
  	}

  yield();

}

void getIt()
{
  //String vindchillString;
  //float vindchill;
  int linecounter=0;
  String lines[3]="";

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 666;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  delay(1500);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    lines[linecounter++] = client.readStringUntil('\r');
  }

  if(lines[0]!="")
  {
  Serial.println("DATA:");
  Serial.print("line0: ");
  Serial.println(lines[0]);
  Serial.print("line1: ");
  Serial.println(lines[1]);
  Serial.print("line2: ");
  Serial.println(lines[2]);
  }

  Serial.println();
  Serial.println("closing connection");

}