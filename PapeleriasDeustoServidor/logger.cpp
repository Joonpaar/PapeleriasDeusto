#include "logger.h"
#include <stdio.h>

logger::logger() {
	// TODO Auto-generated constructor stub

}

logger::~logger() {
	// TODO Auto-generated destructor stub
}

void logger:: mensajeLog(const char* msg){
	FILE * log=fopen("log.txt", "a");
	//fprintf(stderr, "%s\n", msg);
	//fflush(stderr);
	fprintf(log, "%s\n", msg);
	fclose(log);
}

void logger::errorLog(const char* msg){
	char cadena[200];
	sprintf(cadena, "Error: %s\n", msg);
	mensajeLog(cadena);
}
