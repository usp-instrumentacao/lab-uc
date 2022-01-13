/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO SENSOR ÓPTICO REFLEXIVO
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
#include <LiquidCrystal.h>

//Definição pino do sensor 
#define SENSOR_PIN_ANALOG 25
#define SENSOR_PIN_DIGITAL 26
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
const int threshold_value_volts = 3.1; //V
const int threshold_value_bits =(int)(4095/3.3)*threshold_value_volts; //bits

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

  //Definição do pino do sensor digital e modo de interrupção
  pinMode(SENSOR_PIN_DIGITAL, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_DIGITAL), interrup_function, FALLING); 

  //Definição do pino do sensor anlógico e led
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
  delay(dt);
}
// End Main Loop ------------------------------------------------------------------------------------------

// Funções auxiliares -------------------------------------------------------------------------------------
void interrup_function()  
{
	
 digitalWrite(LED_PIN,HIGH); //acende o led caso ocorra interrupção (aproximação do objeto)
 
 int aux = analogRead(SENSOR_PIN_ANALOG);
 while( aux < threshold_value_bits ) // mantém o led acesso enquanto o objeto estiver próximo o suficiente
 {
  delay(5);
  aux =analogRead(SENSOR_PIN_ANALOG);
 }
 
 digitalWrite(LED_PIN,LOW); //apaga o led com o afastamento do objeto
 
}
