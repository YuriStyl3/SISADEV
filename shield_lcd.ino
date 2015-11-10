#include <LiquidCrystal.h>  
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int menu_cont; //Variável para contagem dos menus
int sel=0; //Variável para verificar estado do botão selecionar
  
void setup() {
	Serial.begin(9600);   
	lcd.begin(16, 2);      
}  
  
void loop() {  
	int botoes;  
 	botoes = analogRead (0); //Leitura do valor da porta analógica A0
	atualiza_menu();    
}

void atualiza_menu() {
	lcd.setCursor(8,1);

	if(botoes > 100 && botoes < 200) { //Se botão da esquerda for pressionado 
    	menu_cont--; //Volta para o MENU anterior
  	
  	} else if(botoes > 700 && botoes < 800) { //Senão se o botão da direita for pressionado
    	menu_cont++;  //Vai para o próximo MENU
  	
  	} else if(botoes < 100) {
   		sel = 1; //Valida que o botão de seleção foi pressionado
  	}
  	
  	trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
  	menu_list();
}

void menu_list() {

  if(menu_cont == 0) {
  	lcd.setCursor(4,0);  
	lcd.print("SISADEV");
    lcd.setCursor(0,1); 
    lcd.print("18 - Bairro Nordeste");

    if(sel == 1) {//Se botão de seleção for pressionado
    
    	while(sel == 1) {//Enquanto o botão de selecionar não for pressionado denovo
      
	        botoes = analogRead(A0); //Lê os botões
	        ajuste1(); //Vai para a função de ajuste do Brilho
	        lcd.clear(); //Limpa LCD
	        trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
	        
	        if(botoes < 100) {//Se o botão de seleção for pressionado
		    	sel = 0; //Sai do MENU
		        trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        	}
		}
    }
  
  } else if(menu_cont == 1) {
  	lcd.setCursor(4,0);  
	lcd.print("SISADEV");
    lcd.setCursor(0,1); 
    lcd.print("77 - Parque dos Coqueiros");
    
    if(sel == 1) {//Se botão de seleção for pressionado
    
    	while(sel == 1) {//Enquanto o botão de selecionar não for pressionado denovo
      
	        botoes = analogRead(A0); //Lê os botões
	        ajuste1(); //Vai para a função de ajuste do Brilho
	        lcd.clear(); //Limpa LCD
	        trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
	        
	        if(botoes < 100) {//Se o botão de seleção for pressionado
		    	sel = 0; //Sai do MENU
		        trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        	}
		}
    }
  
  } else if(menu_cont == 2) {//Menu 3: Tela de Ajuste do Contraste
  	lcd.setCursor(4,0);  
	lcd.print("SISADEV");
    lcd.setCursor(0,1); 
    lcd.print("64 - Nova Natal");
    
    if(sel == 1) {//Se botão de seleção for pressionado
    
    	while(sel == 1) {//Enquanto o botão de selecionar não for pressionado denovo
      
	        botoes = analogRead(A0); //Lê os botões
	        ajuste1(); //Vai para a função de ajuste do Brilho
	        lcd.clear(); //Limpa LCD
	        trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
	        
	        if(botoes < 100) {//Se o botão de seleção for pressionado
		    	sel = 0; //Sai do MENU
		        trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        	}
		}
    }
  }
else if(menu_cont == 3) {//Menu 4: Tela de Estado do Relé
    lcd.setCursor(4,0);  
	lcd.print("SISADEV");
    lcd.setCursor(0,1); 
    lcd.print("85 - Soledade");
    
    if(sel == 1) {//Se botão de seleção for pressionado
    
    	while(sel == 1) {//Enquanto o botão de selecionar não for pressionado denovo
      
	        botoes = analogRead(A0); //Lê os botões
	        ajuste1(); //Vai para a função de ajuste do Brilho
	        lcd.clear(); //Limpa LCD
	        trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
	        
	        if(botoes < 100) {//Se o botão de seleção for pressionado
		    	sel = 0; //Sai do MENU
		        trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        	}
		}
    }
  
  } else if(menu_cont == 4) {//Se a contagem de menu for para 4
    menu_cont = 0; //Volta para o primeiro menu
  
  } else if(menu_cont == -1) {//Se a contagem de menu for para -1
    menu_cont = 3; //Volta para o último menu
  }
}

void trata_botao() {
  while(botoes != 1023) {//Enquanto o botão não for solto, fica preso no laço
    botoes=analogRead(A0);
  }
}

void trata_botao2() {
  while(botoes > 900) {//Enquanto nenhum botão for pressionado, fica preso no laço
    botoes=analogRead(A0);
  }
}
