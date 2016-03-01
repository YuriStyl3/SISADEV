#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10
 
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

float data[1];

// Singleton instance of the radio driver
//RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup() {
  Serial.begin(9600);
  radio.begin();
  /*radio.setPALevel(RF24_PA_MAX);    
  radio.setDataRate(RF24_250KBPS);*/  
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  /*while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");*/    
}

void loop(){
  if (radio.available()) {
    radio.read(data, sizeof(data));
    Serial.print("Recebido: ");
    Serial.println(data[0]);    
  } else {
    Serial.println("Nao ha dados de radio disponiveis...");
  }
  /*if (nrf24.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    int rec = (int)buf;
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
//      NRF24::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println(rec);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      nrf24.send(data, sizeof(data));
      nrf24.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }*/
  delay(1000);
}
