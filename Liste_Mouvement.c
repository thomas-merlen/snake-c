#include"Liste_Mouvement.h"
#include<stdio.h>
#include<stdlib.h>


struct section_mvt *creer_section_mvt(struct coord coord, int direction) {
  struct section_mvt *s = malloc(sizeof(struct section_mvt)); // alloue une nouvelle section de mouvement
  s->coord.x = coord.x;
  s->coord.y = coord.y;
  s->direction = direction; // 1 = haut, 2 = droite, 3 = bas, 4 = gauche
  s->suivant = NULL;
  return s;
}



void desallouer_section_mvt(struct section_mvt *s) {
  if (s != NULL) {
      free(s);     // libère la mémoire
      s = NULL;    // évite les pointeurs sauvages (même si local ici)
  }
}


struct liste_mvt *nouvelle_liste_mvt() {
  struct liste_mvt *l = malloc(sizeof(struct liste_mvt)); // alloue une nouvelle liste
  l->premier = NULL;  // tête vide
  l->dernier = NULL;  // queue vide
  l->longueur = 0;
  return l;
}


void ajouter_section_mvt_debut(struct liste_mvt *l, struct section_mvt *s) {
  if (l->longueur == 0) {
      l->dernier = s; // si liste vide, le dernier devient aussi le nouvel élément
  }
  s->suivant = l->premier; // insère en tête
  l->premier = s;
  ++l->longueur;
}



struct section_mvt *extraire_section_mvt_debut(struct liste_mvt *l) {
  struct section_mvt *s = l->premier;
  if (s != NULL) {
      l->premier = s->suivant; // passe au suivant
      --l->longueur;
      if (l->longueur == 0) {
          l->dernier = NULL; // si vide, mettre à jour dernier
      }
      s->suivant = NULL; // on détache la section extraite
  }
  return s;
}



void detruire_liste_mvt(struct liste_mvt *l) {
  if (l != NULL) {
      while ((l)->longueur != 0) {
          struct section_mvt *s = extraire_section_mvt_debut(l); // extrait une à une
          desallouer_section_mvt(s); // libère chaque section
      }
      free(l); // libère la structure liste elle-même
      l = NULL;
  }
}

 
void ajouter_section_mvt_queue(struct liste_mvt *l, struct section_mvt *s) {
  s->suivant = NULL; // fin de liste
  if (l->longueur == 0) {
      l->premier = s; // si vide, premier = nouvel élément
  } else {
      l->dernier->suivant = s; // relie à la fin
  }
  l->longueur++;
  l->dernier = s; // met à jour le dernier
}

