CC=gcc
CFLAGS=-g -Wall
LDFLAGS=
EXEC=client server

all: $(EXEC)

client: client.o network.o tools.o
	$(CC) -o client client.o network.o tools.o $(LDFLAGS)

client.o: client.c network.h tools.h
	$(CC) -c client.c $(CFLAGS)

server: server.o network.o tools.o
	$(CC) -o server server.o network.o tools.o $(LDFLAGS)

server.o: server.c network.h tools.h
	$(CC) -c server.c $(CFLAGS)

network.o: network.c tools.h
	$(CC) -c network.c $(CFLAGS)

tools.o: tools.c
	$(CC) -c tools.c $(CFLAGS)

clean:
	rm -rf *.o

vclean: clean
	rm -rf $(EXEC)
