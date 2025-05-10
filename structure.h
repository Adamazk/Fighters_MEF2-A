#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Pour la fonction sleep
#include <limits.h> // Pour INT_MAX

#define MAX_TEAM_NAME 50

typedef struct {
    char nom[50];
    char description[100];
    int tours_actif;
    int nb_recharge;
} technique_speciale;

typedef struct {
    char nom[50];
    int pv;
    int pvmax;
    int att;
    int def;
    int agi;
    int vit;
    technique_speciale spe1;
    technique_speciale spe2;
    technique_speciale spe3;
} personnage;

typedef struct {
    char nom[50];
    personnage membre1;
    personnage membre2;
    personnage membre3;
    int pv;
} equipe;

int pv_equipe(equipe equipe1);

#endif /* STRUCTURE_H */
