#include <VirtualWire.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;
const int led = 12;

void setup() {
  Serial.begin(115200);

  vw_set_ptt_inverted(true);
  vw_set_rx_pin(13);
  vw_setup(1000);
  pinMode(led, OUTPUT);
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if (vw_get_message(buf, &buflen)) {
    if(buf[0]=='1') {
      digitalWrite(led, HIGH);
      tocar();
    }

    if(buf[0]=='0'){
      digitalWrite(led,LOW);
    }
  }

  delay(100);
}

void tocar() {
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  MP3player.begin();
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10);
  MP3player.playTrack(1);
}
