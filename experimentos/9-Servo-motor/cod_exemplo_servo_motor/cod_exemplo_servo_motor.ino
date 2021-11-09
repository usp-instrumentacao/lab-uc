/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO SERVO MOTOR COM ESP32
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
*		  https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/
*     https://www.instructables.com/Interfacing-Servo-Motor-With-ESP32/
*     https://www.arduino.cc/reference/en/libraries/esp32servo/
*     https://dronebotworkshop.com/esp32-servo/
*     https://www.arduino.cc/en/Reference/ServoAttach
*
* Licença: GNU GPLv3
*
*/

//Incluir bibliotecas
#include <LiquidCrystal.h>
#include <ESP32Servo.h>

//Definição de pino para sinal PWM do servo
#define SERVO_PIN 25

//Declaração do objeto servo motor
Servo my_servo;

//Definição de variáveis com propriedades do servo motor
const int my_servo_pulse_freq = 50; //Hz  Especificação do Servo Motor (verificar datasheet)
const int my_servo_min_pulse_width = 544; //us  Especificação do Servo Motor (verificar datasheet)
const int my_servo_max_pulse_width = 2500; //us  Especificação do Servo Motor (verificar datasheet)

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
void setup() 
{
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Atribuir o pino ao objeto do servo motor
  my_servo.setPeriodHertz(my_servo_pulse_freq);
  my_servo.attach(SERVO_PIN,my_servo_min_pulse_width,my_servo_max_pulse_width);
  
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

  delay(5000);
  
  for (int servo_position=0; servo_position<= 180; servo_position+=5)  // Posiciona o servo de 0º até 180º com um passo de 5º 
  { 
    my_servo.write(servo_position);

    display_lcd.clear();
    display_lcd.setCursor(0,0);
    display_lcd.print("Target: " + String(servo_position) + " dg");
    
    delay(200);           
  }

  delay(5000);
  
  for (int servo_position=180; servo_position>= 0; servo_position-=5) // Posiciona o servo de 180º até 0º com um passo de 5º 
  { 
    my_servo.write(servo_position);    

    display_lcd.clear();
    display_lcd.setCursor(0,0);
    display_lcd.print("Target: " + String(servo_position) + " dg");
    
    delay(200);             
  }
  
}
//End main loop -------------------------------------------------------------------------------------------
