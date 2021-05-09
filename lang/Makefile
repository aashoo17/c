.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc

main:macro.c
	cc -o $@ $<
