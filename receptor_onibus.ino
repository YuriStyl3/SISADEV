#include <VirtualWire.h>

const int buzzer = 8;
int valor_recebido_RF;
char recebido_RF_char[4];

void setup() {
  Serial.begin(9600);
  vw_set_rx_pin(13); //Pino ligado ao pino DATA do receptor RF
  vw_setup(1000); //Velocidade de comunicacao (bits por segundo)
  vw_rx_start();//Inicia a recepcao
  Serial.println("Recepcao modulo RF - Aguardando...");
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN]; 
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
  if (vw_get_message(buf, &buflen)) {
    int i; //contador 
    for (i = 0; i < buflen; i++) {            
      recebido_RF_char[i] = char(buf[i]); //Armazena os caracteres recebidos 
    }
    
    recebido_RF_char[buflen] = '\0';
    valor_recebido_RF = atoi(recebido_RF_char); //Converte o valor recebido para integer
    
    Serial.print("Recebido: ");
    Serial.print(valor_recebido_RF);
    
    if (valor_recebido_RF == 0) {
      tone(buzzer, 1500); //Liga o buzzer se o valor recebido for 0 (o valor que o transmissor do usuário enviará)
      
      delay(5000);
    }

    noTone(buzzer);
  }
}
