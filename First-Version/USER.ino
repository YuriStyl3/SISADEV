#include <Keypad.h>
#include <VirtualWire.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

//int ledReceptor = 5; //Esse led acenderá sempre que o receptor receber dados
//const int pino_botao = A0;

// Variáveis pra tratar os valores recebidos
int valor_recebido_RF;
char recebido_RF_char[4];

String onibus;
//String linha_onibus[1];

SdFat sd; //variável para o cartão de memória
SFEMP3Shield MP3player; //variável para o player

// Definição do teclado no arduino
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
  Serial.begin(9600);
  ativar_mp3(10);
  //pinMode(ledReceptor, OUTPUT);   
}

void loop() {
  // Ativa o teclado e verificar os valores recebidos constantemente
   ativar_teclado();
   verificar_receptor();
}

// Função que trata os botões do teclado
void ativar_teclado() {
  char tecla_press = teclado.getKey();
  int numero = (int)tecla_press /*- 48*/;
  
  if (tecla_press) {
    if (tecla_press == '*') {
      onibus = "";
      //Serial.println(numero);
      ativar_mp3(numero);

    } else if (tecla_press == '#') {
      Serial.println("Enviado");
      ativar_mp3(numero);
      ativar_transmissor(onibus);
      onibus = "";
      //Serial.println(numero);
      
    } else {
      //int numero_bus = (int)tecla_press - 48;   
      Serial.print("Tecla pressionada: ");
      Serial.println(tecla_press);
      onibus += tecla_press;
      Serial.print("Linha: ");
      Serial.println(onibus);
      //linha_onibus[0] = onibus;
      //Serial.println(numero); 
      ativar_mp3(numero);
    }  
  } 
}

// Função para enviar os dados digitados no teclado
void ativar_transmissor(String onibus) {
  vw_rx_stop();
  
  const char *bus = onibus.c_str();
  
  vw_set_tx_pin(10); 
  vw_setup(1000);
  
  for (int i = 0; i < 5; i++) {
   vw_send((uint8_t *)bus, strlen(bus));
    vw_wait_tx();
    Serial.print("Valor enviado: ");
    Serial.println(bus);
    delay(1500);
  }
  //verificar_receptor();
}

// Função para verificar a recepção de dados
void verificar_receptor() {
  vw_set_rx_pin(9);
  vw_rx_start();//Pino ligado ao pino DATA do receptor RF
  vw_setup(1000); //Velocidade de comunicacao (bits por segundo)
  
  uint8_t buf[VW_MAX_MESSAGE_LEN]; 
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
  if (vw_get_message(buf, &buflen)) {
    int i; //contador 
    for (i = 0; i < buflen; i++) {            
      recebido_RF_char[i] = char(buf[i]); //Armazena os caracteres recebidos 
    }
    
    recebido_RF_char[buflen] = '\0';
    valor_recebido_RF = atoi(recebido_RF_char); //Converte o valor recebido para integer
    
    if (valor_recebido_RF == 1) {
      ativar_mp3(99);
      vw_rx_stop();    
    }
    
    Serial.print("Recebido: ");
    Serial.println(valor_recebido_RF);
    
  }
  //Serial.println("Aguardando dados...");
  delay(100); 
}  

// Função para ativar o shield mp3    
void ativar_mp3(int track) {
  //Inicializa o cartão de memória
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  
  MP3player.begin(); //Inicializa o mp3 shield
  MP3player.setBitRate(192);
  MP3player.setVolume(10,10); //Ajusta o volume
  MP3player.playTrack(track);
  delay(2000);
}
