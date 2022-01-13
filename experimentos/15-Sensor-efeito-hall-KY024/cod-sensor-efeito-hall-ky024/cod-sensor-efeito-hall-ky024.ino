/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO MÓDULO SENSOR DE EFEITO HALL KY-024
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
* Referências:
*         https://microcontrollerslab.com/water-flow-sensor-pinout-interfacing-with-arduino-measure-flow-rate/
*         https://how2electronics.com/iot-water-flow-meter-using-esp8266-water-flow-sensor/
*         
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <LiquidCrystal.h>

//Definição pinos do sensor e led
#define SENSOR_PIN_ANALOG 26
#define SENSOR_PIN_DIGITAL 25
#define LED_PIN 27

// Definição de pinos para o display 16x2
#define DISPLAY_RS 15
#define DISPLAY_EN 2
#define DISPLAY_D4 4
#define DISPLAY_D5 16
#define DISPLAY_D6 17
#define DISPLAY_D7 5

// Declaração do display lcd (rs, en, d4, d5, d6, d7);
LiquidCrystal display_lcd(DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

// Declaração variáveis globais
const int dt=50; // ms
int analog_read=0;

// Setup --------------------------------------------------------------------------------------------------
void setup() 
{
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Delay de inicialização
  delay(10);

  //Limpa o display 16x2
  display_lcd.clear();

  //Definição do pino do sensor digital, anlógico e led
  pinMode(SENSOR_PIN_DIGITAL, INPUT); 
  pinMode(SENSOR_PIN_ANALOG, INPUT);
  pinMode(LED_PIN, OUTPUT);

  //Display
  display_lcd.setCursor(0,0);
  display_lcd.print("Pronto");
  
}
// End Setup ----------------------------------------------------------------------------------------------
 
// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{

  //Leitura analógica do sensor
  analog_read = analogRead(SENSOR_PIN_ANALOG);

  //Leitura digital do sensor
  if(digitalRead(SENSOR_PIN_DIGITAL)==HIGH)
  {
    digitalWrite(LED_PIN,HIGH);
  }
  else
  {
    digitalWrite(LED_PIN,LOW);
  }
  
  //Display
  display_lcd.setCursor(0,0);
  display_lcd.print("Read Value:");
  display_lcd.setCursor(0,1);
  display_lcd.print(String(analog_read));
  
  delay(dt);
}
// End Main Loop ------------------------------------------------------------------------------------------
