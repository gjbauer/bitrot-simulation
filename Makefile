
all:
	gcc -o simulation main.c tiny-AES-c/aes.c -lssl -lcrypto -Itiny-AES-c -DAES256

clean:
	rm simulation

.PHONY: clean

