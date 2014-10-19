#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>

int value;
float input = 0;

byte mac[]    = {  0x90, 0xA2, 0xAA, 0x33, 0x59, 0x5A };
byte server[] = { 172, 16, 0, 70 };
byte ip[]     = { 172, 16, 0, 133 };

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

void callback(char* topic, byte* payload, unsigned int length)
{
  payload[length] = '\0';
  int value = atoi((char * ) payload);
  //Serial.println(value);
  analogWrite(6, value);
}



void setup() {
  Ethernet.begin(mac, ip);
  //Serial.begin(9600);
  pinMode(6, OUTPUT);
}

int scaleToMeter(float input) {
  // math scale function with to points (255|40), (122|20)
  return 6.65 * input - 11;
}

void loop() {
  
  
  if(client.connected())
  {
      client.loop();   
  }
  else
  {
    if(client.connect("arduinoAnalogMeter")) {
      client.subscribe("byteli/analogMeter");
    }
    else {
      delay(5000);
    }
  }
 
  
  
}
