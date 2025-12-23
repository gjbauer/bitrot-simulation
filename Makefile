
all: aes.o
	gcc -o simulation main.c aes.o -lssl -lcrypto -Itiny-AES-c
	rm aes.o

aes.o:
	gcc -o aes.o tiny-AES-c/aes.c -DAES256 -c

clean:
	rm simulation

.PHONY: clean

