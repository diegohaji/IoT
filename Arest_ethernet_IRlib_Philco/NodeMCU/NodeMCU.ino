/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  This example illustrate the cloud part of aREST that makes the board accessible from anywhere
  See the README file for more details.

  Written in 2016 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>


#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_LED 4  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
#define LED_Status 0 //LED de sinalização para os eventos

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.
// Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Create aREST instance
aREST rest = aREST(client);

// Unique ID to identify the device for cloud.arest.io
char* device_id = "091193";

// WiFi parameters
const char* ssid = "Josiele";
const char* password = "NYF71900";

//Variáveis utilizadas para acionar as funções através de botões 
// int buttonState1, buttonState2, buttonState3 , buttonState4, buttonState5, buttonState6;

// Functions
void callback(char* topic, byte* payload, unsigned int length);

//Variaveis armazenando os codigos das funcoes
#define RAW_DATA_LEN 68
uint16_t power[RAW_DATA_LEN] ={9000, 4550, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 580, 1700, 550, 1700, 550, 580, 550, 1700, 550, 1700, 550, 1700, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 580, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 550, 1711, 550, 1700, 550 };
uint16_t vol_mais[RAW_DATA_LEN]= {9000,4550,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,580,550,1700,550,580,550,1700,550,1700,550,580,550,1700,550,580,550,580,550,580,550,1700,550,580,550,580,550,1700,550,580,550,1700,550,1700,550,1700,550 };
uint16_t vol_menos[RAW_DATA_LEN]= {9000,4550,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,1700,550,580,550,580,550,580,550,1700,550,580,550,1700,550,580,550,580,550,1700,550,1700,550,1700,550 };
uint16_t canal_mais[RAW_DATA_LEN]= {9000,4550,550,580,550,550,550,580,550,580,550,580,550,580,550,580,550,580,550,1700,550,1700,550,1700,550,1700,580,1700,550,1700,550,580,550,1700,550,580,550,580,550,1700,550,580,550,1700,550,580,550,580,550,580,550,1700,550,1700,550,580,550,1700,550,580,550,1700,550,1700,550,1700,550};
uint16_t canal_menos[RAW_DATA_LEN]={9000,4550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,1700,580,1700,580,1700,580,1700,580,1700,580,1700,580,550,580,1700,580,550,580,550,580,550,580,1700,580,1700,580,550,580,550,580,550,580,1700,580,1700,580,1700,580,550,580,550,580,1700,580,1700,580,1700,580 };

#define RAW_DATA_LEN2 198 //Valor exclusivo para o AC Rheem
uint16_t power_ac[RAW_DATA_LEN2] ={6100,7400,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,580,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,1700,550,580,550,1700,550,1700,550,1700,550,1700,550,1700,550,580,550,1700,550,1700,550,580,550,580,550,580,550,580,550,580,550,1700,550,580,550,580,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,580,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,580,550,1700,550,1700,550,7400,550};

int tv_power(String a){
  irsend.sendRaw(power,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
  Serial.println("tv_power");
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  return 0;
}

int tv_canal_mais(String b){
  irsend.sendRaw(canal_mais,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
  Serial.println("tv_canal_mais");
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  return 0;
}

int tv_canal_menos(String c){
  irsend.sendRaw(canal_menos,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
  Serial.println("tv_canal_menos");
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  return 0;
}

int tv_vol_mais(String d){
  irsend.sendRaw(vol_mais,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
  Serial.println("tv_vol_mais.");
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  return 0;
}

int tv_vol_menos(String e){
  irsend.sendRaw(vol_menos,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
  Serial.println("tv_vol_menos");
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  return 0;
}

int ac_power(String a){
  irsend.sendRaw(power_ac,RAW_DATA_LEN2,38);//Pass the buffer,length, optionally frequency
  Serial.println("ac_power");
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  digitalWrite(LED_Status,HIGH);
  delay(50);
  digitalWrite(LED_Status,LOW);
  delay(50);
  return 0;
}
void setup(void)
{
  // Start Serial
  Serial.begin(115200);
  // Set callback
  client.setCallback(callback);

  //LED de sinalização para os eventos
  pinMode(LED_Status,OUTPUT);
  
  //Ativando o emissor de IR
  irsend.begin();
  
  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id(device_id);
  rest.set_name("node1");

//Declares the function in the Arduino sketch for Arest
  rest.function("power",tv_power); //o primeiro termo é como arest vai ler essa funcao e o segundo é o nome da função declarada dentro do sketch
  rest.function("vol_mais",tv_vol_mais);
  rest.function("vol_menos",tv_vol_menos);
  rest.function("canal_mais",tv_canal_mais); 
  rest.function("canal_menos",tv_canal_menos);
  rest.function("ac_power",ac_power);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(LED_Status,HIGH);
  delay(1000);
  digitalWrite(LED_Status,LOW);
  delay(500);
  digitalWrite(LED_Status,HIGH);
  delay(1000);
  digitalWrite(LED_Status,LOW);
  delay(500);
  

  // Set output topic
  char* out_topic = rest.get_topic();
       
}

void loop() {
   
      
  // Connect to the cloud
  rest.handle(client);

  // Acionamento das funções a partir de botões, na ordem são D0 = GPIO16, D1 = GPIO5, D5 = GPIO14, D6 = GPIO12, D7 = GPIO13, D8 = GPIO15
  // buttonState1 = digitalRead(16);  //tv_vol_mais
  // buttonState2 = digitalRead(5); //tv_vol_menos
  // buttonState3 = digitalRead(14);  //tv_canal_mais
  // buttonState4 = digitalRead(12);  //tv_canal_menos
  // buttonState5 = digitalRead(13);  //tv_power
  // buttonState6 = digitalRead(15);  //ac_power
   
  // if (buttonState1 == HIGH) { //D0
    // tv_vol_mais("null");
  // delay(500);
  // }
  // if (buttonState2 == HIGH) { //D1
    // tv_vol_menos("null");
  // delay(500);
  // }
  // if (buttonState3 == HIGH) { //D5
    // tv_canal_mais("null");
  // delay(500);
  // }
  // if (buttonState4 == HIGH) { //D6
    // tv_canal_menos("null");
  // delay(500);
  // }
  // if (buttonState5 == HIGH) { //D7
    // tv_power("null");
  // delay(500);
  // }
  // if (buttonState6 == HIGH) { //D8
    // ac_power("null");
  // delay(500);
  // }
}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  rest.handle_callback(client, topic, payload, length);
  digitalWrite(LED_Status,HIGH);
  delay(500);
  digitalWrite(LED_Status,LOW);
  delay(500);
  digitalWrite(LED_Status,HIGH);
  delay(500);
  digitalWrite(LED_Status,LOW);
  delay(500);
  digitalWrite(LED_Status,HIGH);
  delay(500);
  digitalWrite(LED_Status,LOW);
  delay(500);

}





