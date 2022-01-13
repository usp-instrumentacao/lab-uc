/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO MOTOR DE PASSO COM DRIVER ULN 2003
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
*		  https://randomnerdtutorials.com/esp32-stepper-motor-28byj-48-uln2003/
*     http://www.esp32learning.com/code/esp32-and-stepper-motor-example.php
*
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <LiquidCrystal.h>
#include <Stepper.h>

// Definição de pinos para o módulo ULN2003
#define ULN2003_IN1 27
#define ULN2003_IN2 26
#define ULN2003_IN3 25
#define ULN2003_IN4 33

// Definição de constante para o número de passos para completar uma revolução no motor, esse valor
// irá ser específico para cada motor utilizado
const int steps_per_rev = 2048;  

//Declaração do objeto motor de passo
Stepper my_step_motor(steps_per_rev, ULN2003_IN1, ULN2003_IN3, ULN2003_IN2, ULN2003_IN4);

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
int dt=100; //ms


// Setup --------------------------------------------------------------------------------------------------
void setup() {
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Ajuste de velocidade de rotação do motor de passo em RPM
  my_step_motor.setSpeed(6);
  
  //Inicializa o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Delay de inicialização
  delay(1000);
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop() 
{
  
  int steps_number = 0;
  float ang = 0;
  
  //Posição 30º sentido horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 30 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("horario");
  
  ang = 30;
  steps_number = round((ang * steps_per_rev) / 360);
  my_step_motor.step(steps_number);
  release_servo_pins();
  
  delay(5000);
  
  
  //Retorno Posição 0º sentido anti-horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 0 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("anti-horario");
  
  my_step_motor.step(-steps_number);
  release_servo_pins();
  
  delay(5000);

  //Posição 90º sentido horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 90 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("horario");
  
  ang = 90;
  steps_number = round((ang * steps_per_rev) / 360);
  my_step_motor.step(steps_number);
  release_servo_pins();
  
  delay(5000);
  
  //Retorno Posição 0º sentido anti-horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 0 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("anti-horario");
  
  my_step_motor.step(-steps_number);
  release_servo_pins();
  
  delay(5000);

  //Posição 180º sentido horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 180 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("horario");
  
  ang = 180;
  steps_number = round((ang * steps_per_rev) / 360);
  my_step_motor.step(steps_number);
  release_servo_pins();
  
  delay(5000);

  //Retorno Posição 0º sentido anti-horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 0 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("anti-horario");
  
  my_step_motor.step(-steps_number);
  release_servo_pins();
  
  delay(5000);

  //Posição 360º sentido horário
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Target: 360 dg");
  display_lcd.setCursor(0,1);
  display_lcd.print("horario");
  
  ang = 360;
  steps_number = round((ang * steps_per_rev) / 360);
  my_step_motor.step(steps_number);
  release_servo_pins();
  
  delay(5000);
  
}
//End main loop -------------------------------------------------------------------------------------------

// Funções auxiliares -------------------------------------------------------------------------------------
void release_servo_pins()
{
  digitalWrite(ULN2003_IN1, LOW);
  digitalWrite(ULN2003_IN2, LOW);
  digitalWrite(ULN2003_IN3, LOW);
  digitalWrite(ULN2003_IN4, LOW);
}
// End Funções auxiliares ---------------------------------------------------------------------------------
