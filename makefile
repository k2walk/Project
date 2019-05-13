CC = g++

sha256.exe : src.c
	g++ -o sha256.exe src.c -lcrypto

clean :
	rm -rf sha256.exe