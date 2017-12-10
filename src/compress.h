#include "types.h"
#define TAILLE_ASCII 256

void init_tab_freq(int tab[TAILLE_ASCII]);
//Procedure initialisant toutes les cases du tableau tab a 0

void table_frequence(char* path, int tab[TAILLE_ASCII]);
//Procedure de fabrication de la table de frequence du fichier fp

void init_Arbre(int tab[TAILLE_ASCII], Noeud** arbre, int* ptr_taille);
//Procedure d'initialisation de l'arbre de Huffman (tableau dynamique de Noeuds)

void trier_Arbre(Noeud** arbre, int taille);
//Procedure de tri par ordre croissant des Noeuds de l'arbre suivant leur "frequence"

void regrouper(Noeud** arbre, int* ptr_taille);
//Procedure regroupant les 2 premiers noeuds de l'arbre en un seul ayant pour descendance 
//les 2 noeuds ainsi regroupés

void generer_dict(Noeud* arbre, Dict* dict);
//Procedure de creation du dictionnaire a partir de l'arbre complet de Huffman

void compresser(Noeud* arbre, FILE* fp);
//procedure de d'ecriture du fichier compresse

void afficher_tab_freq(int tab[TAILLE_ASCII]);
//affiche la table de frequence

void permutter(Noeud** arbre, int j, int k);
//permutte dans le tableau de noeuds "arbre" les noeuds aux indices j et k
//Necessite que j et k <= taille(arbre)

void afficher_arbre(Noeud* arbre, int tabulation);
//affiche l'arbre de huffman

void faire_arbre(Noeud** arbre, int tab[TAILLE_ASCII], int* taille);
void erase(Noeud** arbre);
void dictionnaire (Noeud* arbre, Dict dict[TAILLE_ASCII], unsigned char code, int etage);
void afficher_dictionnaire(Dict dict[TAILLE_ASCII]);
void init_dict(Dict dict[TAILLE_ASCII]);
void printf_arbre(Noeud arbre[], int taille);
void ecrire(Noeud* arbre, FILE* stream, Dict dict[TAILLE_ASCII]);
unsigned char compter_taille_arbre(Dict dict[TAILLE_ASCII]);
void parcours_infixe(Noeud* arbre, unsigned  char* parcours, int* longueur);
