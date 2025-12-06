EP : arvore.o 17076671.o
	cc arvore.o 17076671.o -o EP 

17076671.o : 17076671.c
	cc -c 17076671.c

arvore.o : arvore.c
	cc -c arvore.c -o arvore.o

clean :
	rm -rf *.o EP
