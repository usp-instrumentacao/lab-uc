# Utilizando o Display LCD

## Introdução
Neste experimento iremos demonstrar alguns princípios básicos da
da plataforma Arduino através de um exemplo utilizando um display LCD.

Caso ainda não tenha familiaridade com Arduino, é possível encontrar
uma rica e diversa documentação em seu site, indo desde os princípios
básicos até a utilização de bibliotecas mais específicas. Além do
mais, saber buscar informações é muito mais importante do que sabe-las
de cor.

Aluns links interessantes relacionadas à documentação da plataforma
Arduino:
- [**Conhecimentos Básicos Diante o Ecossistema Arduino**](https://docs.arduino.cc/learn/)
- [Tutoriais - Arduino](https://docs.arduino.cc/tutorials/)
- [Documentação de Referência da Linguagem Arduino em Português](https://www.arduino.cc/reference/pt/)
- [Get Started - ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)

É importante ressaltar que por mais que o microcontrolador utilizado
nesse e nos próximos experimentos seja um ESP32, este é totalmente
integrado e compatível com a plataforma Arduino, e portanto, um código
feito para rodar em uma placa de desenvolvimento Arduino deve ser
facilmente portável para um ESP32 e vice versa. As principais
alterações envolvem o número dos pinos, que a princípio deve ficar
claro que, a menos que sejam pinos de funções especiais, podem ser
arbitrariamente escolhidos. 

## Display LCD
O display LCD utilizado possui 16 pinos, resumidos a seguir:
- 1 e 2: Alimentação (VDD ligado a 5V e VSS ligado ao GND).
- 3: Pino de constraste, ligado ao potenciômetro RV1.
- 4: Selecionador de registro. 1 (ligado) seleciona os bits de entrada
  como sendo de dados e 0 (desligado) sendo de instrução.
- 5: Seleciona o modo do LCD para escrita (0) ou leitura (1). Ligado
  ao GND para o modo de apenas escrita.
- 6: Pino de habilitação
- 7 ao 14: Pinos de dados. Utilizamos apenas 4 neste experimento, e
  portanto, cada dado é passado como um conjunto de 4 bits.
- 15 e 16: Iluminação do LED.

## Código

## Circuito
![Esquemático](esquematico.png)
![Foto do circuito montado em uma protoboard.](imagem.png)


