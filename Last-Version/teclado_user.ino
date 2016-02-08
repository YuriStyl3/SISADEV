#include <Keypad.h>

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
  if (tecla_press) {
    if (tecla_press == '*') {
      onibus = "";
    } else if (tecla_press == '#') {
      Serial.println("Enviado");
      onibus = "";
    } else {
      Serial.print("Tecla pressionada: ");
      Serial.println(tecla_press);
      onibus += tecla_press;
      Serial.println(onibus);
      Serial.println();
    } 
    
  } 
}
