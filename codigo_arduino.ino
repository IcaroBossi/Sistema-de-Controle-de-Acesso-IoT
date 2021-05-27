// Projeto - Sistema de Controle de Acesso

// Baixar e incluir a biblioteca MFRC522
#include <SPI.h>
#include <MFRC522.h>
#include "SoftwareSerial.h"
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crie uma instância MFRC522.
SoftwareSerial ser(2,3); // RX, TX 

void setup() 
{
  Serial.begin(9600);   // Inicie uma comunicação serial
  ser.begin (115200);
  SPI.begin();      // Iniciar barramento SPI
  mfrc522.PCD_Init();   // Iniciar MFRC522
  Serial.println("Coloque o cartão RFID para ser feita a leitura ...");
  Serial.println();
  pinMode(7, OUTPUT); // Pino que conecta o rele e o led verde
 
}
void loop() 
{
  // Procurando pelos Cartoes (Tags)
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Selecione um dos cartões
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostrar UID no monitor serial
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Usuario No./Nome:    ");
  content.toUpperCase();
  if (content.substring(1) == "99 09 25 B3" ) //UID do 1º cartão
  {
    Serial.println("1-Icaro Bossi de Farias");
    ser.write(1);
    Serial.println();
    digitalWrite(7, HIGH); // Abre o relé e acende o led
    delay(3000);           // espera 3 segundos
    digitalWrite(7, LOW);  // Fecha relé e apaga o led
    
    delay(3000);
  }
   if (content.substring(1) ==  "EA A3 9F 07" ) //UID do 2º cartão
  {
    Serial.println("2-José");
    ser.write(2);
    Serial.println();
    digitalWrite(7, HIGH); // Abre o relé e acende o led
    delay(3000);           // espera 3 segundos
    digitalWrite(7, LOW);  // Fecha relé e apaga o led
    
    delay(3000);
  }
  }
