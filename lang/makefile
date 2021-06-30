.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc
file=error.c

main:$(file)
	gcc -o $@ $<


ass:$(file)
	gcc -o main.s -S $<

cl: 
	rm main main.s


.PHONY: all, ass, cl