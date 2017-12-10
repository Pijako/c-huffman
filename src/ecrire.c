#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "compress.h"
#include <malloc.h>
#define TAILLE_ASCII 256
#define TAILLE_OCTET 8
void ecrire_caractere_infixe(Noeud* arbre,FILE* stream){
	//on parcourt l'arbre de maniere infixe et on ecrit dans le fichier
	//les caracteres que l'on rencontre
	
	if (arbre->left == NULL && arbre->right == NULL)
		fwrite(&(arbre->data), sizeof(unsigned char), 1, stream);
	
	if (arbre->left != NULL) 
		ecrire_caractere_infixe(arbre->left,stream);
	
	if (arbre->right != NULL)
		ecrire_caractere_infixe(arbre->right,stream);
}


void encoder(int texte, Dict dict[TAILLE_ASCII],int* taille, int* dispo, unsigned char** texte_code){
	/* texte = caractere a ecrire encode dans *texte_code */
	/* dispo = bits disponibles dans l'octet d'ecriture   */
	/* taille = nombre d'octets pleins dans texte_code    */
	
	//codage par Huffman du caractere
	unsigned char code = dict[texte].code;
	
	//nbre de bits utiles dans le codage
	int etage = dict[texte].etage;
	
	//si il y a assez de place pour ecrire le caractere
	if (etage <= *dispo){													 
		(*texte_code)[*taille] = (*texte_code)[*taille] + (code<<(*dispo-etage)); 
		*dispo = *dispo - etage;
		
	//sinon on rajoute un octet
	}else{
		//on remplit l'octet courant																 
		(*texte_code)[*taille] = (*texte_code)[*taille] + (code>>(etage-*dispo));
		//puis on en ajoute un nouveau
		unsigned char *nouveau = realloc(*texte_code, sizeof(unsigned char)*(*taille + 2));
		assert(nouveau != NULL);
		*texte_code = nouveau;
		*taille = *taille +1;
		(*texte_code)[*taille] = code<<(TAILLE_OCTET - (etage - *dispo));			
		*dispo = TAILLE_OCTET - (etage - *dispo);										
	}
}

void ecrire_parcours_infixe(FILE* stream, unsigned char* parcours){
	
}
	

void ecrire(Noeud* arbre, FILE* stream, Dict dict[TAILLE_ASCII]){
	unsigned char taille_arbre = compter_taille_arbre(dict);
	unsigned int taille = arbre->frequence;
	
	//4 octets pour le nbre de caracteres total
	fwrite(&taille, sizeof(unsigned int), 1, stream); 	
	
	//1 octet pour le nbre de caracteres differents		
	fwrite(&taille_arbre, sizeof(unsigned char), 1, stream); 	
	
	//on ecrit les caracteres dans leur ordre infixe d'apparition dans
	//l'arbre	
	ecrire_caractere_infixe(arbre, stream);
	
	//on recupere le parcours infixe de l'arbre
	int longueur = 1;
	unsigned char* infixe = malloc(sizeof(unsigned char));
	parcours_infixe(arbre, infixe, &longueur);
	
	//on l'ecrit dans le fichier en binaire
	int dispo=TAILLE_OCTET;
	unsigned char* texte_code = malloc(sizeof(unsigned char));
	int taille_tab = 0;
	FILE* stream_a_lire;
	stream_a_lire = fopen("file.txt", "r");	
	assert(stream_a_lire != NULL);
	int car = fgetc(stream_a_lire);							
	while(car != EOF){
		encoder(car, dict, &taille_tab, &dispo, &texte_code);
		car = fgetc(stream_a_lire);
	}
	fwrite(texte_code, sizeof(unsigned char), taille_tab+1, stream);
	if (stream_a_lire == NULL)
		fclose(stream_a_lire);
	
	
	for (int i=0; i<longueur; i++){
		printf("%d", infixe[i]);
	}
	printf("\n");
	free(texte_code);
}
