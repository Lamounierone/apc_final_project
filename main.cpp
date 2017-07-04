#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <string.h>
#include "sqlite3.h"

#define DB "unb.db"
#define RESX 1200
#define RESY 710
#define user "calouro"

static int openDb(sqlite3*);
static int createTables(sqlite3*);
static int verificaUser(sqlite3*, char*);
static int gCallback(void*, int, char**, char**);

void window(void);
void escreve(char*);
int click(void); 

int main() 
{
	int x=0, y=0;
	int verificacao;
	char uuser[12];
	char usuario[10];
	int i=0;
	int rc;
	char *zErrMsg = 0;
	
	sqlite3 *db;
	
	
	rc = sqlite3_open_v2(DB, &db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
	
	if (rc) {
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db));
		//return 1;
	} else {
		fprintf(stderr, "Opened database successfully\n");
		//return 0;
	}
	
	createTables(db); // Cria uma estrutura basica de tabelas de usuarios
	
	window();
	
	readimagefile("LOGIN.jpg", 20, 20, RESX, RESY);
			
	escreve(usuario);
	puts(usuario);
	//puts(user);
	verificacao=strcmp(usuario,user);
	
	if(verificacao==0)
	{
	readimagefile("entrar.jpg",532,503,696,444);
	click();
	window();
	
	readimagefile("Lista opções.jpg", 20, 20, RESX, RESY);
	
	
	
	}
	else
	{
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

static int openDb(sqlite3* db){
	
	int rc;
	char *zErrMsg = 0;
	
	rc = sqlite3_open_v2(DB, &db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);

	if (rc) {
		fprintf(stderr, "Can't open the database: %s\n", sqlite3_errmsg(db));
		return 1;
	} else {
		fprintf(stderr, "Opened database successfully\n");
		return 0;
	}
}

static int createTables(sqlite3* db)
{
	int rc;
	char *zErrMsg = 0;
	
	const char* sql;
	const char* sql_tabela_cursos;

	sql = "CREATE TABLE alunos (ID INT PRIMARY KEY NOT NULL, nome TEXT NOT NULL, apelido TEXT NOT NULL, idade int NOT NULL, matricula int NOT NULL);";

	sql_tabela_cursos = "CREATE TABLE disciplinas (ID INT PRIMARY KEY NOT NULL, semestre INT NOT NULL, nome TEXT NOT NULL, cod_unb TEXT NOT NULL);";
	
	rc = sqlite3_exec(db, sql, gCallback, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stderr, "Tabela de usuarios criada");
	}
	
	rc = sqlite3_exec(db, sql_tabela_cursos, gCallback, 0, &zErrMsg);
	
	if( rc!= SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Tabela de Cursos Criada");
	}
}

int verificaUser(sqlite3* db, char* uuser)
{		
	int rc;
	sqlite3_stmt *res;
	
	char* zErrMsg = 0;
	const char* sql;
	
	sql = "SELECT * FROM alunos WHERE apelido=?;";
	
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if( rc == SQLITE_OK ){
		sqlite3_bind_text(res, 1, user, -1, 0);
	} else {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	
	int step = sqlite3_step(res);
	
	if (step == SQLITE_ROW){
		printf("Usuario encontrado");
	} else {
		printf("Usuario nao encontrado");
	}
	sqlite3_finalize(res);
}

static int gCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}
