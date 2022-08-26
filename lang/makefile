.SILENT:
all:main
	./main

vpath %.c glibc
file = signal.c

main:$(file)
	gcc -g -o $@ $<

# TODO: delete only when file is available
cl: 
	rm main

.PHONY: all, ass, cl