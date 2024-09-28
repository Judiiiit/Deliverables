//Include this library to be able to make calls in shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Special structure for storing query results
	MYSQL_RES *result;
	MYSQL_ROW row;
	//We create a connection to the MYSQL server
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf("Error creating connection: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//initialize the connection
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "League",0, NULL, 0);
	if (conn==NULL) {
		printf("Error initializing connection: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	int Identifier_G;
	// I ask the identifier of the game
	printf("Give me the Identifier of the Game\n");
	scanf("%d", &Identifier_G);
	char Identifier_G_str[10];  // Para convertir el nÃºmero a cadena
	sprintf(Identifier_G_str, "%d", Identifier_G);  // Convierte el entero a cadena
	
	// Construimos la consulta usando strcpy y strcat
	strcpy(query, "SELECT Game_Record.Score FROM Game,Game_Record WHERE Game.Identifier_G = '");
	strcat(query, Identifier_G_str);  // Concatenamos el identificador convertido a cadena
	strcat(query, "' AND Game.Identifier_G = Game_Record.Game");
	err=mysql_query (conn, query);
	if (err!=0) {
		printf ("Error while querying data from database %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//We collect the result of the query. The result of the
	//query is returned in a variable of pointer type to
	//MYSQL_RES as we have declared previously.
	//This is a virtual table in memory that is the copy
	//from the actual table on disk.
	result = mysql_store_result(conn);
	// The result is a matrix structure in memory
	// where each row contains data for one person.
	// Now we get the first row that is stored in a
	// variable of type MYSQL_ROW
	row = mysql_fetch_row(result);
	if (row == NULL)
		printf("No data was obtained in the query\n");
	else
		while (row !=NULL) {
			// column 0 contains the score
			printf("%s\n", row[0]);
			// get the next row
			row = mysql_fetch_row(result);
	}
		mysql_close(conn);
		exit(0);
}
