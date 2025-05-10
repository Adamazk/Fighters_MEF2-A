#include "equipe.h"
#include "affichage.h"
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void creer_equipe(equipe *equipe, personnage *personnages, int taille, int mode) {
    clear_terminal();
    printf("Entrez le nom de votre équipe : ");

    fgets(equipe->nom, MAX_TEAM_NAME, stdin);
    equipe->nom[strcspn(equipe->nom, "\n")] = 0;

    printf("Choisissez %d membres pour l'équipe %s :\n", mode, equipe->nom);
    afficher_personnages_disponibles(personnages, taille);

    int choix[3];
    for (int i = 0; i < mode; i++) {
        printf("Choix du membre %d (1-%d) : ", i + 1, taille);
        choix[i] = lire_entier_avec_validation(1, taille);
    }

    equipe->membre1 = personnages[choix[0] - 1];

    if (mode >= 2) {
        equipe->membre2 = personnages[choix[1] - 1];
    }

    if (mode == 3) {
        equipe->membre3 = personnages[choix[2] - 1];
    }

    equipe->pv = pv_equipe(*equipe);
}

void afficher_victoire(equipe *equipe) {
    printf("L'équipe %s a gagné !\n", equipe->nom);
}

void afficher_combat(equipe *equipe1, equipe *equipe2) {
    printf("Combat entre l'équipe %s et l'équipe %s !\n", equipe1->nom, equipe2->nom);
}

personnage* vitesse_equipe_membre(equipe *equipe) {
    personnage *resultat = &equipe->membre1;
    if (equipe->membre2.vit > resultat->vit) {
        resultat = &equipe->membre2;
    }
    if (equipe->membre3.vit > resultat->vit) {
        resultat = &equipe->membre3;
    }
    return resultat;
}


