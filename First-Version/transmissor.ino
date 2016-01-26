#include <VirtualWire.h>

char *controller;
const int led = 12;

void setup() {
  pinMode(led,OUTPUT);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(13);
  vw_setup(1000); // speed of data transfer Kbps
}

void loop(){
  controller="1";
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led, HIGH);
  delay(2000);  

  
  controller="0";
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led, LOW);
  delay(2000); 
  
}
