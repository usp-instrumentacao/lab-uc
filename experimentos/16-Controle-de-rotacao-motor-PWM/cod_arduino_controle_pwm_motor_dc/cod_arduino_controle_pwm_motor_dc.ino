/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         CONTROLE DE ROTAÇÃO DE MOTOR DC COM PWM
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

//Definição pino do potenciômetro de controle de velocidade
#define ADC_PIN 25

//Definição pino de saída do sinal e constantes de configuração PWM
#define OUT_PWM_PIN 14
const int pwm_freq = 250; // Frequência PWM (Hz)
const int pwm_resolution = 16; // Resolução PWM 8, 10, 12, 16 (bits)

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
float adc_value = 0.0;
int out_pwm_value = 0;

// Setup --------------------------------------------------------------------------------------------------
void setup() 
{
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Definição do pino do potênciometro como input
  pinMode(ADC_PIN, INPUT);

  //configuração das funcionalidades da saída PWM
  pinMode(OUT_PWM_PIN,OUTPUT);
  ledcSetup(OUT_PWM_PIN, pwm_freq, pwm_resolution);
  ledcAttachPin(OUT_PWM_PIN, OUT_PWM_PIN);
  ledcWrite(OUT_PWM_PIN, 0);
  
  //Delay de inicialização
  delay(1000);

  //Limpa o display 16x2
  display_lcd.clear();
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop()
{

  // Leitura do pino analógico e conversão para tensão elétrica
  adc_value = analogRead(ADC_PIN);
  adc_value = (3.3/4095)*adc_value; //12 bits de resolução (ESP32)

  // Escrita do valor de PWM
  out_pwm_value = int(round((adc_value/3.3)*(pow(2,pwm_resolution)-1)));
  ledcWrite(OUT_PWM_PIN, out_pwm_value);
  
  // Exibir valor no monitor serial do arduino
  Serial.println("Valor de tensão no pino ADC = " + String(adc_value,4));
  Serial.println("Variável de saída PWM = " + String((adc_value/3.3)*100,1));
  
  // Exibir valor no display
  display_lcd.setCursor(0,0);
  display_lcd.print("Saída [%]");
  display_lcd.setCursor(0,1);
  display_lcd.print(String((adc_value/3.3)*100,1));
  
  // loop delay
  delay(dt);
  
}
//End main loop -------------------------------------------------------------------------------------------
