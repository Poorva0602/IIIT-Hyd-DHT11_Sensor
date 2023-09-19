#include <DHT.h>
#include <ESP8266WiFi.h>
String apikey = "UY3CGPJ0EBGUCC4Y";

const char *ssid = "RAHUL 4G";
const char *password = "poorva2000";
const char* server = "api.thingspeak.com";

#define DHTPIN D3 

DHT dht(DHTPIN, DHT11);
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();

  Serial.println("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi cpnnected");

}
void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t))
  {
    Serial.println("failed to read");
    return;
  }
   if(client.connect(server,80))
  {
    
    String postStr = apiKey;
    postStr +="&field1=";
    postStr +=  String(t);
    postStr +="&field2=";
    postStr +=  String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print("postStr");
    
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degree Celcius, Humidity: ");
    Serial.print(h);
    Serial.print("%. Send to Thingspeak.");
   }

    client.stop();

    Serial.print("waiting.....");
    delay(10000);
}
  }
