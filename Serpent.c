#include"Serpent.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"Grille.h"
		
struct serpent * creer_serpent(int x,int y){
	struct serpent * S = malloc(sizeof(struct serpent));
	S->tete.x=x;
	S->tete.y=y;
	S->corps = nouvelle_liste();
	S->mvt=nouvelle_liste_mvt();
	return S;
}		



void Grille_remplir_serpent(struct grille * G,struct serpent * S){
	int i;
	struct section *M=S->corps->premier;
	struct section_mvt *Sec=S->mvt->premier;
	struct coord dernier;
	G->tab[S->tete.x][S->tete.y] = "\33[42m:p";
	dernier.x=S->tete.x;
	dernier.y=S->tete.y;
	while(M!=NULL){
		switch(Sec->direction){
		
			case 1:
				for(i=0;i<M->taille;i++){
					dernier.x++;
					G->tab[dernier.x][dernier.y]=M->couleur;
					if (dernier.x==Sec->coord.x && dernier.y==Sec->coord.y){
						Sec=Sec->suivant;
					}
				}
				break;
				
			case 2:
				for(i=0;i<M->taille;i++){
					dernier.y--;
					G->tab[dernier.x][dernier.y]=M->couleur;
					if (dernier.x==Sec->coord.x && dernier.y==Sec->coord.y){
						Sec=Sec->suivant;
					}
				}
				break;
			
			case 3:
				for(i=0;i<M->taille;i++){
					dernier.x--;
					G->tab[dernier.x][dernier.y]=M->couleur;
					if (dernier.x==Sec->coord.x && dernier.y==Sec->coord.y){
						Sec=Sec->suivant;
					}
				}
				break;
			
			case 4:
				for(i=0;i<M->taille;i++){
					dernier.y++;
					G->tab[dernier.x][dernier.y]=M->couleur;
					if (dernier.x==Sec->coord.x && dernier.y==Sec->coord.y){
						Sec=Sec->suivant;
					}
				}
				break;
	
			default:
				break;
		}
	
	
		M=M->suivant;
	}
}
	
	

	
	
