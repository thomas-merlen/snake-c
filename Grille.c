#include"Grille.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


//Définition des fonctions déclarées dans Grille.h


struct grille *Grille_allouer(int n,int m){
    int i, j;
    struct grille* G = malloc(sizeof(struct grille)); // allocation de la structure grille
    G->n = n; // nombre de lignes
    G->m = m; // nombre de colonnes

    if (G == NULL) { // vérification de l'allocation
        fprintf(stderr,"Impossible d'allouer de l'espace mémoire\n");
        return NULL;
    }

    G->tab = malloc(sizeof(char**) * G->n); // allocation des lignes de la grille

    for (i = 0; i < G->n; i++) {
        *(G->tab + i) = malloc(sizeof(char*) * G->m); // allocation des colonnes pour chaque ligne
        for (j = 0; j < G->m; j++) {
            *(*(G->tab + i) + j) = malloc(sizeof(char) * 8); // chaque case peut contenir une chaîne ANSI
        }
    }

    return G;
}


void Grille_vider(struct grille* G){
    int i, j;
    for (i = 0; i < G->n; i++) {
        for (j = 0; j < G->m; j++) {
            G->tab[i][j] = "\33[40m  "; // couleur noire par défaut (fond vide)
        }
    }
}


void Grille_tirage_fruit(struct grille* G){
    G->fruit.x = rand() % (G->n); // position aléatoire ligne
    G->fruit.y = rand() % (G->m); // position aléatoire colonne
}


void Grille_remplir(struct grille* G){
    G->tab[G->fruit.x][G->fruit.y] = "\33[41m  "; // place le fruit avec fond rouge
}


void Grille_desallouer(struct grille* G){
    int i, j;
    for (i = 0; i < G->n; i++) {
        for (j = 0; j < G->m; j++) {
            free(G->tab[i][j]); // libère chaque case
        }
        free(G->tab[i]); // libère chaque ligne
    }
    free(G->tab); // libère le tableau de pointeurs de lignes
    free(G); // libère la structure grille elle-même
}


void Grille_redessiner(struct grille* G){
    int i, j, k;

    // Affiche une bordure supérieure bleue
    for (k = 0; k < G->m + 2; k++)
        printf("\33[44m  "); // fond bleu
    printf("\33[00m  "); // reset couleur
    printf("\n\r");

    // Affichage de chaque ligne de la grille
    for (i = 0; i < G->n; i++) {
        printf("\33[44m  "); // bordure gauche
        for (j = 0; j < G->m; j++) {
            printf("%s", G->tab[i][j]); // affiche le contenu de la case
        }
        printf("\33[44m  "); // bordure droite
        printf("\33[00m  ");
        printf("\n\r");
    }

    // Bordure inférieure
    for (k = 0; k < G->m + 2; k++)
        printf("\33[44m  ");
    printf("\33[00m  ");
    printf("\n");
}


































	
	
