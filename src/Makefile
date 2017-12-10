all:compress

compress:	test_compress.c compress.o ecrire.o arbre.o compress.h
		c99 -g -Wall -o compress compress.o ecrire.o arbre.o test_compress.c
		
compress.o: compress.c  compress.h
		c99 -g -Wall  -c -o compress.o compress.c -pedantic

ecrire.o: ecrire.c compress.h
		c99 -g -Wall -c -o ecrire.o ecrire.c -pedantic

arbre.o: arbre.c compress.h
		c99 -g -Wall -c -o arbre.o arbre.c -pedantic
test_compress.o: test_compress.c compress.h
		c99 -g -Wall -c -o test_compress.c -pedantic

clean:
	rm -rf *.o
mrproper: clean
	rm -rf compress

