#include "network.h"
#include "tools.h"

int main(int argc, char *argv[]){
	sendMessage(argv[1], atoi(argv[2]), argv[3]);
	return 0;
}