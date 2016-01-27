#include "PP_TFTLCD.h"
#include "PP_TouchScreen.h"

#define YP A1 //Y+ esta na porta Analog1
#define XM A2 //A- esta na porta Analog2
#define YM 7 //Y- esta na porta Digital 7
#define XP 6 //X+ esta na porta Digital 6

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

PP_TouchScreen ts = PP_TouchScreen(XP, YP, XM, YM, 100);

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

//(LCD_CS, LCD_DS, LCD_WR, LCD_RD, LCD_RESET)
PP_TFTLCD tft (A3, A2, A1, A0, A4);

//Armazena o estado dos botoes
bool botao0 = 0;
bool botao1 = 0;
bool botao2 = 0;
bool botao3 = 0;
bool botao4 = 0;
bool botao5 = 0;
bool botao6 = 0;
bool botao7 = 0;
bool botao8 = 0;
bool botao9 = 0;
bool botao_enter = 0;

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void setup(void) {
  Serial.begin(9600);
  Serial.println("Sisadev Bus");
  tft.reset();
  delay(500);
  uint16_t identifier = tft.readRegister(0x0);
  Serial.println("Driver encontrado");
  Serial.println(identifier, HEX);

  tft.initDisplay();
  tft.fillScreen(BLACK);
  tft.setRotation(3);

  tft.drawRoundRect(30, 5, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(50, 10);
  tft.println("1");

  tft.drawRoundRect(130, 5, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(150, 10);
  tft.println("2");

  tft.drawRoundRect(230, 5, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(250, 10);
  tft.println("3");

  tft.drawRoundRect(30, 65, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(50, 70);
  tft.println("4");

  tft.drawRoundRect(130, 65, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(150, 70);
  tft.println("5");

  tft.drawRoundRect(230, 65, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(250, 70);
  tft.println("6");

  tft.drawRoundRect(30, 125, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(50, 130);
  tft.println("7");

  tft.drawRoundRect(130, 125, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(150, 130);
  tft.println("8");

  tft.drawRoundRect(230, 125, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(250, 130);
  tft.println("9");

  tft.drawRoundRect(80, 185, 62, 50, 5, WHITE);
  tft.setTextColor(YELLOW);
  tft.setTextSize(5);
  tft.setCursor(100, 190);
  tft.println("0");

  tft.drawRoundRect(180, 185, 62, 50, 5, GREEN);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.setCursor(190, 195);
  tft.println("OK");
}

void loop() {
  Point ponto = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);

  if ((ponto.z > MINPRESSURE) && (ponto.z < MAXPRESSURE)) {
    ponto.x = tft.width() - (map(ponto.x, TS_MINX, TS_MAXX, tft.width(), 0));
    ponto.y = tft.height() - (map(ponto.y, TS_MINY, TS_MAXY, tft.height(), 0));
    if (ponto.y > 10) {
      Serial.print("py: ");
      Serial.println(ponto.y);
      Serial.print("px: ");
      Serial.println(ponto.x);
      Serial.println("---------------------");

      //Teste do botao1
      if (ponto.y > 25 & ponto.y < 70 & ponto.x > 255 & ponto.y < 305) {
        if (botao1 == 0) {
          tft.fillRoundRect(31, 6, 60, 48, 5, RED);
          mostra_on(50, 10, 1);
          botao1 = !botao1;
        } 
        else {
          tft.fillRoundRect(31, 6, 60, 48, 5, BLACK);
          mostra_off(50, 10, 1);
          botao1 = !botao1;
        }
      }
       //Teste do botao2
      if (ponto.y > 100 & ponto.y < 155 & ponto.x > 255 & ponto.y < 305) {
        if (botao2 == 0) {
          tft.fillRoundRect(131, 6, 60, 48, 5, RED);
          mostra_on(150, 10, 2);
          botao2 = !botao2;
        } 
        else {
          tft.fillRoundRect(131, 6, 60, 48, 5, BLACK);
          mostra_off(150, 10, 2);
          botao2 = !botao2;
        }
      }
      //Teste do botao3
      if (ponto.y > 185 & ponto.y < 240 & ponto.x > 255 & ponto.y < 305) {
        if (botao3 == 0) {
          tft.fillRoundRect(231, 6, 60, 48, 5, RED);
          mostra_on(250, 10, 3);
          botao3 = !botao3;
        } 
        else {
          tft.fillRoundRect(231, 6, 60, 48, 5, BLACK);
          mostra_off(250, 10, 3);
          botao3 = !botao3;
        }
      }
      //Teste do botao 4
      if (ponto.y > 25 & ponto.y < 70 & ponto.x > 162 & ponto.x < 224) {
        if (botao4 == 0) {
          tft.fillRoundRect(31, 66, 60, 48, 5, RED);
          mostra_on(50, 70, 4);
          botao4 = !botao4;
        } 
        else {
          tft.fillRoundRect(31, 66, 60, 48, 5, BLACK);
          mostra_off(50, 70, 4);
          botao4 = !botao4;
        }
      }
      //Teste do botao 5
      if (ponto.y > 100 & ponto.y < 155 & ponto.x > 162 & ponto.x < 224) {
        if (botao5 == 0) {
          tft.fillRoundRect(131, 66, 60, 48, 5, RED);
          mostra_on(150, 70, 5);
          botao5 = !botao5;
        } 
        else {
          tft.fillRoundRect(131, 66, 60, 48, 5, BLACK);
          mostra_off(150, 70, 5);
          botao5 = !botao5;
        }
      }
      //Teste do botao 6
      if (ponto.y > 175 & ponto.y < 310 & ponto.x > 162 & ponto.x < 224) {
        if (botao6 == 0) {
          tft.fillRoundRect(231, 66, 60, 48, 5, RED);
          mostra_on(250, 70, 6);
          botao6 = !botao6;
        } 
        else {
          tft.fillRoundRect(231, 66, 60, 48, 5, BLACK);
          mostra_off(250, 70, 6);
          botao6 = !botao6;
        }
      }
      //Teste do botao 7
      if (ponto.y > 25 & ponto.y < 70 & ponto.x > 70 & ponto.x < 132) {
        if (botao7 == 0) {
          tft.fillRoundRect(31, 126, 60, 48, 5, RED);
          mostra_on(50, 130, 7);
          botao7 = !botao7;
        } 
        else {
          tft.fillRoundRect(31, 126, 60, 48, 5, BLACK);
          mostra_off(50, 130, 7);
          botao7 = !botao7;
        }
      }
      //Teste do botao 8
      if (ponto.y > 100 & ponto.y < 155 & ponto.x > 70 & ponto.x < 132) {
        if (botao8 == 0) {
          tft.fillRoundRect(131, 126, 60, 48, 5, RED);
          mostra_on(150, 130, 8);
          botao8 = !botao8;
        } 
        else {
          tft.fillRoundRect(131, 126, 60, 48, 5, BLACK);
          mostra_off(150, 130, 8);
          botao8 = !botao8;
        }
      }
      //Teste do botao 9
      if (ponto.y > 175 & ponto.y < 310 & ponto.x > 70 & ponto.x < 132) {
        if (botao9 == 0) {
          tft.fillRoundRect(231, 126, 60, 48, 5, RED);
          mostra_on(250, 130, 9);
          botao9 = !botao9;
        } 
        else {
          tft.fillRoundRect(231, 126, 60, 48, 5, BLACK);
          mostra_off(250, 130, 9);
          botao9 = !botao9;
        }
      }
    } 
  }
}

void mostra_on(int x, int y, int z) {
  tft.setTextColor(YELLOW);
  tft.setCursor(x, y);
  tft.setTextSize(5);
  tft.println(z);
  delay(100);
}

void mostra_off(int x, int y, int z) {
  tft.setTextColor(YELLOW);
  tft.setCursor(x, y);
  tft.setTextSize(5);
  tft.println(z);
  delay(100);
}
