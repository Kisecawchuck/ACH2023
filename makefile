EP : arvore.o lista.o main.o
	cc arvore.o lista.o main.o -o EP -Wall

main.o : 17076671.c
	cc -c main.c

arvore.o : arvore.c
	cc -c arvore.c -o arvore.o

lista.o : lista.c
	cc -c lista.c -o lista.o

clean :
	rm -rf *.o EP
