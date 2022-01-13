/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         UTILIZANDO CÉLULA DE CARGA ALIADA A MÓDULO AMPLIFICADOR HX711
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
*		  https://arduino.stackexchange.com/questions/17542/connect-hx711-to-a-three-wire-load-cell
*         https://how2electronics.com/iot-weighing-scale-hx711-load-cell-esp8266/
*		  https://learn.sparkfun.com/tutorials/iot-weight-logging-scale/all
*		  https://www.ni.com/pt-br/innovations/white-papers/07/measuring-strain-with-strain-gages.html
*		  https://www.michsci.com/what-is-a-strain-gauge/
*
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <LiquidCrystal.h>
#include <HX711.h>

//Definição pino do botão de tara
#define TARE_PIN 33

//Definição pinos módulo HX711
#define HX711_DATA 35
#define HX711_CLK 32

// Declaração do objeto hx711
HX711 modulo_hx711;

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
float medida_hx711=0.0;
int fator_calibracao=27300;
int aux_tare = 0;

// Setup --------------------------------------------------------------------------------------------------
void setup() {
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Inicia o módulo hx711
  modulo_hx711.begin(HX711_DATA,HX711_CLK);
  modulo_hx711.set_scale(fator_calibracao);
  modulo_hx711.tare(); 

  //Definição do pino do botão START e modo de interrupção
  pinMode(TARE_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(TARE_PIN), interrup_function_one, RISING); 
  
  //Delay de inicialização
  delay(2000);

  //Limpa o display 16x2
  display_lcd.clear();
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{

  noInterrupts(); //desabilita interrupção
  
    if(aux_tare==1)
    {
      modulo_hx711.tare();

      display_lcd.clear();
      display_lcd.setCursor(0,0);
      display_lcd.print("Tarando...");
      delay(1);
      
      aux_tare=0;
    }
    
    //Carregar informações do módulo hx711
    medida_hx711 = modulo_hx711.get_units();
    
    //Exibir valor no monitor serial do arduino
    Serial.println("Valor informado pelo módulo hx711 = " + String(medida_hx711));
  
    //Exibir valor no display
    display_lcd.setCursor(0,0);
    display_lcd.print("Valor hx711");
    display_lcd.setCursor(0,1);
    display_lcd.print(String(medida_hx711));

  interrupts(); //habilita interrupção
  
  //loop delay
  delay(dt);
  
}
//End main loop -------------------------------------------------------------------------------------------

// Funções auxiliares -------------------------------------------------------------------------------------

  //Função de interrupção 1
  void interrup_function_one()
  {
     aux_tare=1;
     delay(20);
  }
  
