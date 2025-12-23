
all:
	gcc -o simulation main.c tiny-AES-c/aes.c -lssl -lcrypto -Itiny-AES-c -DAES256

clean:
	rm simulation corrupted.bin uncorrupted.bin

.PHONY: clean

