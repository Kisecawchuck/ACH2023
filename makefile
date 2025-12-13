EP : arvore.o lista.o 17076671.o
	cc arvore.o lista.o 17076671.o -o EP -Wall

17076671.o : 17076671.c
	cc -c 17076671.c

arvore.o : arvore.c
	cc -c arvore.c -o arvore.o

lista.o : lista.c
	cc -c lista.c -o lista.o

clean :
	rm -rf *.o EP
