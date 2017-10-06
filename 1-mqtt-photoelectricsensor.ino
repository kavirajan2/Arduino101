/*********************************************************************
This is an MQTT series  example working codes.
  ------> http://www.adafruit.com/category/63_98
  
Written by Kavirajan ST  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
int sensorValue;

//sensorValue = analogRead(A0);

// Update these with values suitable for your network.

#define wifi_ssid "SSID-Name"
#define wifi_password "wifipassword"


#define mqtt_server "xx.xx.xx.xx"
//Hide the below two line if not set user credentials.
#define mqtt_user "username"
#define mqtt_password "password"

#define light_topic "/home/firstfloor/light"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();

  sensorValue = analogRead(A0);
  Serial.print(sensorValue, DEC); // prints the value read
  Serial.print(" \n"); // prints a space between the numbers
  client.publish(light_topic, String(sensorValue).c_str(), DEC);

  delay(1000); // wait 100ms for next reading

}
