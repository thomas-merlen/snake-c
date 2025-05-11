all: Grille.o Serpent.o Main.o Liste_Section.o Liste_Mouvement.o Fonction_Jeu_1_serpent.o
	gcc Grille.o Liste_Section.o Liste_Mouvement.o Serpent.o Fonction_Jeu_1_serpent.o Main.o -lncurses -o snake
	
Main.o: Main.c Grille.h Serpent.h
	gcc -c -Wall Main.c 
	
Serpent.o: Serpent.c Serpent.h 
	gcc -c -Wall Serpent.c
	
Grille.o: Grille.c Grille.h
	gcc -c -Wall Grille.c

Liste_Section.o: Liste_Section.c Liste_Section.h
	gcc -c -Wall Liste_Section.c
	
Liste_Mouvement.o: Liste_Mouvement.c Liste_Mouvement.h
	gcc -c -Wall Liste_Mouvement.c
	
Fonction_Jeu_1_serpent.o: Fonction_Jeu_1_serpent.c Fonction_Jeu_1_serpent.h 
	gcc -c -Wall  Fonction_Jeu_1_serpent.c 


clean: rm *.o snake
