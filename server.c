#include "network.h"
#include "tools.h"

int main(int argc, char *argv[]){
	char buf[256];
	receiveMessage(atoi(argv[1]), buf);
	printf("Donnees recues :%s\n", buf);
	return 0;
}