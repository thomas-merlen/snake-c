#include <ncurses.h>
#include "Fonction_Jeu_1_serpent.h"
#include "Serpent.h"
#include <string.h>
#include <stdlib.h>
#include "Grille.h"

int gameover1(struct grille* G, struct serpent* S) {
    // Si le serpent sort de la grille OU touche certaines couleurs (le corps du serpent)
    if (S->tete.x < 0 || S->tete.y < 0 || S->tete.x == G->n || S->tete.y == G->m || 
        (strcmp(G->tab[S->tete.x][S->tete.y], "\33[42m  ") == 0 ||
         strcmp(G->tab[S->tete.x][S->tete.y], "\33[43m  ") == 0 ||
         strcmp(G->tab[S->tete.x][S->tete.y], "\33[44m  ") == 0 ||
         strcmp(G->tab[S->tete.x][S->tete.y], "\33[45m  ") == 0 ||
         strcmp(G->tab[S->tete.x][S->tete.y], "\33[46m  ") == 0 ||
         strcmp(G->tab[S->tete.x][S->tete.y], "\33[47m  ") == 0)) {
        return -1; // Game over
    }
    return 0;
}


char* generer_couleur() {
    int nb = 42 + rand() % 6; // Choisit un code de couleur ANSI entre 42 et 47
    char* couleur = (char*)malloc(sizeof(char) * 8); // Alloue une chaîne
    if (couleur == NULL) {
        fprintf(stderr, "Impossible d’allouer la mémoire\n");
    }
    snprintf(couleur, 8, "\33[%dm  ", nb); // Formate la couleur en chaîne ANSI
    return couleur;
}


void manger_fruit(struct serpent* S) {
    // Ajoute entre 1 et 5 nouvelles sections au serpent
    for (int i = 0; i <= rand() % 5 + 1; i++) {
        struct section* Sec = creer_section(1, generer_couleur()); // Crée une nouvelle section colorée
        ajouter_section_queue(S->corps, Sec); // L'ajoute à la fin du serpent
    }
}


int jeu(struct grille* G, struct serpent* S, int vitesse) {
    // Initialisation de ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE); // Permet d'utiliser les touches fléchées
    noecho();

    int score = 0;
    int car; // touche pressée
    int est_fruit = 1; // indique si le fruit est mangé ou non
    int der_car; // dernière touche valide

    // Ajoute un mouvement initial vers la gauche (code 4)
    ajouter_section_mvt_debut(S->mvt, creer_section_mvt(S->tete, 4));

    // Efface l'écran
    printf("\33[2J");
    printf("\33[H");

    // Affiche la grille initiale
    Grille_remplir_serpent(G, S);
    Grille_tirage_fruit(G);
    Grille_remplir(G);
    Grille_redessiner(G);
    halfdelay(vitesse); // définit le délai d'attente entre chaque tour

    // Boucle principale du jeu
    do {
        est_fruit = 1;
        car = getch(); // lit la touche appuyée

        // Si aucune touche appuyée, on garde la direction précédente
        if (car == -1) {
            car = der_car;
        }

        // Déplacement du serpent selon la touche appuyée
        switch (car) {
            case KEY_UP:
                if (der_car != KEY_DOWN || S->corps->premier == NULL) {
                    ajouter_section_mvt_debut(S->mvt, creer_section_mvt(S->tete, 1));
                    S->tete.x--;
                    der_car = KEY_UP;
                }
                break;

            case KEY_DOWN:
                if (der_car != KEY_UP || S->corps->premier == NULL) {
                    ajouter_section_mvt_debut(S->mvt, creer_section_mvt(S->tete, 3));
                    S->tete.x++;
                    der_car = KEY_DOWN;
                }
                break;

            case KEY_LEFT:
                if (der_car != KEY_RIGHT || S->corps->premier == NULL) {
                    ajouter_section_mvt_debut(S->mvt, creer_section_mvt(S->tete, 4));
                    S->tete.y--;
                    der_car = KEY_LEFT;
                }
                break;

            case KEY_RIGHT:
                if (der_car != KEY_LEFT || S->corps->premier == NULL) {
                    ajouter_section_mvt_debut(S->mvt, creer_section_mvt(S->tete, 2));
                    S->tete.y++;
                    der_car = KEY_RIGHT;
                }
                break;
        }

        // Si le serpent mange un fruit
        if (S->tete.x == G->fruit.x && S->tete.y == G->fruit.y) {
            est_fruit = 0;
            manger_fruit(S);
            score++;
        }

        // Mise à jour de l'écran
        fflush(stdout);
        printf("\33[2J");
        printf("\33[H");

        Grille_vider(G); // vide la grille

        // Si un fruit a été mangé, on en génère un autre à une case libre
        if (!est_fruit) {
            do {
                Grille_tirage_fruit(G);
            } while (strcmp(G->tab[G->fruit.x][G->fruit.y], "\33[42m:p") == 0 ||
                     strcmp(G->tab[G->fruit.x][G->fruit.y], S->corps->premier->couleur) == 0);
        }

        // On met à jour la grille avec le serpent et le fruit
        Grille_remplir(G);
        Grille_remplir_serpent(G, S);
        Grille_redessiner(G);

    } while (gameover1(G, S) != -1); // on continue tant que le jeu n’est pas perdu

    endwin(); // Fin de l’interface ncurses

    printf("\33[37mVotre score est : %d\n", score); // Affiche le score

    return 1; // Retour de fin
}
