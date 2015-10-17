#include <VirtualWire.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

//Define pino led
int ledPin = 5;
int led = 13;
//variável para o cartão de memória
SdFat sd; 
SFEMP3Shield MP3player;
//botao
const int pino_botao = A0;
int valor_recebido_RF;
char recebido_RF_char[4]; 
int valor_botao = 1;
//int estado = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(led, OUTPUT);
  //Pino ligado ao pino DATA do receptor RF
  vw_set_rx_pin(7);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(1000); 
  //Inicia a recepcao  
  vw_rx_start();
  Serial.println("Recepcao modulo RF - Aguardando...");
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
  if (vw_get_message(buf, &buflen)) {
    int i; 
    for (i = 0; i < buflen; i++) {            
      //Armazena os caracteres recebidos  
      recebido_RF_char[i] = char(buf[i]);
    }
    
    recebido_RF_char[buflen] = '\0';
       
    //Converte o valor recebido para integer
    valor_recebido_RF = atoi(recebido_RF_char);
         
    //Mostra no serial monitor o valor recebido
    Serial.print("Recebido: ");
    Serial.print(valor_recebido_RF);
    //Altera o estado do led conforme o numero recebido
    if (valor_recebido_RF == 1) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(led, HIGH);
      ativar_mp3();
      ativar_botao();
      delay(5000);
    }
    if (valor_recebido_RF == 0) {
      digitalWrite(ledPin, LOW);
      //Serial.println(" - Led apagado !");
    }
  }
}

void ativar_mp3() {
  //inicializa o cartão de memória
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  
  MP3player.begin(); //inicializa o mp3 shield
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10); //ajusta o volume
  MP3player.playTrack(1); /*seleciona o toque mp3, que aqui, no caso, será 1 apenas para testes*/
}

void ativar_botao() {
  delay(5000);
  vw_rx_stop();
  char Valor_CharMsg[4];
  
  pinMode(pino_botao, INPUT);
  vw_set_tx_pin(4);
  vw_setup(1000);
  
  valor_botao = digitalRead(pino_botao);
  
  if(valor_botao == HIGH){
    Serial.println("Botão não foi pressionado...");
  }else{
    itoa(valor_botao, Valor_CharMsg, 10);
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    Serial.println("Valor enviado: ");
    Serial.println(Valor_CharMsg);
  }

  vw_rx_start();
}
