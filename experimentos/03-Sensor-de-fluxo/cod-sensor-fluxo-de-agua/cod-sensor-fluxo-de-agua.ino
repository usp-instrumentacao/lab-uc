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
 *
 * Referências:
 *		https://microcontrollerslab.com/water-flow-sensor-pinout-interfacing-with-arduino-measure-flow-rate/
 *		https://how2electronics.com/iot-water-flow-meter-using-esp8266-water-flow-sensor/
 *
 *	Licença:
 *		GNU GPLv3
 */

//incluir bibliotecas
#include <LiquidCrystal.h>

// Botão para alternar entre o modo de calibração e leitura
#define TOGGLE_MODE_PIN 23

// Botão para iniciar e finalizar a calibração
#define CALIBRATION_PIN 22

// Definição pino do sensor de fluxo
#define SENSOR_PIN 34

// Definição de pinos para o display 16x2
#define LCD_RS 15
#define LCD_EN 2
#define LCD_D4 4
#define LCD_D5 16
#define LCD_D6 17
#define LCD_D7 5

// Instanciação do display lcd (rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Variáveis globais
const float volume_calibracao = 0.5; // Quantidade de água utilizada na calibração em litros
const int tempo_amostragem = 1000; // Tempo de leitura do sensor em ms

float vazao; // Variável para armazenar valor de vazão
float coef_sensor; // pulsos/litro

volatile int count_pulsos = 0; // Conta a quantidade de pulsos medidos
volatile bool calibration_mode = false; // Quando true, entra no modo de calibração.
volatile bool calibrating = false; // Quando true, começa a contagem dos pulsos p/ calibração

void setup()
{
	// Inicia o display 16x2
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	lcd.print("Iniciando...");

	// Delay de inicialização
	delay(2000);

	// Limpa o display 16x2
	lcd.clear();

	// Declaração dos modos dos pinos utilizados
	pinMode(TOGGLE_MODE_PIN, INPUT);
	pinMode(CALIBRATION_PIN, INPUT);
	pinMode(SENSOR_PIN, INPUT);

	// Anexa os pinos especificados a uma função de interrupção
	attachInterrupt(digitalPinToInterrupt(TOGGLE_MODE_PIN), toggle_mode, RISING);
	attachInterrupt(digitalPinToInterrupt(CALIBRATION_PIN), calibration, RISING);
}

void loop()
{
	if(calibration_mode)
		{
			lcd.clear();
			lcd.print("Modo calibracao");
			delay(1000);
			if(calibrating)
				{
					lcd.clear();
					lcd.print("Calibrando...");

					count_pulsos = 0;
					attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensor_count, RISING);
					while(calibrating) {}
					detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));

					coef_sensor = count_pulsos/volume_calibracao; // Num pulsos contados para 1 litro

					lcd.clear();
					lcd.print("Fim calibracao");
					lcd.setCursor(0,1);
					lcd.print(String(coef_sensor) + " Pulsos/L");

					while(calibration_mode) {} // Aguarda o modo de calibração ser desativado
				}
		}
	else
		{
			// Cada leitura dura o tempo definido por tempo_amostragem
			count_pulsos = 0;
			attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensor_count, RISING);
			delay(tempo_amostragem);
			detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));
			vazao = count_pulsos / coef_sensor * (tempo_amostragem / 1000); // [pulsos] / [pulsos/L] * [segundos]
			vazao = vazao * 60; // Conversão de [L/s] para [L/min]

			// Exibe a vazão no LCD
			lcd.clear();
			lcd.print("Vazao [L/min]");
			lcd.setCursor(0,1);
			lcd.print(String(vazao));
		}
}

void toggle_mode()
{
	calibration_mode = !calibration_mode;
}

void calibration()
{
	calibrating = !calibrating;
}

void sensor_count()
{
	count_pulsos++; //Incrementa o contador
}
