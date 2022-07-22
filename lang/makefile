.SILENT:
all:main
	./main
	rm main

vpath %.c glibc/socket
file = function.c

main:$(file)
	gcc -o $@ $<

# TODO: delete only when file is available
cl: 
	rm main

.PHONY: all, ass, cl