/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO MÓDULO SENSOR DE FLUXO BASEADO EM SENSOR DE EFEITO HALL YF-S201B (CALIBRAÇÃO DO MÓDULO)
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
* Referências:
*         https://microcontrollerslab.com/water-flow-sensor-pinout-interfacing-with-arduino-measure-flow-rate/
*         https://how2electronics.com/iot-water-flow-meter-using-esp8266-water-flow-sensor/
*         
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <LiquidCrystal.h>

//Definição pino do botão START E STOP
#define START_BTN_PIN 23
#define STOP_BTN_PIN 22

//Definição pino do sensor 
#define SENSOR_PIN 34

// Definição de pinos para o display 16x2
#define DISPLAY_RS 15
#define DISPLAY_EN 2
#define DISPLAY_D4 4
#define DISPLAY_D5 16
#define DISPLAY_D6 17
#define DISPLAY_D7 5

// Declaração do display lcd (rs, en, d4, d5, d6, d7);
LiquidCrystal display_lcd(DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

// Declaração de variáveis globais
int contador_pulsos; //Variável para a quantidade de pulsos
int aux_plot=0;

// Setup --------------------------------------------------------------------------------------------------
void setup() {
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Delay de inicialização
  delay(2000);

  //Limpa o display 16x2
  display_lcd.clear();

  //Definição do pino do sensor e modo de interrupção
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), interrup_function1, RISING);

  //Definição do pino do botão START e modo de interrupção
  pinMode(START_BTN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(START_BTN_PIN), interrup_function2, RISING); 

  //Definição do pino do botão STOP e modo de interrupção
  pinMode(STOP_BTN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(STOP_BTN_PIN), interrup_function3, RISING); 

  // Exibir msg no serial do arduino
  Serial.println("Aguardando início (botão start)...");

  // Exibir msg no display
  display_lcd.setCursor(0,0);
  display_lcd.print("Aguardando...");
  display_lcd.setCursor(0,1);
  display_lcd.print("Aguardando...");
 
}
// end Setup ----------------------------------------------------------------------------------------------
 
// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{
  
  if (aux_plot==1)
  {
   // Exibir valor no monitor serial do arduino
   Serial.println("Número de pulsos para fluir 1 litro de água = " + String(contador_pulsos));

   // Exibir valor no display
	 display_lcd.clear();
   display_lcd.setCursor(0,0);
   display_lcd.print("Num. pulsos/L:");
   display_lcd.setCursor(0,1);
   display_lcd.print(String(contador_pulsos));

   aux_plot=0;
   interrupts(); //habilita interrupção   
  }
  
}
// End Main Loop ------------------------------------------------------------------------------------------

// Funções auxiliares -------------------------------------------------------------------------------------

void interrup_function1()
{
   contador_pulsos++; //Incrementa o contador
}

void interrup_function2() //Botão START 
{
   while (digitalRead(START_BTN_PIN)==HIGH)
   {
      contador_pulsos = 0;//zera o contador
   }
}

void interrup_function3()  //Botão STOP
{
   aux_plot=1;
   noInterrupts(); //desabilita interrupção
}

// End Funções auxiliares ---------------------------------------------------------------------------------
