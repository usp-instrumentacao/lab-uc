/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         COMUNICAÇÃO SERIAL BLUETOOTH ENTRE MICROCONTROLADORES ESP32
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
*		  https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
*     https://circuitdigest.com/microcontroller-projects/using-classic-bluetooth-in-esp32-and-toogle-an-led
*
* Licença: GNU GPLv3
*
*/

//incluir bibliotecas
#include <LiquidCrystal.h>
#include <BluetoothSerial.h>

// Checagem se o Bluetooth está habilitado no SDK (Softare Development Kit), caso não esteja será necessário recompilar o SDK
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Declaração do objeto para comunicação serial por Bluetooth
BluetoothSerial SerialBT;

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

// Declaração de variáveis e constantes relacionadas a comunicação serial
String serial_received_data;
const byte buffer_size = 150; //bytes
char end_of_line = '\n'; //caracter que indica fim da informação enviada ou recebida

// Setup --------------------------------------------------------------------------------------------------
void setup() {
  
  //Inicia as comunicações seriais
  Serial.begin(115200);

  //Inicializa o display 16x2
  display_lcd.begin(16, 2);
  display_lcd.setCursor(0,0);
  display_lcd.print("Iniciando...");

  //Delay de inicialização
  delay(1000);
  
  //Inicia o bluetooth
  SerialBT.begin("ESP32_bluetooth"); //Especificar o nome do dispositivo bluetooth
  
  Serial.println("Bluetooth iniciado! Pronto para pareamento...");
  display_lcd.clear();
  display_lcd.setCursor(0,0);
  display_lcd.print("Parear bluetooth...");

  //Delay de inicialização
  delay(1000);
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop() {

  //Verificar se existem dados provindos da comunicação Serial com o PC
  serial_received_data = check_hardware_serial_for_data(Serial);
  if (serial_received_data.isEmpty()==false)
  {
    //Exibir dados enviados para o celular via bluetooth
    Serial.print(("Enviado: " + serial_received_data + String(end_of_line)));
    
    //Enviar dados informados no monitor serial do PC para o celular via bluetooth
    SerialBT.print((serial_received_data + String(end_of_line)));
  }

  //Verificar se existem dados provindos da comunicação Serial Bluetooth
  serial_received_data = check_bluetooth_serial_for_data(SerialBT);
  if (serial_received_data.isEmpty()==false)
  {
    //Exibir dados enviados para o ESP32 via bluetooth
    Serial.print(("Recebido: " + serial_received_data + String(end_of_line)));

    //Exibir dados enviados para o ESP32 via bluetooth no display
    display_lcd.clear();
    display_lcd.setCursor(0,0);
    display_lcd.print(serial_received_data);
  }
  
  //loop delay
  delay(dt);
  
}
//End main loop -------------------------------------------------------------------------------------------

// Funções auxiliares -------------------------------------------------------------------------------------

  //Check hardware serial for data
  String check_hardware_serial_for_data(HardwareSerial &ref_serial)
  {
    bool end_of_data=false;
    char serial_buffer[buffer_size];
    byte buffer_index=0;
    String aux_string;
    if(ref_serial.available()>0)
    {
      char recieved_data;
      while(end_of_data==false)
      { 
        delay(2);
        recieved_data = ref_serial.read();
        if (recieved_data != end_of_line && String(recieved_data)!="")
        {
          serial_buffer[buffer_index++] = recieved_data;
          if(buffer_index >= buffer_size)
          {
            buffer_index = buffer_size - 1;
          }
        }
        else
        {
          serial_buffer[buffer_index] = '\0'; //finaliza a string
          aux_string = String(serial_buffer);
          end_of_data = true;
        }
      }
    }
    return aux_string;
  }

  
  //Check bluetooth serial for data
  String check_bluetooth_serial_for_data(BluetoothSerial &ref_serial)
  {
    bool end_of_data=false;
    char serial_buffer[buffer_size];
    byte buffer_index=0;
    String aux_string;
    if(ref_serial.available()>0)
    {
      char recieved_data;
      while(end_of_data==false)
      { 
        delay(2);
        recieved_data = ref_serial.read();
        if (recieved_data != end_of_line && String(recieved_data)!="")
        {
          serial_buffer[buffer_index++] = recieved_data;
          if(buffer_index >= buffer_size)
          {
            buffer_index = buffer_size - 1;
          }
        }
        else
        {
          serial_buffer[buffer_index] = '\0'; //finaliza a string
          aux_string = String(serial_buffer);
          end_of_data = true;
        }
      }
    }
    return aux_string;
  }
