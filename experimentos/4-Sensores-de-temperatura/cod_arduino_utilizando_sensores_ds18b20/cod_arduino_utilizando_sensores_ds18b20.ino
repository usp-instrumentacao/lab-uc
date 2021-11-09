/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO SENSORES DE TEMPERATURA DS18B20
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
#include <DallasTemperature.h>
#include <LiquidCrystal.h> 

//Definição pino do sensor (comunicação i2c)
#define SENSOR_PIN 32

// Definição de pinos para o display 16x2
#define DISPLAY_RS 15
#define DISPLAY_EN 2
#define DISPLAY_D4 4
#define DISPLAY_D5 16
#define DISPLAY_D6 17
#define DISPLAY_D7 5

// Declaração do objetos sensores
OneWire dallas_sensors(SENSOR_PIN);
DallasTemperature DS18B20_sensors(&dallas_sensors);
DeviceAddress DS18B20_1 = { 0x28, 0xCD, 0x1C, 0x8C, 0xB, 0x0, 0x0, 0x9C }; //sensor 1
DeviceAddress DS18B20_2 = { 0x28, 0x8B, 0x9, 0x8C, 0xB, 0x0, 0x0, 0xF5 }; //sensor 2
DeviceAddress DS18B20_3 = { 0x28, 0xDA, 0xDA, 0x8C, 0xB, 0x0, 0x0, 0xFC }; //sensor 3

// Declaração do display lcd (rs, en, d4, d5, d6, d7);
LiquidCrystal display_lcd(DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

// Declaração variáveis globais
int dt=100; //ms
float temp_value1=0.0;
float temp_value2=0.0;
float temp_value3=0.0;

// Setup --------------------------------------------------------------------------------------------------
void setup() 
{
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Inicia sensores de temperatura DS18B20
  DS18B20_sensors.begin();
  DS18B20_sensors.setResolution(DS18B20_1, 12); //configura sensor resolução em bits
  DS18B20_sensors.setResolution(DS18B20_2, 12); //configura sensor resolução em bits
  DS18B20_sensors.setResolution(DS18B20_3, 12); //configura sensor resolução em bits
  
  //Delay de inicialização
  delay(2000);

  //Limpa o display 16x2
  display_lcd.clear();
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{

  //Requisita valores de temperatura dos sensores
  DS18B20_sensors.requestTemperatures();
  temp_value1 = DS18B20_sensors.getTempC(DS18B20_1);
  temp_value2 = DS18B20_sensors.getTempC(DS18B20_2);
  temp_value3 = DS18B20_sensors.getTempC(DS18B20_3);
  
  //Exibe valores de temperatura no monitor serial
  Serial.println("Temperatura Sensor 1: " + String(temp_value1) + " ºC");
  Serial.println("Temperatura Sensor 2: " + String(temp_value2) + " ºC");
  Serial.println("Temperatura Sensor 3: " + String(temp_value3) + " ºC");
  Serial.println();
  
  //Exibir valores no display
  display_lcd.setCursor(0,0);
  display_lcd.print("Sensor 1: ");
  display_lcd.setCursor(10,0);
  display_lcd.print(String(temp_value1,1));
  display_lcd.setCursor(15,0);
  display_lcd.print("ºC");
  
  display_lcd.setCursor(0,1);
  display_lcd.print("Sensor 2: ");
  display_lcd.setCursor(10,1);
  display_lcd.print(String(temp_value2,1));
  display_lcd.setCursor(15,1);
  display_lcd.print("ºC");
  
  // loop delay
  delay(dt);
  
}
// End Main Loop ------------------------------------------------------------------------------------------
