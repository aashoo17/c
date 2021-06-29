.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc
file=crypto.c

main:$(file) 
	$(CC) -o $@ $< -lcrypt


ass:$(file)
	$(CC) -o main.s -S $<

cl: 
	rm main main.s


.PHONY: all, ass, cl