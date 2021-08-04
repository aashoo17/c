all:main
	./main
	rm main

# vpath %.c socket/tcp
file=io.c

main:$(file) 
	$(CC) -o $@ $<

dbg:$(file)
	$(CC) -g $< -o main


ass:$(file)
	$(CC) -o main.s -S $<

cl: 
	rm main


.PHONY: all ass cl dbg
.SILENT: all main ass cl dbg