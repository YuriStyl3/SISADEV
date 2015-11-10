#define brilho 5; //Define o brilho
#define contraste 9; //Define o contraste

#include <Wire.h> 
#include <LiquidCrystal_l2C.h>

//Comunicação entre l2C com o display LCD
LiquidCrystal_l2C lcd(32,16,2); //Inicia o endereço l2C, as colunas e linhas;

int botoes; //Variável para leitura de botões
int cont; //Contador

float pwm_brilho = 255; //Controle de pwm do brilho
float pwm_contraste = 0; //Controle de pwm do contraste
float porcentagem_brilho; //Conversão do pwm do brilho em porcentagem
float porcentagem_contraste //Conversão do pwm do contraste em porcentagem

void setup() {
	Serial.begin(9600);

	//Inicializar o LCD
	lcd.init(); 
	lcd.backlight();

	pinMode(brilho, OUTPUT); //Configura o pino 5 como saída
	pinMode(contraste, OUTPUT); //Configura o pino 9 como saída

	inicializacao();
}

void loop() {
	botoes = analogRead(A0); //Faz a leitura da porta A0 e armazena na variável
	Serial.println(botoes); //Escreve o valor lido
	delay(1000);
	ajuste();
}

void inicializacao() { //Inicialização da tela LCD para a aplicação
	analogWrite(brilho, 255);
	analogWrite(contraste, 0);

	Serial.println("");
	Serial.println("Shield LCD iniciado....");

	lcd.setCursor(0,0); //Posicionando o cursor na primeira coluna e na primeira linha
	lcd.print("LCD Shield l2C"); //Escreve no LCD

	for (cont = 0; cont <= 4; cont++) { //Laço para o efeito de piscagem
		lcd.setCursor(0,1); //Posiciona o cursor na primeira coluna e segunda linha
		lcd.print("                "); //Limpar segunda linha
		delay(250);
		lcd.setCursor(0,1); //Posiciona cursor
		lcd.print("SISADEV");
		delay(250);		
	}
}	

void ajuste() {
	if (botoes > 100 && botoes < 200) { //Se o botão da esquerda for pressionado
		if (pwm_brilho > 0) { //Se o pwm do brilho for maior que 0
			pwm_brilho -= 25.5; //Diminui em 10% no pwm do brilho 
			analogWrite(brilho, pwm_brilho); //Atualiza o pwm do brilho
		}
		
		porcentagem_brilho = (pwm_brilho/255) * 100; //Armazena o valor do pwm em porcentagem 
		Serial.print("Brilho = ");
		Serial.print(porcentagem_brilho);
		Serial.print("%");
		trata_botao(); //Tratar botão para variar apenas 10% ao ser clicado
	
	} else if (botoes > 700 && botoes < 800) { //Se o botão da direita for pressionado
		if (pwm_brilho < 255) { //Se o pwm do brilho for menor que 255
			pwm_brilho += 25.5; //Aumenta em 10% no pwm do brilho 
			analogWrite(brilho, pwm_brilho); 
		}
		
		porcentagem_brilho = (pwm_brilho/255) * 100; 
		Serial.print("Brilho = ");
		Serial.print(porcentagem_brilho);
		Serial.print("%");
		trata_botao();
	
	} else if (botoes > 200 && botoes < 300) { //Se o botão de baixo for pressionado
		if (pwm_contraste > 0) { //Se o pwm do brilho for menor que 255
			pwm_contraste -= 25.5; //Diminui em 10% no pwm do contraste 
			analogWrite(contraste, pwm_contraste); 
		}
		
		porcentagem_contraste = (pwm_contraste/255) * 100; 
		Serial.print("Contraste = ");
		Serial.print(porcentagem_contraste);
		Serial.print("%");
		trata_botao();
	
	} else if (botoes > 400 && botoes < 500) { //Se o botão de baixo for pressionado
		if (pwm_contraste < 255) { //Se o pwm do brilho for menor que 255
			pwm_contraste += 25.5; //Aumenta em 10% no pwm do contraste 
			analogWrite(contraste, pwm_contraste); 
		}
		
		porcentagem_contraste = (pwm_contraste/255) * 100; 
		Serial.print("Contraste = ");
		Serial.print(porcentagem_contraste);
		Serial.print("%");
		trata_botao();
	}
}

void trata_botao() {
	while(botoes != 1023) {
		botoes = analogRead(AO);
	}
}
