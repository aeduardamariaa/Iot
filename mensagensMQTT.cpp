#include <WiFi.h>
#include<Arduino.h>
#include "PubSubClient.h"

/*Constantes*/
const char* WIFI_SSID = "Shrek";
const char* WIFI_PWD = "chorameliga";

const char* MQTT_BROKER = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char* MQTT_USERNAME = "";
const char* MQTT_PASSWORD = "";

/*Variaveis*/
WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

bool connectWiFi(const char* ssid, const char* pwd)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, pwd);

  uint8_t current_trial = 0;

  Serial.print("Conectando");
  while(WiFi.status() != WL_CONNECTED)
  {
    current_trial++;

    if (current_trial > 300)
    {
      return false;
    }
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.println("Conectado!");

  Serial.print("Conectado com o IP: ");
  Serial.println(WiFi.localIP());

  return true;
}

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.printf("Mensagem recebida no topico %s: ", topic);

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup()
{
    //serial comunicação
    Serial.begin(115200);

    //wifi
    connectWiFi(WIFI_SSID, WIFI_PWD);

    //MQTT
    mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);
    mqtt_client.setCallback(callback);

    while (!mqtt_client.connected())
    {
        String client_id = "mqttx_dta_esp_subsys_05";
        client_id += String(WiFi.macAddress());

        if (mqtt_client.connected(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
        {
            Serial.println("Conexao MQTT bem sucedida");
        }
    }

    mqtt_client.subscribe("testdta");
}
void loop()
{
    mqtt_client.publish("testdta", "credoooooooooooo");

    delay(5000);
}
