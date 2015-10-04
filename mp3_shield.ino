#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>


SdFat sd;
SFEMP3Shield MP3player;
int resultado;

void setup() {
  //Serial.begin(115200);

  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");  
  resultado = MP3player.begin();

  if(resultado != 0) {
    Serial.print(F("Codigo de erro: "));
    Serial.print(resultado);
    Serial.println(F(" ao tentar tocar a musica"));
    
    if(resultado == 6 ) {
      Serial.println(F("Atencao: Plugins não encontrados."));
    }
  }
}

void loop() {
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10);
  MP3player.playTrack(1);

  delay(100);
}
