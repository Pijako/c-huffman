#include <stdlib.h>
#include <stdio.h>

#ifndef TAILLE_ASCII
#define TAILLE_ASCII 256
#endif

typedef struct{
	
	int ftab[256];
	
}Freq_table;
	
typedef struct Noeud Noeud;

struct Noeud{
	
	int frequence;
	char data;
	struct Noeud *left;
	struct Noeud *right;
	struct Noeud *previous;
	
};

typedef struct Noeud* Tree;

typedef struct{

	int num;
	int niveau;
	char bin;
	char caractere;

}Dict;

typedef struct{
	
	int text_size;
	int tree_size;
	char *used_char;
	int char_number;
	int infix_way_size;
	Dict dict[TAILLE_ASCII];
	
}Infos;


