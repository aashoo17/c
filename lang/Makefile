.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc

main:main.c
	cc -o $@ $<

ass:main.c
	gcc -S main.c
