all: EP

EP: arvore.o
	cc arvore.o 17076671.c -o EP 

arvore.o: arvore.c
	cc -c arvore.c -o arvore.o -W -Wall

clean:
	rm -rf *.o EP
