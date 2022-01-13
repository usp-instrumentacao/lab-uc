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

#include <LiquidCrystal.h>

// Definição pino do botão START E STOP
#define START_BTN_PIN 23
#define STOP_BTN_PIN 22

// Definição pino do sensor
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

// Declaração de variáveis globais
unsigned int contador_pulsos; // Variável para a quantidade de pulsos
int aux_plot = 0;

void setup() {

	// Inicia as comunicações seriais
	Serial.begin(115200);

	// Inicia o display 16x2
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	lcd.print("Iniciando...");

	// Delay de inicialização
	delay(2000);

	// Limpa o display 16x2
	lcd.clear();

	// Definição do pino do sensor e modo de interrupção
	pinMode(SENSOR_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), interrup_function1, RISING);

	// Definição do pino do botão START e modo de interrupção
	pinMode(START_BTN_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(START_BTN_PIN), interrup_function2, RISING);

	// Definição do pino do botão STOP e modo de interrupção
	pinMode(STOP_BTN_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(STOP_BTN_PIN), interrup_function3, RISING);

	// Exibir msg no serial do arduino
	Serial.println("Aguardando início (botão start)...");

	// Exibir msg no display
	lcd.setCursor(0,0);
	lcd.print("Aguardando...");
	lcd.setCursor(0,1);
	lcd.print("Aguardando...");
}

void loop()
{
	if (aux_plot==1)
		{
			// Exibir valor no monitor serial do arduino
			Serial.println("Número de pulsos para fluir 1 litro de água = " + String(contador_pulsos));

			// Exibir valor no display
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Num. pulsos/L:");
			lcd.setCursor(0,1);
			lcd.print(String(contador_pulsos));

			aux_plot=0;
			interrupts(); // Habilita interrupção
		}
}


void interrup_function1()
{
	contador_pulsos++; // Incrementa o contador
}

void interrup_function2() // Botão START
{
	while (digitalRead(START_BTN_PIN)==HIGH)
		{
			contador_pulsos = 0;// zera o contador
		}
}

void interrup_function3() // Botão STOP
{
	aux_plot=1;
	noInterrupts(); // Desabilita interrupção
}
