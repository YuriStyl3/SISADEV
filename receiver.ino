#include <VirtualWire.h>

const int led = 12;

void setup() {
    vw_set_ptt_inverted(true);
    vw_set_rx_pin(13);
    vw_setup(1000); 
    pinMode(led, OUTPUT);
    vw_rx_start();       
}

void loop(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    if(buf[0]=='1'){
      digitalWrite(led,HIGH);
    } 
       
    if(buf[0]=='0'){
      digitalWrite(led,LOW);
    }
  }
}

