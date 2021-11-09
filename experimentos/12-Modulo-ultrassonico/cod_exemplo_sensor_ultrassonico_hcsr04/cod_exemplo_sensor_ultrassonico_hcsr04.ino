/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO MÓDULO SENSOR DE DISTÂNCIA ULTRASSÔNICO HC-SR04
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
*		  https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
*         https://maker.pro/custom/tutorial/hc-sr04-ultrasonic-proximity-sensor-datasheet-highlights
*
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <LiquidCrystal.h>

//Definiçao de pinos do módulo sensor HC-SR04
#define TRG_PIN 26
#define ECHO_PIN 27

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
const float air_sound_speed = 340; // m/s
const int avg_number = 8;
float flight_time=0.0;
float distance=0.0;

// Setup --------------------------------------------------------------------------------------------------
void setup() {
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia as comunicação
  pinMode(TRG_PIN, OUTPUT); // Configura pino de trigger como output
  pinMode(ECHO_PIN, INPUT); // Configura pino de eco como input
  
  //Inicializa o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Pino de trigger em baixo
  digitalWrite(TRG_PIN, LOW);
     
  //Delay de inicialização
  delay(2000);
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop() {

  //zerar váriavel da distância para cálculo de média posterior
  distance=0.0;
  
  for (int i=1; i<=avg_number; i++)
  {

    //Habilita o pino de trigger em estado alto por 10 microsegundos
    digitalWrite(TRG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRG_PIN, LOW);
  
    //Leitura do tempo em estado alto do pino de eco
    flight_time = pulseIn(ECHO_PIN, HIGH); // microsegundos
    flight_time = flight_time/1e6; //segundos
    
    //Cálculo da distância e soma para cálculo posterior da média
    distance = distance + ((flight_time*air_sound_speed)/2)*100; // cm

    //delay entre aquisições
    delay(50);
    
  }

  //Cálculo da média das distâncias
  distance = distance/avg_number;
  
  //Exibe distância no display
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Distância: ");
  display_lcd.setCursor(0,1);
  display_lcd.print(String(distance));

  //Exibe distância no serial
  Serial.println("Distância :" + String(distance) + " cm");
  
  //loop delay
  delay(dt);
  
}
//End main loop -------------------------------------------------------------------------------------------
