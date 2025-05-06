#ifndef COMBAT_H
#define COMBAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

int lire_entier();

// Fonctions d'animation
void clear_terminal();
void afficher_animation_attaque(const char* attaquant, const char* cible);
void afficher_animation_speciale(const char* attaquant, const char* cible, const char* type);

// Fonctions d'équipe
int pv_equipe(equipe e);
personnage* vitesse_equipe_membre(equipe* e);

// Fonctions de combat
void attaque(personnage* attaquant, personnage* cible);
void appliquer_special(technique_speciale* special, personnage* attaquant, personnage* cible);
int combat(equipe equipe1, equipe equipe2, int mode);
int combat_1v1(personnage* perso1, personnage* perso2);
int combat_2v2(equipe equipe1, equipe equipe2);

#endif /* COMBAT_H */
