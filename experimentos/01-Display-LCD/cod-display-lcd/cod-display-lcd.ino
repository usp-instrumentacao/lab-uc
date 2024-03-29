/*
 *	Material de apoio para as disciplinas:
 *		5910230 - Introdução à Instrumentação Biomédica
 *		5910130 - Eletrônica
 *
 *	Títuo:
 *		Utilizando Display LCD
 *
 *	Autores:
 *		Carlos Eduardo Gallo Filho
 *		Edgar Mazón Valadez
 *		Fábio Eduardo Flores de Lima
 *		Ricardo Ricci Bordonal
 *		Prof. Dr. Theo Zeferino Pavan
 *
 *	Descrição:
 *		Exemplifica a utilização do módulo LCD
 *
 *	Licença:
 *		GNU GPLv3
 */

// Incluir bibliotecas
#include <LiquidCrystal.h>

// Definição de pinos para o display 16x2
#define LCD_RS 15
#define LCD_EN 2
#define LCD_D4 4
#define LCD_D5 16
#define LCD_D6 17
#define LCD_D7 5

// Declaração do display lcd (rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Declaração variáveis globais
const int dt = 100; //ms

void setup()
{
	// Inicia o display 16x2
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	lcd.print("Iniciando...");

	// Delay de inicialização
	delay(2000);

	// Limpa o display
	lcd.clear();
}

void loop()
{
	// Exibir texto no display
	lcd.setCursor(0,0); // Inicia texto na posição 0 da linha 0
	lcd.print("Texto linha 0");
	lcd.setCursor(0,1); // Inicia texto na posição 0 da linha 1
	lcd.print("Texto linha 1");

	// Loop delay
	delay(dt);
}
