#include"Liste_Section.h"
#include<stdio.h>
#include<stdlib.h>


struct section *creer_section(int t, char *c) {
  struct section *s = malloc(sizeof(struct section)); // alloue une section
  s->taille = t;         // taille (longueur visuelle)
  s->couleur = c;        // couleur (chaine ANSI, ex: "\33[42m  ")
  s->suivant = NULL;     // pas de suivant
  return s;
}


void desallouer_section(struct section **m) {
  if (*m != NULL) {
    free((*m)->couleur); // libère la chaîne de couleur
    free(*m);            // libère la section elle-même
    *m = NULL;           // évite un pointeur sauvage
  }
}


struct liste *nouvelle_liste() {
  struct liste *l = malloc(sizeof(struct liste)); // alloue la liste
  l->premier = NULL;
  l->dernier = NULL;
  l->longueur = 0;
  return l;
}


void ajouter_section_debut(struct liste *l, struct section *s) {
  if (l->longueur == 0) {
    l->dernier = s; // si vide, le premier = dernier
  }
  s->suivant = l->premier; // insère au début
  l->premier = s;
  ++l->longueur;
}


void ajouter_section_queue(struct liste *l, struct section *s) {
  s->suivant = NULL;
  if (l->longueur == 0) {
    l->premier = s; // liste vide : premier = nouvel élément
  } else {
    l->dernier->suivant = s; // sinon, on relie à l’ancien dernier
  }
  l->dernier = s;
  ++l->longueur;
}


struct section *extraire_section_debut(struct liste *l) {
  struct section *s = l->premier;
  if (s != NULL) {
    l->premier = s->suivant; // passe au suivant
    --l->longueur;
    if (l->longueur == 0) {
      l->dernier = NULL; // mise à jour si vide
    }
    s->suivant = NULL; // détache proprement
  }
  return s;
}


void detruire_liste(struct liste **l) {
  if (*l != NULL) {
    while ((*l)->longueur != 0) {
      struct section *s = extraire_section_debut(*l); // retire
      desallouer_section(&s); // libère
    }
    free(*l); // libère la structure liste
    *l = NULL;
  }
}

