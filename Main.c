#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ncurses.h>
#include<stdlib.h>
#include"Grille.h"
#include"Serpent.h"
#include"Fonction_Jeu_1_serpent.h"

int main(int argc,char**argv){
	srand(time(NULL));
	int n;
	int m;
	int vitesse;
	int jeux;
	
	/*if(argc!=5){
		fprintf(stderr,"Erreur nombre d'arguments\n");
		return EXIT_FAILURE;
	}
	jeux=argv[4];
	if(strcmp(jeux,"snake")!=0){
		printf("Ce jeu n'existe pas.\n");
		return EXIT_FAILURE;
		}		
		
	vitesse=atoi(argv[3]);
	n=atoi(argv[1]);
	m=atoi(argv[2]);*/
	
	
	
	printf("\33[2J"); 
   	printf("\33[H");
	menu();
	printf("\33[37mChoisissez un jeu parmi les jeux suivants:\n\r ");
	printf("\33[32m[1] snake\n\r ");
	printf("\33[35m[2] GTA6\n\r ");
	printf("\33[93m[3] tetris\n\r ");
	printf("\33[37m\n");
	scanf("%d", &jeux);
	switch(jeux){
		case 1:
			printf("Choisissez la longueur de la grille\n");
			scanf(" %d", &n );
			printf("Choisissez la largeur de la grille\n");
			scanf(" %d", &m );
			printf("Choisissez la vitesse à laquelle vous voulez jouer\n");
			scanf(" %d", &vitesse);
			
			struct grille *G=Grille_allouer(n,m);
		Grille_vider(G);
		Grille_tirage_fruit(G);
		//Grille_remplir(G);
		struct serpent *Snake=creer_serpent((G->n)/2,(G->m)/2);
		//struct section *Sec=creer_section(taille,couleur);
		//ajouter_section_debut(Snake->corps,Sec);
		//Grille_remplir_serpent(G,Snake);
		//Grille_redessiner(G);
		if(jeu(G,Snake,vitesse)==1){
			printf("\33[31mGAMEOVER\n");
		}
		//Grille_desallouer(G);
		break;
		case 2:case 3:
			printf("Jeu en cours de developpement...\n");
		default:
			break;
	}
}	
	
