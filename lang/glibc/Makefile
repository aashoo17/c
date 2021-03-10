.SILENT:
all:main
	./main
	rm main

vpath %.c socket
main:client.c
	gcc -o $@ $?