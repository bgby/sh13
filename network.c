#include "network.h"
#include "tools.h"

int sendMessage(char *servername, int serverport, char *message)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(servername);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(serverport);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    write(sockfd,message,strlen(message));

    close(sockfd);
    return 0;
}

int receiveMessage(int serverport, char* buf){
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    /*if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = serverport;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);


    //while (1)
    //{    
        newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, 
            &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");

        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");

        //printf("Received packet from %s:%d\nData: [%s]\n\n",
                //inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);
        strncpy(buf, buffer, 256);

        close(newsockfd);
    //}
    close(sockfd);
    return 0;
}