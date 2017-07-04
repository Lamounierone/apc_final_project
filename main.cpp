#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "db.h"

#define RESX 1200
#define RESY 710

void window(void);
void escreve(char*);
int click(void); 

int main() 
{
	int x=0, y=0;
	int verificacao;
	char usuario[10];
	int i=0;
	int rc;
	char *zErrMsg = 0;
	
	sqlite3 *db;
		
	rc = sqlite3_open_v2(DB, &db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
	
	if (rc) {
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db));
//		return 1;
	} else {
		fprintf(stderr, "Opened database successfully\n");
//		return 0;
	}
	
	createTables(db); // Cria uma estrutura basica de tabelas de usuarios
	
	window();
	
	readimagefile("LOGIN.jpg", 20, 20, RESX, RESY);
			
	escreve(usuario);
	verificacao = verificaUser(db, usuario);
		
	if(verificacao == 0){
		readimagefile("entrar.jpg",532,503,696,444);
		click();
		window();
	
		readimagefile("Lista opções.jpg", 20, 20, RESX, RESY);
	} else {
		readimagefile("Cadastro.jpg", 20, 20, RESX, RESY);
	}
	
	system("PAUSE");
	return 0;
}

void window(void)
{
	initwindow(RESX, RESY, "Agenda do Calouro UnB");
	setcolor (0);
	setfillstyle (1, 15);
	bar(0, 0, RESX-5, RESY-5);	
}


void escreve(char* usuario)
{

	int i=1, cont=0; //variaveis para guardar as coordenadas do ponteiro do mouse
		
	memset(usuario, '\0', 10);
	//for(i=0; i<10; i++)
	//{
	// usuario[i]='\0';
	//}
	
	while(cont<10)	
	{
		
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
		//fundo branco na letra
		setbkcolor(15);
		//cor da letra
		setcolor(0); //0 é preto
		usuario[cont] = getch();//aqui a letra digitada é lida uma a uma sem necessidade de apertar o enter	
		//printf("%d", usuario[j]);
		if (usuario[cont] == 13) 
		{
			usuario[strlen(usuario)-1] = '\0';
			//strtok(usuario,"13");
			break;
		}
		
		bgiout <<usuario[cont];//função de saída na tela gráfica. Precisará ainda da "outstreamxy"
		
		if(i==1)//para a primeira caixinha
		{
			outstreamxy(i*345,370);//impriminto letras delocadas a cada passo. Para a primeira caixinha é diferente.
		}
		else//para todas as outras caixinhas
		{
			outstreamxy(345+((i-1)*20),370);//cálculo maluco para acertaras letras na caixinha
		}
		i++; //variável utilizada apenas para deslocar o texto
		cont++;
	}
	//puts(usuario);
	//return 0;
}
	
int click(void)
{
	
int x=0,y=0;
	
	
		while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(10); // Five second delay, so there might be a several clicks
    }
	
	//pega as coordenadas do clique esquerdo do mouse e guarda em x e y
if(ismouseclick(WM_LBUTTONDOWN))
	{
		
			
		getmouseclick(WM_LBUTTONDOWN, x, y);//pegando o clique do mouse			
		if((x>=532&&x<=696) && (y>=503)&&(y<=444))
		{
						//dando a impressão gráfica do clique---------
			
			readimagefile("Cadastro.jpg", 20, 20, RESX, RESY);
			readimagefile("entrar.jpg",532,503,696,444);
			delay(500);	
			readimagefile("entrar black .jpg",532,503,696,444);
			delay(500);	
			readimagefile("entrar.jpg",532,503,696,444);
				
				delay(500);		
			readimagefile("entrar black .jpg",532,503,696,444);
		
			//------------------------------------------------------
			
			
			
		}
		else
		{
		 	readimagefile("entrar black .jpg",532,503,696,444);
		}
			
	}
	
}
