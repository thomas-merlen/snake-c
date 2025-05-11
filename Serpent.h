#ifndef _SERPENT_H
#define _SERPENT_H
#include"Liste_Section.h"
#include"Grille.h"
#include"Liste_Mouvement.h"

struct serpent{
	struct coord tete;
	struct liste *corps;
	struct liste_mvt *mvt;
};



struct serpent * creer_serpent(int x,int y);
	

void Grille_remplir_serpent(struct grille*G ,struct serpent*S);

#endif
