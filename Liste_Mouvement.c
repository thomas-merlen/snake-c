#include"Liste_Mouvement.h"
#include<stdio.h>
#include<stdlib.h>


struct section_mvt *creer_section_mvt(struct coord coord,int direction) {
  struct section_mvt *s = malloc(sizeof(struct section_mvt));
  s->coord.x = coord.x;
  s->coord.y = coord.y;
  s->direction=direction;
  s->suivant = NULL;
  return s;
}


void desallouer_section_mvt(struct section_mvt *s) {
  if (s != NULL) {
    free(s);
    s = NULL;
  }
}

struct liste_mvt *nouvelle_liste_mvt() {
  struct liste_mvt *l = malloc(sizeof(struct liste_mvt));
  l->premier = NULL;
  l->dernier = NULL;
  l->longueur = 0;
  return l;
}


void ajouter_section_mvt_debut(struct liste_mvt *l, struct section_mvt *s) {
  if (l->longueur==0) {  
  	l->dernier = s; 
  }
  s->suivant = l->premier;
  l->premier = s;
  ++l->longueur;
}


struct section_mvt *extraire_section_mvt_debut(struct liste_mvt *l) {
  struct section_mvt *s = l->premier;
  if (s != NULL) {
    l->premier = s->suivant;
    --l->longueur;
    if (l->longueur==0) { l->dernier = NULL; }
    s->suivant = NULL;
  }
  return s;
}


void detruire_liste_mvt (struct liste_mvt *l) {
  if (l != NULL) {
    while ((l)->longueur!=0) {
      struct section_mvt *s = extraire_section_mvt_debut(l);
      desallouer_section_mvt(s);
    }
    free(l);
    l = NULL;
  }
}
 
 
void ajouter_section_mvt_queue(struct liste_mvt *l,struct section_mvt *s){
  s->suivant=NULL;
	if(l->longueur==0)
	{
    l->premier=s;
	}
	else
	{
    l->dernier->suivant=s;
	}
  l->longueur++;
  l->dernier=s;
}
