#include "sqlite3.h"

#define DB "unb.db"

static int openDb(sqlite3*);
static int createTables(sqlite3*);
static int verificaUser(sqlite3*, char*);
static int gCallback(void*, int, char**, char**);


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
		sqlite3_bind_text(res, 1, uuser, -1, 0);
	} else {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	
	int step = sqlite3_step(res);
	
	if (step == SQLITE_ROW){
		printf("Usuario encontrado");
		return 0;
	} else {
		printf("Usuario nao encontrado");
		return 1;
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
