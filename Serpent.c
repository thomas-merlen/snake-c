#include"Serpent.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"Grille.h"
		
struct serpent * creer_serpent(int x, int y) {
    struct serpent * S = malloc(sizeof(struct serpent)); // allocation mémoire pour le serpent
    S->tete.x = x;       // position initiale de la tête en coordonnée x
    S->tete.y = y;       // position initiale de la tête en coordonnée y
    S->corps = nouvelle_liste();      // corps du serpent : liste chaînée de sections
    S->mvt = nouvelle_liste_mvt();    // liste des mouvements (directions et coordonnées)
    return S;           // retourne le pointeur vers le serpent créé
}
	



void Grille_remplir_serpent(struct grille * G, struct serpent * S) {
    int i;
    struct section *M = S->corps->premier;     // pointeur sur la première section du corps
    struct section_mvt *Sec = S->mvt->premier; // pointeur sur la première section de mouvement
    struct coord dernier;

    G->tab[S->tete.x][S->tete.y] = "\33[42m:p"; // place la tête du serpent dans la grille (couleur verte avec ":p")

    dernier.x = S->tete.x;  // position courante initialisée à la tête
    dernier.y = S->tete.y;

    while (M != NULL) {    // pour chaque section du corps
        switch (Sec->direction) {   // selon la direction enregistrée dans la liste des mouvements

            case 1:  // direction vers le haut (décalage x++)
                for (i = 0; i < M->taille; i++) {
                    dernier.x++;                        // avance d'une case vers le bas (x+1)
                    G->tab[dernier.x][dernier.y] = M->couleur;  // remplit la grille avec la couleur de la section
                    if (dernier.x == Sec->coord.x && dernier.y == Sec->coord.y) {
                        Sec = Sec->suivant;            // changement de direction à ce point
                    }
                }
                break;

            case 2:  // direction vers la gauche (décalage y--)
                for (i = 0; i < M->taille; i++) {
                    dernier.y--;                       // avance d'une case vers la gauche (y-1)
                    G->tab[dernier.x][dernier.y] = M->couleur;
                    if (dernier.x == Sec->coord.x && dernier.y == Sec->coord.y) {
                        Sec = Sec->suivant;
                    }
                }
                break;

            case 3:  // direction vers le bas (décalage x--)
                for (i = 0; i < M->taille; i++) {
                    dernier.x--;                       // avance d'une case vers le haut (x-1)
                    G->tab[dernier.x][dernier.y] = M->couleur;
                    if (dernier.x == Sec->coord.x && dernier.y == Sec->coord.y) {
                        Sec = Sec->suivant;
                    }
                }
                break;

            case 4:  // direction vers la droite (décalage y++)
                for (i = 0; i < M->taille; i++) {
                    dernier.y++;                       // avance d'une case vers la droite (y+1)
                    G->tab[dernier.x][dernier.y] = M->couleur;
                    if (dernier.x == Sec->coord.x && dernier.y == Sec->coord.y) {
                        Sec = Sec->suivant;
                    }
                }
                break;

            default:
                break;
        }

        M = M->suivant;  // passe à la section suivante du corps
    }
}

	
	

	
	
