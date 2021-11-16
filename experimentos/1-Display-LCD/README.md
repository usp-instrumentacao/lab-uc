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



