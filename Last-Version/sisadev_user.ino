#include <Keypad.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <nRF24L01.h>
#include <RF24.h>

SdFat sd; //variável para o cartão de memória
SFEMP3Shield MP3player;

String onibus;
String linha_onibus[1];

RF24 radio(11,12);

const uint64_t pipe = 0xE14BC8F482LL;

const byte LINHAS = 4;
const byte COLUNAS = 3;

char matriz_teclas[LINHAS][COLUNAS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte PinosLinhas[LINHAS] = {4, 5, 6, 7};
byte PinosColunas[COLUNAS] = {8, 9, 10};

Keypad teclado = Keypad(makeKeymap(matriz_teclas), PinosLinhas, PinosColunas, LINHAS, COLUNAS);

void setup() {
  Serial.begin(57600);
  /*Serial.println("Teclado 4x3");
  Serial.println("Aguardando o click do usuário...");
  Serial.println();*/     
}

void loop() {
  
  char tecla_press = teclado.getKey();
  while (tecla_press) {
    if (tecla_press == '*') {
      int numero = (int)tecla_press;
      //Serial.println(numero);
      onibus = "";
      //ativar_mp3(numero);

    } else if (tecla_press == '#') {
      int numero = (int)tecla_press;
      Serial.println("Enviado");
      ativar_transceiver(onibus);
      onibus = "";
      //Serial.println(numero);
      //ativar_mp3(numero);
      
    } else {
      int numero = (int)tecla_press - 48;   
      Serial.print("Tecla pressionada: ");
      Serial.println(tecla_press);
      onibus += tecla_press;
      linha_onibus[0] = onibus; 
      Serial.println(onibus);
      Serial.println();
      /*Serial.println(numero);*/
      //ativar_mp3(numero);
    }  
  } 
  delay(100);
}

void ativar_transceiver(String onibus) {
  int linha[1];
  linha[0] = atoi(onibus.c_str());
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.write(linha, 1);
}

//função para ativar o shield mp3
void ativar_mp3(int numero) {
  //inicializa o cartão de memória
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  MP3player.begin(); //inicializa o mp3 shield
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10); //ajusta o volume
  MP3player.playTrack(numero); /*seleciona o toque mp3, que aqui, no caso, será o valor digitado*/
}
