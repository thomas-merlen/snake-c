#ifndef _GRILLE_H
#define _GRILLE_H

//Structure des coordonnées
struct coord{
	int x; //coordonnée horizontale
	int y; //coordonnée verticale
};

//Structure de la grille
struct grille{
	int n; //nb lignes
	int m; //nb colonnes
	char *** tab; //tab à 2 dimensions de chaines de caractères
	struct coord fruit; //coordonnées de la case contenant le fruit
};

//Déclaration des fonctions définies dans Grille.c

struct grille *Grille_allouer(int n,int m);

void Grille_vider(struct grille*);

void Grille_tirage_fruit(struct grille*);

void Grille_remplir(struct grille*);

void Grille_desallouer(struct grille*);

void Grille_redessiner(struct grille*);







#endif
