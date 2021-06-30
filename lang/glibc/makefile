.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc
file=signal.c

main:$(file) 
	$(CC) -o $@ $<

dbg:$(file)
	$(CC) -g $< -o main


ass:$(file)
	$(CC) -o main.s -S $<

cl: 
	rm main main.s


.PHONY: all, ass, cl, dbg