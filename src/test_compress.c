#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "compress.h"
#define TAILLE_ASCII 256


void test_table_frequence(){
	int tab[TAILLE_ASCII];
	char* path = "file.txt";
	init_tab_freq(tab);
	table_frequence(path, tab);
	//afficher_tab_freq(tab);
}

void test_arbre(){
	int tab[TAILLE_ASCII];
	init_tab_freq(tab);
	table_frequence("file.txt", tab);
	//afficher_tab_freq(tab);
	Noeud* arbre = NULL;
	int taille = 0;
	faire_arbre(&arbre, tab, &taille);
	afficher_arbre(arbre, 0);
	Dict dict[TAILLE_ASCII];
	init_dict(dict);
	
	dictionnaire(arbre, dict, 0, 0);
	afficher_dictionnaire(dict);
	FILE* stream;
	stream = fopen("test.txt", "wb");
	ecrire(arbre, stream, dict);
	fclose(stream);
	erase(&arbre);
	free(arbre);
}










		
int main(){
	//test_table_frequence();
	test_arbre();
	return 0;
}
