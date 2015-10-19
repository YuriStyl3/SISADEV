#include <VirtualWire.h>

const int ledPin = 13;
char Valor_CharMsg[4]; 
int estado = 1; //Armazena estado led = ligar/desligar

void setup() {
  Serial.begin(9600);   
  pinMode(ledPin,OUTPUT);
  vw_set_tx_pin(4); //Pino ligado ao pino DATA do transmissor RF
  vw_setup(1000);   //Velocidade de comunicacao (bits por segundo)
}

void loop() {
  itoa(estado,Valor_CharMsg,10); //Converte valor para envio
  digitalWrite(13, true); //Liga o led da porta 13 para indicar envio dos dados
  
  vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg)); //transmite o dado 
  vw_wait_tx(); //Aguarda envio do dado
  
  digitalWrite(13, false); //Desliga o led da porta 13 ao final da transmissao
  Serial.print("Valor enviado: ");
  Serial.println(Valor_CharMsg);
  
  delay(2000);
}
