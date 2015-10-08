//importa as bibliotecas necessárias para o funcionamento dos componentes
#include <VirtualWire.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

SdFat sd; //variável para o cartão de memória
SFEMP3Shield MP3player;
const int led = 12; //variável para o led no pino 12 do arduino

void setup() {
  Serial.begin(115200); //inicializa a serial

  //inicializa o receptor
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(13);
  vw_setup(1000);
  vw_rx_start();

  pinMode(led, OUTPUT); //inicializa o led
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if (vw_get_message(buf, &buflen)) { //se receber a mensagem
    if(buf[0]=='1') { //se a mensagem for igual a 1 acende o led e liga o mp3
      digitalWrite(led, HIGH);
      ativar_mp3();
    }

    if(buf[0]=='0'){ //se a mensagem for igual a 0 o led fica desligado
      digitalWrite(led,LOW);
    }
  }

  delay(100);
}

//função para ativar o shield mp3
void ativar_mp3() {
  //inicializa o cartão de memória
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  MP3player.begin(); //inicializa o mp3 shield
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10); //ajusta o volume
  MP3player.playTrack(1); /*seleciona o toque mp3, que aqui, no caso, será 1 para
  fins de teste*/
}
