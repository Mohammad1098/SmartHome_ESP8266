
//ard gnd ----> ard REST 
//esp tx ----> ard tx 
//esp rx ----> ard rx 
//esp vcc ----> ard 5v 
//esp ch_pd ----> ard 5v 
//esp gnd ----> ard gnd
//esp gpio0 ----> ard gnd  don't forget to disconnect it after upload code 
//esp gpio2 ----> ard 5v   don't forget to disconnect it after upload code 


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//These attributes used later to establish connection to AP and MQTT server
const char* ssid = "Null";
const char* password =  "Null";
const char* mqttServer = "Null";
const int mqttPort = 00000;
const char* mqttUser = "Null";
const char* mqttPassword = "Null";
WiFiClient espClient;
PubSubClient client(espClient);



void setup() {

  
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }
  //Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    //Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      //Serial.println("connected");  
 
    } else {
 
      //Serial.print("failed with state ");
      //Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.subscribe("esp/test");
 
}
 



void callback(char* topic, byte* message, unsigned int length) {
  //Serial.print("Message arrived on topic: ");
  //Serial.print(topic);
  String messageTemp;
  //Serial.println();

  for (int i = 0; i < length; i++) {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  //Serial.println();

  
  if (String(topic) == "esp/test") {
    if(messageTemp == "toggle2LightBulb"){
        Serial.print("toggle2LightBulb");
      
    }
    
  }
}


 
void loop() {
  client.loop();
}
