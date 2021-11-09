/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO SENSORES DE TEMPERATURA DS18B20 (DESCOBRINDO ENDEREÇO I2C DOS SENSORES)
* 
* Autores:
*         Carlos Eduardo Gallo Filho
*         Ernesto Edgar Mazón Valadez 
*         Fábio Eduardo Flores de Lima
*         Ricardo Ricci Bordonal
*         Prof. Dr. Theo Zeferino Pavan
*         
* Descrição:
*         Códigos auxiliares para o utilização de módulos sensores de diversos tipos aliados 
*         ao microcontrolador ESP32 por meio da placa de desenvolvimento ESP32-DEVKIT1. Os códigos
*         também são compatíveis placas Arduino, porém, é necessário revisar a compatibilidade de  
*         funções dos pinos.
*         
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <OneWire.h>

//Definição pino do sensor 
#define SENSOR_PIN 32

// Declaração do objeto OneWire 
OneWire dallas_sensor(SENSOR_PIN);  //declaração de objeto 

// Setup --------------------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{
  
  Serial.println("Início verificação de endereço de sensor Dallas DS18B20");
  Serial.println();

  byte i;
  byte addr[8];
  i=0;
  while(dallas_sensor.search(addr)) 
  {
    Serial.print("Sensor encontrado = { ");
    for (i=0; i<8; i++) 
    {
      Serial.print("0x");
      Serial.print(addr[i], HEX);
      if(i!=7)
      {
        Serial.print(", ");
      }
      else
      {
        Serial.print(" }");
      }
    }
  }
  if(i==0)
  {
    Serial.print("Nenhum sensor encontrado");
  }
  Serial.println();
  
  Serial.println("Fim da verificação");
  dallas_sensor.reset_search();
  
  delay(500);
    
}
// End Main Loop ------------------------------------------------------------------------------------------
