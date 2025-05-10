#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structure.h"

void clear_terminal();
void afficher_animation_attaque(const char *attaquant, const char *cible);
void afficher_animation_speciale(const char *attaquant, const char *cible, const char *type);
void afficher_menu_mode_de_jeu();
void afficher_personnages_disponibles(personnage *personnages, int taille);
void afficher_introduction();
void afficher_menu_principal();

#endif
