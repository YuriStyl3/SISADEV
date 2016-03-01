#include <Keypad.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RH_NRF24.h>

SdFat sd; //variável para o cartão de memória
SFEMP3Shield MP3player;

String onibus;
String linha_onibus[1];
float data[1];


#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
//RH_NRF24 nrf24;
//RF24 radio(9,10);

//byte canal[5] = {'s', 'i', 's', 'a', 'd'};

const uint64_t pipe = 0xE8E8F0F0E1LL;
const byte LINHAS = 4;
const byte COLUNAS = 3;

char matriz_teclas[LINHAS][COLUNAS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte PinosLinhas[LINHAS] = {8, 7, 6, 5};
byte PinosColunas[COLUNAS] = {4, 3, 2};

Keypad teclado = Keypad(makeKeymap(matriz_teclas), PinosLinhas, PinosColunas, LINHAS, COLUNAS);

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(pipe);
  /*radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);*/
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

void loop() {
  
  char tecla_press = teclado.getKey();
  if (tecla_press) {
    if (tecla_press == '*') {
      int numero = (int)tecla_press;
      onibus = "";
      //ativar_mp3(numero);

    } else if (tecla_press == '#') {
      int numero = (int)tecla_press;
      Serial.println("Enviado");
      ativar_transceiver(onibus);
      onibus = "";
      //ativar_mp3(numero);
      
    } else {
      int numero = (int)tecla_press - 48;   
      Serial.print("Tecla pressionada: ");
      Serial.println(tecla_press);
      onibus += tecla_press;
      Serial.print("Linha: ");
      Serial.println(onibus);
      linha_onibus[0] = onibus; 
      //ativar_mp3(numero);
    }  
  } 
  delay(100);
}

void ativar_transceiver(String onibus) {
  data[0] = atof(onibus.c_str());
  bool ok = radio.write(data, sizeof(data));
  
  if (ok) {
    Serial.print("Dado enviado: ");
    Serial.println(data[0]);
  } else {
    Serial.println("Nao foi possivel enviar...");
  }
  /*uint8_t bus = atoi(onibus.c_str()); 
  uint8_t data[1] = {bus};
  Serial.println("Sending to nrf24_server");
  nrf24.send(data, sizeof(data));*
  /*Serial.print("Enviado: ");
  Serial.println(data[0]);
  Serial.println("---------------------------");
  nrf24.waitPacketSent();
  
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  
  if (nrf24.waitAvailableTimeout(500)) {
    if (nrf24.recv(buf, &len)) {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
    } else {
        Serial.println("recv failed");
    }
  }else{
      Serial.println("No reply, is nrf24_server running?");
  }
  
  /*Serial.println(linha[0]);
  Serial.println("--------------");
  delay(400);*/
  
  /*radio.begin();
  radio.setChannel(100);
  radio.openWritingPipe(pipe);
  radio.write(linha, 1);*/
  delay(1000);  
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
