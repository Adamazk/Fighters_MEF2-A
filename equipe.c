#include "equipe.h"
#include "affichage.h"
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour créer une équipe avec un certain nombre de membres
void creer_equipe(equipe *equipe, personnage *personnages, int taille, int mode) {
    clear_terminal(); // Efface l'écran pour un affichage propre
    printf("Entrez le nom de votre équipe : ");

    fgets(equipe->nom, MAX_TEAM_NAME, stdin); // Récupère le nom de l’équipe entré par l’utilisateur
    equipe->nom[strcspn(equipe->nom, "\n")] = 0; // Supprime le retour à la ligne à la fin

    printf("Choisissez %d membres pour l'équipe %s :\n", mode, equipe->nom);
    afficher_personnages_disponibles(personnages, taille); // Affiche la liste des personnages disponibles

    int choix[3];
    for (int i = 0; i < mode; i++) {
        printf("Choix du membre %d (1-%d) : ", i + 1, taille);
        choix[i] = lire_entier_avec_validation(1, taille); // Demande à l’utilisateur de choisir un personnage
    }

    // Ajoute le premier membre choisi à l’équipe
    equipe->membre1 = personnages[choix[0] - 1];

    // Ajoute un deuxième membre si nécessaire
    if (mode >= 2) {
        equipe->membre2 = personnages[choix[1] - 1];
    }

    // Ajoute un troisième membre si nécessaire
    if (mode == 3) {
        equipe->membre3 = personnages[choix[2] - 1];
    }

    equipe->pv = pv_equipe(*equipe); // Calcule les points de vie totaux de l’équipe
}

// Affiche un message de victoire pour une équipe
void afficher_victoire(equipe *equipe) {
    printf("L'équipe %s a gagné !\n", equipe->nom);
}

// Affiche les deux équipes qui vont s’affronter
void afficher_combat(equipe *equipe1, equipe *equipe2) {
    printf("Combat entre l'équipe %s et l'équipe %s !\n", equipe1->nom, equipe2->nom);
}

// Retourne le membre le plus rapide de l’équipe
personnage* vitesse_equipe_membre(equipe *equipe) {
    personnage *resultat = &equipe->membre1; // Commence par considérer le membre1 comme le plus rapide

    // Compare avec le membre2
    if (equipe->membre2.vit > resultat->vit) {
        resultat = &equipe->membre2;
    }

    // Compare avec le membre3
    if (equipe->membre3.vit > resultat->vit) {
        resultat = &equipe->membre3;
    }

    return resultat; // Retourne le membre avec la plus grande vitesse
}



