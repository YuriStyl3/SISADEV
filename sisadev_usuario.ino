#include <VirtualWire.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

int ledReceptor = 5; //Esse led acenderá sempre que o receptor receber dados
const int pino_botao = A0;
int valor_recebido_RF; 
char recebido_RF_char[4]; 
int valor_botao = 0; //valor que será transmitido quando o botão for clicado

SdFat sd; //variável para o cartão de memória
SFEMP3Shield MP3player; //variável para o player

void setup() {
  Serial.begin(9600);
  pinMode(ledReceptor, OUTPUT);
  vw_set_rx_pin(7);//Pino ligado ao pino DATA do receptor RF
  vw_setup(1000); //Velocidade de comunicacao (bits por segundo) 
  vw_rx_start(); //Inicia a recepcao  
  Serial.println("Aguardando dados...");
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
    
    if (valor_recebido_RF == 1) {
      /*Se o valor recebido for 1, o led acenderá, 
      o player será ativado e o botão poderá ser clicado durante 5 segundos*/
      digitalWrite(ledReceptor, HIGH); 
      ativar_mp3();
      ativar_botao();
      
      delay(5000);
    }
    if (valor_recebido_RF == 0) {
      digitalWrite(ledReceptor, LOW);
    }
  }
}

void ativar_mp3() {
  //Inicializa o cartão de memória
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  
  MP3player.begin(); //Inicializa o mp3 shield
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10); //Ajusta o volume
  MP3player.playTrack(1); /*Seleciona o toque mp3, que aqui, no caso, será 1*/
}

void ativar_botao() {
  delay(5000); //Tempo para a player ser encerrada e o botão ser ativado
  vw_rx_stop(); //O receptor para de receber dados
  char Valor_CharMsg[4]; //Variável que possui o valor a ser transmitido
  
  pinMode(pino_botao, INPUT);
  vw_set_tx_pin(4); //Define o pino do transmissor
  vw_setup(1000);
  
  valor_botao = digitalRead(pino_botao);
  
  if(valor_botao == LOW){
    /*Se o botão for pressionado, ele enviará o valor 0 pelo transmissor*/
    itoa(valor_botao, Valor_CharMsg, 10);
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    Serial.println("Valor enviado: ");
    Serial.println(Valor_CharMsg);
  }

  /*Quando toda a transmissão de dados terminar,
  o circuito passa a receber dados novamente*/
  vw_rx_start(); 
}
