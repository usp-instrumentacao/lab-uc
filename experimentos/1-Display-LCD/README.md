# Utilizando o Display LCD

## Introdução
Neste experimento iremos demonstrar alguns princípios básicos da
da plataforma Arduino através de um exemplo utilizando um display LCD.

## Display LCD

Modulos de display LCD são uma ótima interface de comunicação visual e
são utilizados em uma infinidade de projetos embarcados devido sua
simplicidade. Um display exibe uma ou mais linhas de caracteres. No
nosso experimento, utilizamos um display 16x2, ou seja, que possui
duas linhas de 16 caracteres cada.

O display LCD utilizado possui 16 pinos, resumidos a seguir:
- 1 e 2: Alimentação (VDD ligado a 5V e VSS ligado ao GND).
- 3: Pino de constraste, ligado ao potenciômetro RV1.
- 4: Selecionador de registro. 1 (ligado) seleciona os bits de entrada
  como sendo de dados e 0 (desligado) sendo de instrução.
- 5: Seleciona o modo do LCD para escrita (0) ou leitura (1). Ligado
  ao GND para o modo de apenas escrita.
- 6: Pino de habilitação.
- 7 ao 14: Pinos de dados. Utilizamos apenas 4 neste experimento, e
  portanto, cada dado é passado como um conjunto de 4 bits.
- 15 e 16: Iluminação do LED.

Displays com este mesmo esquema de pinos são extremamente
genéricos. No entando, podem existir displays que funcionam de maneira
diferente e/ou com diferentes conformações de pinos, portanto, sempre
verifique o datasheet dos dispositivos que estiver utilizando antes de
começar a trabalhar.

Você não precisa conhecer o funcionamento interno do LCD para ser
capaz de utiliza-lo pois existem bibliotecas, ou seja, códigos já
prontos que já implementam as funcionalidades de baixo nível do
módulo. Bibliotecas são muito úteis pois fornecem uma camada de
abstração na programação. A biblioteca utilizada neste experimento
para o modulo, por exemplo, fornece metodos simples como `print()`,
que escreve no display um ou mais caracteres especificados como
parâmetro da função.

Caso queira entender um pouco mais a fundo o funcionamento de displays
LCD, há um ótimo artigo em:
[https://www.embarcados.com.br/modulo-de-display-lcd/](https://www.embarcados.com.br/modulo-de-display-lcd/).
 
## Circuito
![Esquemático](esquematico.png)

![Foto do circuito montado em uma protoboard.](imagem.png)

## Código
Primeiramente, precisamos incluir a biblioteca para utilização do
display LCD:
```
#include <LiquidCrystal.h>
```	
Após isso, definimos os pinos que serão utilizados para a
interface com o LCD:
```
#define DISPLAY_RS 15
#define DISPLAY_EN 2
#define DISPLAY_D4 4
#define DISPLAY_D5 16
#define DISPLAY_D6 17
#define DISPLAY_D7 5
``` 
A expressão `#define` não cria nenhuma variável na memória, apenas
atribui um valor a uma expressão, que na hora da compilação do código
será trocada pelo seu valor. Neste contexto, todo lugar no código que
possuir a expressão `DISPLAY_RS` será compilada como se tivéssemos
explicitamente colocado o número `15` no lugar. Isso é uma ótima
prática de programação, pois torna o código mais legível e evita
números arbitrários no meio do código. Caso conecte o display de
maneira diferente, é necessário apenas mudar este escopo para se
adequar ao seu modo de conexão (desde que todos esses pinos sejam
digitais e de uso geral).

Em seguida, nós instanciamos um objeto `display_lcd` da classe
`LiquidCrystal` fornecida pela biblioteca:
```
LiquidCrystal display_lcd(DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);
```
A criação do objeto é semelhante à de uma variável, com a diferença de
que são passados argumentos para sua criação (neste caso os pinos
definidos anteriormente).

Por fim é declarada uma variável global que será utilizada como delay
de execução do loop:
```
int dt=100;
```

Na função `setup()`, precisamos iniciar a comunicação serial, iniciar
o display e também limpa-lo (isto é, apagar tudo que estiver escrito
nele). Esta função é executada sempre que o microcontrolador é
iniciado.
```
void setup() 
{
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicia o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0); //Seleciona onde será iniciada a escrita (linha,coluna)
  display_lcd.print("Iniciando..."); //Escreve "Iniciando..." no display

  //Delay de inicialização
  delay(2000);

  //Limpa o display 16x2
  display_lcd.clear();
}
```
Ao cabo do setup, tudo estará configurado para utilizarmos posteriormente.
 
A função `loop()` é executada indefinidamente (um loop infinito)
enquanto o dispositivo estiver ligado.
