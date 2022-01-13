/*
* 
* Material de apoio para as disciplinas: 
*                                         5910230 - Introdução à Instrumentação Biomédica
*                                         5910130 - Eletrônica
* 
* Exemplo:
*         COMUNICAÇÃO SERIAL ENTRE MCUS (HARDWARE SERIAL)
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

// Definição de portas seriais
HardwareSerial SERIAL_BET_ESPs(2);   // ESP32 possui 3 portas serias (0, 1 e 2) para utilização. A 0 nunca deve ser utilizada pois é a porta de gravação usb

//Definiçao de pinos Rx e Tx da comunicação serial
#define RX_BET_ESPs 27 
#define TX_BET_ESPs 26

// Declaração variáveis globais
int dt=100; //ms

// Declaração de variáveis e constantes relacionadas a comunicação serial
const byte buffer_size = 150; //bytes
char end_of_line = '\n'; //caracter que indica fim da informação enviada ou recebida
String serial_received_data;

// Setup --------------------------------------------------------------------------------------------------
void setup() 
{
  
  //Inicia as comunicações seriais
  Serial.begin(115200);
  SERIAL_BET_ESPs.begin(115200, SERIAL_8N1, TX_BET_ESPs, RX_BET_ESPs);
  SERIAL_BET_ESPs.setRxBufferSize(buffer_size);

  //Delay de inicialização
  delay(2000);
  
}
// end Setup ----------------------------------------------------------------------------------------------

// Main Loop ----------------------------------------------------------------------------------------------
void loop() 
{

  //Verificar se existem dados provindos da comunicação Serial com o PC
  serial_received_data = check_hardware_serial_for_data(Serial);
  if (serial_received_data.isEmpty()==false)
  {
    //Exibir dados enviados para o outro ESP32
    Serial.print(("Enviado ao ESP2: " + serial_received_data + String(end_of_line)));
    
    //Enviar dados informados no monitor serial do PC para o outro ESP32
    SERIAL_BET_ESPs.print((serial_received_data + String(end_of_line)));
  }

  //Verificar se existem dados provindos da comunicação Serial com o outro ESP32
  serial_received_data = check_hardware_serial_for_data(SERIAL_BET_ESPs);
  if (serial_received_data.isEmpty()==false)
  {
    //Exibir dados recebidos do outro ESP32
    Serial.print(("Recebido do ESP2: " + serial_received_data + String(end_of_line)));
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
    if(ref_serial.available()>0) //verificação de flag de comunicação serial
    {
      //Serial.println("Dados na porta serial:" + String(ref_serial));
      char recieved_data;
      while(end_of_data==false)
      { 
        delay(2);
        recieved_data = ref_serial.read();
        //Serial.println("Char. recebido:" + String(recieved_data));
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
