.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc
file=thread.c

main:$(file)
	$(CC) -o $@ $<


ass:$(file)
	$(CC) -o main.s -S $<

cl: 
	rm main main.s


.PHONY: all, ass, cl