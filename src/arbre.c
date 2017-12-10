#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "compress.h"
#include <malloc.h>
/**********************************************************************/
/************************ TABLE DE FREQUENCES *************************/
/**********************************************************************/

void table_frequence(char* path, int tab[256]){
	int car; 
	FILE *fp;
	fp = fopen(path,"r");
	assert(fp);
	while((car = fgetc(fp)) != EOF)
		tab[car] = tab[car] + 1;
	fclose(fp);
}

void init_tab_freq(int tab[TAILLE_ASCII]){
	for (int i=0; i<TAILLE_ASCII; i++)
		tab[i] = 0;
}

void afficher_tab_freq(int tab[TAILLE_ASCII]){
	for (int i=0; i<TAILLE_ASCII; i++)
		if (tab[i]!=0){
			printf("[%c->", i);
			printf("%d] ", tab[i]);
		}
	printf("\n");
}
/**********************************************************************/
/************************* ARBRE DE HUFFMANN **************************/
/**********************************************************************/

void init_Arbre(int tab[TAILLE_ASCII], Noeud** arbre, int* ptr_taille){
	*ptr_taille = 0;
		
	for (int i=0; i<TAILLE_ASCII; i++){
		if(tab[i] != 0)
			*ptr_taille = (*ptr_taille + 1);
	}
	
	*arbre = malloc((*ptr_taille)*sizeof(Noeud));
	*ptr_taille = 0;
	for (int i=0; i<TAILLE_ASCII; i++){
		if(tab[i] != 0){
			(*arbre)[*ptr_taille].data = i;
			(*arbre)[*ptr_taille].frequence = tab[i];
			(*arbre)[*ptr_taille].left = NULL;
			(*arbre)[*ptr_taille].right = NULL;	
			*ptr_taille = (*ptr_taille + 1);		
		}
	}
}


void permutter(Noeud** arbre, int j, int k){
	Noeud transition = (*arbre)[j];
	(*arbre)[j] = (*arbre)[k];
	(*arbre)[k] = transition;
}

void trier_Arbre(Noeud** arbre, int taille){
	for (int i=1; i<taille; i++){
		int j = i;
		int k = i-1;
		while (k>=0 && (*arbre)[j].frequence < (*arbre)[k].frequence){
			permutter(arbre, j, k);
			j = j-1;
			k = k-1;
		}
	}
}


void regrouper(Noeud** arbre, int* ptr_taille){
	
		Noeud* left = malloc(sizeof(Noeud));
		Noeud* right = malloc(sizeof(Noeud));
		
		*left = (*arbre)[0];
		*right = (*arbre)[1];
		(*arbre)[0].frequence = left->frequence + right->frequence;
		(*arbre)[0].data = '\0';
		(*arbre)[0].left = left;
		(*arbre)[0].right = right;
		
		
		
		*ptr_taille = *ptr_taille-1;
		
		for (int i=2; i<=(*ptr_taille); i++)
			(*arbre)[i-1] = (*arbre)[i];
}



void faire_arbre(Noeud** arbre, int tab[TAILLE_ASCII], int* taille){
	
	init_Arbre(tab, arbre, taille);
	
	while (*taille > 1){ 
		trier_Arbre(arbre, *taille);
		regrouper(arbre, taille);
	}
}


void erase(Noeud** arbre){
	
	if ((*arbre)->left != NULL){
		erase(&(*arbre)->left);
		free((*arbre)->left);
	}
	if ((*arbre)->right != NULL){
		erase(&(*arbre)->right);
		free((*arbre)->right);
	}
}
	
void afficher_arbre(Noeud* arbre, int tabulation){
	
	for (int i=0; i<tabulation; i++)
		printf("      ");
		
	printf("(%d)\\%c \n", arbre->frequence, arbre->data);
	
	if(arbre->left != NULL){
			for (int i=0; i<tabulation; i++)
				printf("      ");
				
			printf("\\--0--\\\n");
			afficher_arbre(arbre->left, tabulation+1);
	}
	
	if(arbre->right != NULL){
		
		for (int i=0; i<tabulation; i++)
			printf("      ");
			
		printf("\\--1--\\\n");
		afficher_arbre(arbre->right, tabulation+1);
	}
}
