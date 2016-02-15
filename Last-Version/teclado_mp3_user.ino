#include <Keypad.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

SdFat sd; //variável para o cartão de memória
SFEMP3Shield MP3player;

String onibus;

const byte LINHAS = 4;
const byte COLUNAS = 3;

char matriz_teclas[LINHAS][COLUNAS] = 
{
  {'1','2','3'}, {'4','5','6'}, {'7','8','9'}, {'*','0','#'}
};

byte PinosLinhas[LINHAS] = {4, 5, 6, 7};
byte PinosColunas[COLUNAS] = {8, 9, 10};

Keypad teclado = Keypad(makeKeymap(matriz_teclas), PinosLinhas, PinosColunas, LINHAS, COLUNAS);

void setup() {
  Serial.begin(9600);
  /*Serial.println("Teclado 4x3");
  Serial.println("Aguardando o click do usuário...");
  Serial.println();*/     
}

void loop() {
  char tecla_press = teclado.getKey();
  int numero = (int)tecla_press;
  
  if (tecla_press) {
    if (tecla_press == '*') {
      onibus = "";
      //ativar_mp3(numero);

    } else if (tecla_press == '#') {
      Serial.println("Enviado");
      onibus = "";
      //ativar_mp3(numero);
      
    } else {
      Serial.print("Tecla pressionada: ");
      Serial.println(tecla_press);
      onibus += tecla_press;
      Serial.println(onibus);
      Serial.println();
      //ativar_mp3(numero);
    }  
  } 
  
  delay(500);
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
