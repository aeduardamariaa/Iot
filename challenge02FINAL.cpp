#include <WiFi.h>
#include <Arduino.h>
#include "PubSubClient.h"
#include "DHT.h"
#include <FirebaseESP32.h>
#include <string.h>

const uint8_t PIN_INPUT = 26;
const uint8_t PIN_LED = 25;

long tempo =0;

/*WIFI*/
const char* WIFI_SSID = "Vivo-Internet-BF17";
const char* WIFI_PW = "78814222";

/*MQTT*/
const char* MQTT_BROKER = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char* MQTT_USERNAME = "";
const char* MQTT_PASSWORD = "";

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

/*FIREBASE*/
const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com/";
const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

FirebaseData fbdo;
FirebaseAuth fbauth;
FirebaseConfig fbconfig;

/*Constantes DHT 11 e DHT 22*/
#define DHTTYPE DHT11

/*Variaveis*/
DHT dht(PIN_INPUT, DHTTYPE);

bool connectWiFi(const char* ssid, const char* pw);
void callback(char* topic, byte* payload, unsigned int length);
void connectFirebase(const char* fb_host, const char* fb_key);
float* readDHT();

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);//inicializa comunicação via USB, e passa o valor da velocidade da comunicação

  dht.begin();
  connectWiFi(WIFI_SSID, WIFI_PW);

  connectFirebase(FB_HOST, FB_KEY);

  mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);
  mqtt_client.setCallback(callback);

  while (!mqtt_client.connected())
  {
    String client_id = "mqttx_32fef669";
    client_id += String(WiFi.macAddress());

    if(mqtt_client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
    {
      Serial.println("Conexao MQTT bem sucedida");
    }
  }
  mqtt_client.subscribe("iiot-dta/check");
  mqtt_client.subscribe("iiot-dta/request");
}

void loop()
{
  if (millis() - tempo > 30000)
  {
    float* data = readDHT();

    FirebaseJson json;

    json.set("/temperature", data[1]);
    json.set("/humidity", data[0]);

    if (Firebase.updateNode(fbdo, "challenge02/subsys_05/", json))
    {
      Serial.println("Dado salvo com sucesso!");
    }
    else
    {
      Serial.print("Falha: ");
      Serial.println(fbdo.errorReason().c_str());
    }

    if (data[1] > 30)
    {
      mqtt_client.publish("iiot-dta/request", "10 MARIA");
    }
    mqtt_client.publish("testdta", "credoooooooooooo");
  }
  mqtt_client.loop();
}

bool connectWiFi(const char* ssid, const char* pw)
{
  WiFi.mode(WIFI_STA); //modo estático, não muda o IP
  WiFi.disconnect();

  int qtde_wifi = WiFi.scanNetworks(); //retorna um int com o número de rede disponíveis

  if(qtde_wifi == 0)
  {
    return false;
  }

  WiFi.begin(WIFI_SSID, WIFI_PW); //iniciliza uma rede Wifi

  Serial.print("Conectando");
  int tentativa = 0;

  while(WiFi.status() != WL_CONNECTED)
  {
    tentativa ++;

    if (tentativa > 300)
    {
      return false;
    }

    Serial.print(".");
    delay(200);
  }
  Serial.print("Conectado com o IP: ");
  Serial.println(WiFi.localIP());

  return true;
}

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.printf("Mensagem recebida no topico: %s", topic);
    Serial.println();

    String menssage = "";

    for(uint16_t i=0; i < length; i++)
    {
      menssage += static_cast<char>(payload[i]);
    }
    Serial.println(menssage);

    if (strcmp(topic, "iiot-dta/check") == 0)
    {
      if (menssage == "100")
      {
        mqtt_client.publish("iiot-dta/check", "1 MARIAAAAAAAAA");
      }
      else if (menssage == "200")
      {
        digitalWrite(PIN_LED, 1);
        delay(5000);
        digitalWrite(PIN_LED, 0);
      }
    }
    else if (strcmp(topic, "iiot-dta/request") == 0)
    {
      if (menssage == "100")
      {
        float* data = readDHT();

        FirebaseJson json;

        json.set("/temperature", data[1]);
        json.set("/humidity", data[0]);

        if (Firebase.updateNode(fbdo, "challenge02/subsys_05/", json))
        {
          Serial.println("Dado salvo com sucesso!");
        }
        else
        {
          Serial.print("Falha: ");
          Serial.println(fbdo.errorReason().c_str());
        }
      }
    }

    Serial.println();
}

void connectFirebase(const char* fb_host, const char* fb_key)
{
  fbconfig.database_url = fb_host;
  fbconfig.signer.tokens.legacy_token = fb_key;

  fbdo.setBSSLBufferSize(4096, 1024);

  Firebase.reconnectWiFi(true);
  Firebase.begin(&fbconfig, &fbauth);
}

float* readDHT()
{
  static float data[2];
  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if(isnan(humidade)|| isnan(temperatura))
  {
    Serial.println("Falha na leitura do sendor DHT");
    return NULL;
  }
  Serial.printf("Humidade: %4.2f\nTemperatura: %7.2f\n\n", humidade, temperatura);
  data[0] = humidade;
  data[1] = temperatura;

  delay(5000);
  return data;
}

