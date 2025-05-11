#ifndef _LISTE_MOUVEMENT_H
#define _LISTE_MOUVEMENT_H
#include"Grille.h"

struct section_mvt{
	struct coord coord;
	int direction;
	struct section_mvt *suivant;
};

struct liste_mvt{
    struct section_mvt *premier;
    struct section_mvt *dernier;
    int longueur;
};

struct section_mvt *creer_section_mvt(struct coord coord,int direction);

void desallouer_section_mvt(struct section_mvt *s);

struct liste_mvt *nouvelle_liste_mvt();

void ajouter_section_mvt_debut(struct liste_mvt *l, struct section_mvt *s);

struct section_mvt *extraire_section_mvt_debut(struct liste_mvt *l);

void detruire_liste_mvt (struct liste_mvt *l);

void ajouter_section_mvt_queue(struct liste_mvt *l,struct section_mvt *s);

#endif
