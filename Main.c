#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include "Grille.h"
#include "Serpent.h"
#include "Fonction_Jeu_1_serpent.h"

int main() {
    srand(time(NULL));
    int n, m, vitesse;

    printf("\33[2J"); 
    printf("\33[H");

    // Paramètres du jeu Snake
    printf("\33[37mBienvenue dans Snake !\n");
    printf("Choisissez la longueur de la grille : ");
    scanf("%d", &n);
    printf("Choisissez la largeur de la grille : ");
    scanf("%d", &m);
    printf("Choisissez la vitesse à laquelle vous voulez jouer (1 = rapide, plus grand = plus lent) : ");
    scanf("%d", &vitesse);

    struct grille *G = Grille_allouer(n, m);
    Grille_vider(G);
    Grille_tirage_fruit(G);

    struct serpent *Snake = creer_serpent(n / 2, m / 2);

    if (jeu(G, Snake, vitesse) == 1) {
        printf("\33[31mVous avez perdu !\n");
    }

    return EXIT_SUCCESS;
}
