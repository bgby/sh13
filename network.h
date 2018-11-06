#ifndef NETWORK
#define NETWORK

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

int sendMessage(char *servername, int serverport, char *message);

int receiveMessage(int serverport, char *buf);

#endif