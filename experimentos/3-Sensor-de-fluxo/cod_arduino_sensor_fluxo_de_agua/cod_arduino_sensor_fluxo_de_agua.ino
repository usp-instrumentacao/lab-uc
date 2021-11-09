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
 
float vazao; //Variável para armazenar valor de vazão
int contador_pulsos; //Variável para a quantidade de pulsos
float frequencia_sensor; //Variável para armazenar a frequência do sensor

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
  delay(2000);

  //Limpa o display 16x2
  display_lcd.clear();

  //Definição do pino do sensor e modo de interrupção
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), interrup_function, RISING); 
  
}
// End Setup ----------------------------------------------------------------------------------------------
 
// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{
  
 // Inicia o ciclo de contagem 
 contador_pulsos = 0;//zera o contador
 interrupts(); //habilita interrupção
 delay(1000); //aguarda 1 segundo
 noInterrupts(); //desabilita interrupção

 // Processamento dos dados obtidos
 frequencia_sensor = contador_pulsos; // pulsos/segundo
 vazao = frequencia_sensor/450; // litros/segundo --> 450 pulsos para 1 litro de água
 vazao = vazao * 60; // litros/minuto

 // Exibir valor no monitor serial do arduino
 Serial.println("Vazão [L/min] = " + String(vazao));

 // Exibir valor no display
 display_lcd.setCursor(0,0);
 display_lcd.print("Vazao [L/min]");
 display_lcd.setCursor(0,1);
 display_lcd.print(String(vazao));
  
}
// End Main Loop ------------------------------------------------------------------------------------------

// Funções auxiliares -------------------------------------------------------------------------------------
void interrup_function()  
{
 contador_pulsos++; //Incrementa o contador
}
