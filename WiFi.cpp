#include<WiFi.h>

void setup() 
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); //modo estático, não muda o IP
  WiFi.disconnect();
}

void loop() 
{
  int qtde_wifi = WiFi.scanNetworks(); //retorna um int com o número de rede disponíveis

  if(qtde_wifi == 0)
  {
    return;
  }

  for(int i=0; i < qtde_wifi; i++)
  {
    Serial.printf("Quantidade de redes disponíveis: %i\n", qtde_wifi);
    Serial.print("Indice: "); //Print só aceita um tipo de dado
    Serial.print(i + 1);
    Serial.print(" SSID: ");
    Serial.print(WiFi.SSID(i)); //Nome da rede
    Serial.print(" RSSI: ");
    Serial.print(WiFi.RSSI(i)); // Intensidades
    Serial.print((" Auth: "));
    Serial.print(WiFi.encryptionType(i)); // autenticação
    Serial.println();
  }
  delay(3000);
}
