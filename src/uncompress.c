#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "types.h"

#define TAILLE_ASCII 256
#define TAILLE_BUFFER 8
#define TAILLE_OCTET 8

void read_infos(FILE* compressed_file, Infos *infos){
	
	int taille[4];
	char car;
	
	for(int i=0;i<=3;i++){
		taille[i] = fgetc(compressed_file);
	}
	infos->text_size = taille[0]+taille[1]*256+taille[2]*pow(256, 2)+taille[3]*pow(256,3); //Taille du texte
	
	infos->tree_size = fgetc(compressed_file); //On recupere la taille de l'arbre
	infos->used_char = malloc(sizeof(char) * (infos->tree_size));
	printf("Taille du texte : %d\n", infos->text_size);
	printf("Taille de l'arbre : %i\n", infos->tree_size);
	
	for (int i=0; i<infos->tree_size; i++){ //On récupère les caractères utilisés
		car = fgetc(compressed_file);
		infos->used_char[i] = car;
		printf("%c", car);
	}
	printf("\n");
}

void ajouter_noeud(Noeud* arbre, int direction, int data){
	Noeud* fils;
	
	if(direction==0){	
			//0 fils gauche
		arbre->left = malloc(sizeof(Noeud));
		fils = arbre->left;
	}
	else{
		arbre->right = malloc(sizeof(Noeud));
		fils = arbre->right;
	}
	
	fils->frequence = 1; //on place une valeur par default
	fils->data = data;
	fils->left = NULL;
	fils->right = NULL;
	fils->previous = arbre;
}

void create_tree(FILE* compressed_file, Infos *infos, Noeud* arbre){
	//on lit maintenant le parcours infixe de l'arbre
	unsigned char buffer[TAILLE_BUFFER];
	int j=0;
	int num_car_lu = 0;
	int m=0;

	arbre = malloc(sizeof(Noeud));
	
	do {
		unsigned char car = fgetc(compressed_file);
		for(int i = 128; i; i >>= 1){
			if(car & i == 1){
				buffer[i] = 1;
			}
			else{
				buffer[i] = 0;	
			}
		}
		for(int j=0;j<=7;j++) printf("%c\n", buffer[j]);
		printf("buffer ok\n");
		while(m<TAILLE_BUFFER-1 && j<infos->tree_size){			//on parcourt le buffer
			if (buffer[m] == 0){
				if(arbre->left == NULL){
					ajouter_noeud(arbre, 0, '\0');
				}else{
					ajouter_noeud(arbre, 1, '\0');
				}
			}else{
				if (buffer[m-1] == 0){	
					arbre->data = infos->used_char[num_car_lu];
					num_car_lu++;
					arbre = arbre->previous;
					j++;
				}else{
					arbre = arbre->previous;
				}
			}
			m++;
		}	
	}while(j<infos->tree_size);
}

void display_tree(Noeud* arbre, int tabulation){
	
	for (int i=0; i<tabulation; i++){
		printf("      ");
	}
	
	printf("(%d)\\%c \n", arbre->frequence, arbre->data);
	
	if(arbre->left != NULL){
		for (int i=0; i<tabulation; i++){
			printf("      ");
			printf("\\--0--\\\n");
			display_tree(arbre->left, tabulation+1);
		}
	}
	
	if(arbre->right != NULL){
		for (int i=0; i<tabulation; i++){
			printf("      ");
		}
		printf("\\--1--\\\n");
		display_tree(arbre->right, tabulation+1);
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

void create_dict(FILE* file, Infos *infos, Tree tree){
	
	char car;
	char *buffer = malloc(sizeof(char));
	Tree curseur;
	curseur = tree;
	int num_read_char = 0;
	
	while((car = fgetc(file)) != EOF){
		for(int i=0;i<=8;i++){
			
				buffer[i] = (car<<i)>>7;
					
				if(buffer[i] == 0){
					curseur = curseur->left;
					if(curseur->data != '\0'){
						infos->dict[num_read_char].num = num_read_char;
						strcpy(&infos->dict[num_read_char].bin, buffer);
						strcpy(&infos->dict[num_read_char].caractere, &curseur->data);
						num_read_char++;
						curseur = tree;
						buffer = 0;
					}
				}
				else{
					curseur = curseur->right;
					if(curseur->data != '\0'){
						infos->dict[num_read_char].num = num_read_char;
						strcpy(&infos->dict[num_read_char].bin, buffer);
						strcpy(&infos->dict[num_read_char].caractere, &curseur->data);
						num_read_char++;
						curseur = tree;
						buffer = 0;
					}
				}
		}
	}
	free(buffer);
}

int main(int argc, char *argv[]){

	FILE* compressed_file = NULL;
	Infos *infos;
	Tree arbre;
    
	compressed_file = fopen("file.hf", "r+");
	
	read_infos(compressed_file, infos);
	
	create_tree(compressed_file, infos, arbre);
	
	//display_tree(arbre, 0);

	erase(&arbre);		

	fclose(compressed_file);

}
