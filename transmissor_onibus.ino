#include <VirtualWire.h>

//Define pinos Led
const int ledPin = 13;
char Valor_CharMsg[4]; 
//Armazena estado led = ligar/desligar
int estado = 1;

void setup() {
  Serial.begin(9600);   
  pinMode(ledPin,OUTPUT);
  //Pino ligado ao pino DATA do transmissor RF
  vw_set_tx_pin(4);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(1000);
}

void loop() {
  //Converte valor para envio
  itoa(estado,Valor_CharMsg,10);
  //Liga o led da porta 13 para indicar envio dos dados
  digitalWrite(13, true);
  //Envio dos dados
  vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
  //Aguarda envio dos dados
  vw_wait_tx();
  //Desliga o led da porta 13 ao final da transmissao
  digitalWrite(13, false);
  Serial.print("Valor enviado: ");
  Serial.println(Valor_CharMsg);
  delay(2000);
}
