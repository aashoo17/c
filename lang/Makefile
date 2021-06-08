.SILENT:
all:main
	./main
	rm main

# vpath %.c glibc
file=loop.c

main:$(file)
	$(CC) -o $@ $<

ass:$(file)
	$(CC) -o main.s -S $<

.PHONY:
cl: 
	rm main main.s