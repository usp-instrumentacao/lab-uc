/*
 *	Material de apoio para as disciplinas:
 *		5910230 - Introdução à Instrumentação Biomédica
 *		5910130 - Eletrônica
 *
 *	Título:
 *		Utilizando módulo sensor de fluxo daseado em sensor de efeito hall YF-S201B
 *
 *	Autores:
 *		Carlos Eduardo Gallo Filho
 *		Ernesto Edgar Mazón Valadez
 *		Fábio Eduardo Flores de Lima
 *		Ricardo Ricci Bordonal
 *		Prof. Dr. Theo Zeferino Pavan
 *
 *	Descrição:
 *		descrição*
 * Referências:
 *		https://microcontrollerslab.com/water-flow-sensor-pinout-interfacing-with-arduino-measure-flow-rate/
 *		https://how2electronics.com/iot-water-flow-meter-using-esp8266-water-flow-sensor/
 *
 *	Licença:
 *		GNU GPLv3
 */

//incluir bibliotecas
#include <LiquidCrystal.h>

//Definição pino do sensor
#define SENSOR_PIN 34

// Definição de pinos para o display 16x2
#define LCD_RS 15
#define LCD_EN 2
#define LCD_D4 4
#define LCD_D5 16
#define LCD_D6 17
#define LCD_D7 5

// Declaração do display lcd (rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

float vazao; // Variável para armazenar valor de vazão
float frequencia_sensor; // Variável para armazenar a frequência do sensor
int contador_pulsos; // Variável para a quantidade de pulsos
int coef_sensor;

void setup()
{
	//Inicia as comunicações seriais
	Serial.begin(115200);

	//Inicia o display 16x2
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	lcd.print("Iniciando...");

	//Delay de inicialização
	delay(2000);

	//Limpa o display 16x2
	lcd.clear();

	//Definição do pino do sensor e modo de interrupção
	pinMode(SENSOR_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), interrup_function, RISING);
}

void loop()
{
	// Inicia o ciclo de contagem
	contador_pulsos = 0; // Zera o contador
	interrupts(); // Habilita interrupção
	delay(1000);
	noInterrupts(); // Desabilita interrupção

	// Processamento dos dados obtidos
	frequencia_sensor = contador_pulsos; // pulsos/segundo
	vazao = frequencia_sensor/coeficiente_sensor; // litros/segundo --> coef. pulsos p/ litro
	vazao = vazao * 60; // litros/minuto

	// Exibir valor no monitor serial do arduino
	Serial.println("Vazão [L/min] = " + String(vazao));

	// Exibir valor no display
	lcd.setCursor(0,0);
	lcd.print("Vazao [L/min]");
	lcd.setCursor(0,1);
	lcd.print(String(vazao));
}

void interrup_function()
{
	contador_pulsos++; //Incrementa o contador
}
