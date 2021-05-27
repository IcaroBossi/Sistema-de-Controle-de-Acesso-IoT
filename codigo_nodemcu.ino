// Projeto - Sistema de Controle de Acesso

//  include <Adafruit_MQTT.h>
//include <Adafruit_MQTT_Client.h>
//#include <Adafruit_MQTT_FONA.h>

// Baixar e incluir bibliotecas do ESP8266 e biblioteca MQTT
#include <ESP8266WiFi.h>   
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Parametros do WiFi
#define WLAN_SSID       "BOSSI2020"
#define WLAN_PASS       "iCARO987"
 
// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "icarobossi"
#define AIO_KEY         "aio_GLHm48VJ9QylmZZSseUSm7jKB5tI"  //Chave obtida através da minha conta no io.adafruit.com
 
// Criando uma classe WiFiClient ESP8266 para se conectar ao servidor MQTT.
WiFiClient client;
 
// Configurando a classe do cliente MQTT passando o cliente WiFi e o servidor MQTT e os detalhes de login.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
 
Adafruit_MQTT_Publish Attendance = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Projeto_ObjetosInteligentes_Icaro"); // Passa o nome do Feed criado no AdaFruit
 
char ID;

 
void setup() {
  Serial.begin(115200);
  Serial.println(F("Adafruit IO"));
 
  // Conectando ao ponto de acesso WiFi.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Conectando a  "));
  Serial.println(WLAN_SSID);
 
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
 
  Serial.println(F("WiFi conectado"));
  Serial.println(F("Endereço IP: "));
  Serial.println(WiFi.localIP());
 
  // conectando ao adafruit io
  connect();
 
}
 
// conectando ao adafruit io via MQTT
void connect() {
  Serial.print(F("Conectando ao Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println(F("Protocolo errado")); break;
      case 2: Serial.println(F("ID rejeitado")); break;
      case 3: Serial.println(F("Servidor indisponível")); break;
      case 4: Serial.println(F("Usuário / senha incorreta")); break;
      case 5: Serial.println(F("Não autenticado")); break;
      case 6: Serial.println(F("Falha ao assinar")); break;
      default: Serial.println(F("Conexão falhou")); break;
    }
 
    if(ret >= 0)
      mqtt.disconnect();
 
    Serial.println(F("Tentando conexão novamente ..."));
    delay(5000);
  }
  Serial.println(F("Adafruit IO Conectado!"));
}
 
void loop() {
  // ping adafruit io algumas vezes para garantir que ainda está conectado
  if(! mqtt.ping(3)) {
    // reconectado ao adafruit io
    if(! mqtt.connected())
      connect();
  }
   if ( Serial.available() ) { // Atualize e envie apenas após 1 segundo
   char a = Serial.read();
   ID = a;  
   
   if (! Attendance.publish(ID)) {                     //Publicar no Adafruit
      Serial.println(F("Falhou"));
    } else {
      Serial.println(F("Dados Enviados!"));
    }
}
}
