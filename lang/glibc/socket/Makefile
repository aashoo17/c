all: server client
	rm ${wildcard *.o}
server: server.o addr.o

client: client.o addr.o

addr: addr.o

.PHONY:
cl:
	rm {server,client}