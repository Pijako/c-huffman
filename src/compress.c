#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "compress.h"
#include <malloc.h>

#define TAILLE_OCTET 8

void init_dict(Dict dict[TAILLE_ASCII]){
		for (int i=0; i<TAILLE_ASCII; i++){
			dict[i].data = i;
			dict[i].code = 0;
			dict[i].etage = 0;
		}
}

void dictionnaire (Noeud* arbre, Dict dict[TAILLE_ASCII], unsigned char code, int etage){
	
	//si on arrive sur une feuille on sauvegarde le codage
	if (arbre->left == NULL && arbre->right == NULL){ 
		dict[arbre->data].data = arbre->data;
		dict[arbre->data].code = code;
		//l'etage permet de connaitre le nbre de bits utiles 
		//dans le codage
		dict[arbre->data].etage = etage; 
	}
	
	//si il existe un fils gauche on decale ajoute un zero a droite au codage 
	if (arbre->left != NULL) 
		dictionnaire(arbre->left, dict, code<<1, etage+1); 
	
	//de meme a droite	
	if (arbre->right != NULL) 
		dictionnaire(arbre->right, dict, (code<<1)+1, etage+1);
}

void afficher_dictionnaire(Dict dict[TAILLE_ASCII]){
	
	//le codage des caracteres etant fait en binaire un affichage 
	//specifique est necessaire
	
	for (int i=0; i<TAILLE_ASCII; i++){
		if (dict[i].etage != 0){
			printf("%c->",dict[i].data);
			unsigned char codage= dict[i].code;
			int etage = dict[i].etage;
			for (int j=0; j<etage;j++){
				codage = dict[i].code;
				codage = codage<<(TAILLE_OCTET - etage + j);
				codage = codage>>(TAILLE_OCTET-1);
				printf("%u", (codage));
			}
			printf("\n");
		}
	}
}



unsigned char compter_taille_arbre(Dict dict[TAILLE_ASCII]){
	
	unsigned char taille = 0;
	
	for (int i=0; i<TAILLE_ASCII; i++)
		if (dict[i].etage != 0)
			taille++;
			
	return taille;
}



void ajout_trajet(unsigned char* parcours, int* longueur, int binary){
	parcours[*longueur-2] = binary;
	*longueur = *longueur +1;
	unsigned char* nouveau = realloc(parcours, sizeof(unsigned char)*(*longueur));
	assert(nouveau != NULL);
	parcours = nouveau;
}
void parcours_infixe(Noeud* arbre, unsigned  char* parcours, int* longueur){
	//on sauvegarde le parcourt infixe dans un tablleau d'unsigned char
	//longueur designe le nombre d'octet alloues

	if (arbre->left != NULL && arbre->right != NULL){
		//on descend dans l'arbre gauche => on ajoute un 0
		ajout_trajet(parcours, longueur, 0);
		parcours_infixe(arbre->left, parcours, longueur);
		
		//on descend dans l'arbre droit ce qui signifie que l'on
		//est remonte depuis l'arbre gauche => on ajoute un 0
		ajout_trajet(parcours, longueur, 1);
		parcours_infixe(arbre->right, parcours, longueur);
		//une fois l'arbre droit parcourut il faut 
		//revenir a l'ascendance
		ajout_trajet(parcours, longueur, 1);
	
	}else{
		//si l'on est sur une feuille on descend dans celle-ci
		ajout_trajet(parcours, longueur, 0);
	}
}




