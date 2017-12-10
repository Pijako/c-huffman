#include <stdlib.h>
#include <stdio.h>

#include "types.h"

void read_infos(FILE* compressed_file, Infos *infos);
// Lit la taille du texte, de l'arbre et les caractères utilisés

void ajouter_noeud(Noeud* arbre, int direction, int data);
//Permet d'ajouter des branches ou des feuilles lors de la reconstruction de l'arbre

void create_tree(FILE* compressed_file, Noeud* arbre, char* tab);
//Recréation de l'arbre

void display_tree(Noeud* arbre, int tabulation);
//Affiche l'arbre

void create_dict(FILE* file, Infos *infos);
//On recréé le dictionnaire

void generate_file(FILE* compressde_file, Infos *infos);
//On en déduit le fichier décompressé





