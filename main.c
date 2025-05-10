#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Pour la fonction sleep
#include <limits.h> // Pour INT_MAX
#include "structure.h"
#include "affichage.h"
#include "combat.h"
#include "equipe.h"

int main() {
    afficher_introduction(); // Afficher l'introduction narrative
    afficher_menu_principal(); // Afficher le menu principal
    clear_terminal(); // Nettoyer le terminal après le menu

    personnage personnages[] = {
        {"Shad'Kar", 90, 90, 80, 60, 70, 90, {"Frappe du Néant", "Réduit l'attaque de 25% pendant 5 tours", 0, 0}, {"Poids de l'Ombre", "Réduit la vitesse de 30% pendant 7 tours", 0, 0}, {"Vitesse de l’Ombre", "Augmente la vitesse de 30% pendant 5 tours", 0, 0}},
        {"Adamar", 70, 70, 90, 50, 80, 100, {"Foudre Perforante", "Réduit l'agilité de 20% pendant 5 tours", 0, 0}, {"Courant Déstabilisant", "Réduit la vitesse de 25% pendant 6 tours", 0, 0}, {"Éclair Foudroyant", "Augmente l'attaque de 25% pendant 6 tours", 0, 0}},
        {"Yassel", 80, 80, 70, 70, 60, 80, {"Morsure des Racines", "Réduit la vitesse de 35% pendant 6 tours", 0, 0}, {"Souffle de la Terre", "Réduit l'attaque de 20% pendant 5 tours", 0, 0}, {"Bénédiction du Bambou", "Augmente la défense de 30% pendant 7 tours", 0, 0}},
        {"Raynor", 100, 100, 60, 80, 50, 70, {"Choc Sismique", "Réduit la défense de 30% pendant 6 tours", 0, 0}, {"Roc Déstabilisant", "Réduit l'agilité de 25% pendant 7 tours", 0, 0}, {"Bouclier de Terre", "Augmente la défense de 40% pendant 8 tours", 0, 0}},
        {"Tymion", 60, 60, 85, 55, 75, 110, {"Choc Distorisonnel", "Réduit l'attaque de 20% pendant 5 tours", 0, 0}, {"Vortex Magnétique", "Réduit la vitesse de 30% pendant 6 tours", 0, 0}, {"Éclat Astral", "Augmente la vitesse de 30% pendant 6 tours", 0, 0}},
        {"Joaka", 75, 75, 95, 65, 85, 95, {"Brûlure Mentale", "Réduit l'agilité de 25% pendant 5 tours", 0, 0}, {"Explosion Incandescente", "Réduit la défense de 20% pendant 7 tours", 0, 0}, {"Flamme Enflammée", "Augmente l'attaque de 35% pendant 6 tours", 0, 0}}
    };

    int taille_personnages = sizeof(personnages) / sizeof(personnages[0]);

    afficher_menu_mode_de_jeu();
    int mode;
    mode = lire_entier_avec_validation(1, 3);

    if (mode == 1) {
        printf("Choisissez deux personnages pour le mode 1v1 :\n");
        afficher_personnages_disponibles(personnages, taille_personnages);

        int choix1, choix2;
        printf("Choix du personnage 1 (1-%d) : ", taille_personnages);
        choix1 = lire_entier_avec_validation(1, taille_personnages);

        printf("Choix du personnage 2 (1-%d) : ", taille_personnages);
        choix2 = lire_entier_avec_validation(1, taille_personnages);
        while (choix2 == choix1) {
            printf("Choix invalide. Réessayez : ");
            choix2 = lire_entier_avec_validation(1, taille_personnages);
        }

        personnage *perso1 = &personnages[choix1 - 1];
        personnage *perso2 = &personnages[choix2 - 1];

        clear_terminal(); // Nettoyer le terminal avant le début du combat
        printf("\nDébut du combat 1v1 entre %s et %s !\n", perso1->nom, perso2->nom);
        combat_1v1(perso1, perso2);
    } else {
        equipe equipe1, equipe2;

        printf("Création de l'équipe 1 :\n");
        creer_equipe(&equipe1, personnages, taille_personnages, mode);

        printf("\nCréation de l'équipe 2 :\n");
        creer_equipe(&equipe2, personnages, taille_personnages, mode);

        clear_terminal(); // Nettoyer le terminal avant le début du combat
        if (mode == 2) {
            printf("\nDébut du combat 2v2 entre l'équipe %s et l'équipe %s !\n", equipe1.nom, equipe2.nom);
            combat_2v2(equipe1, equipe2);
        } else {
            printf("\nDébut du combat 3v3 entre l'équipe %s et l'équipe %s !\n", equipe1.nom, equipe2.nom);
            combat(equipe1, equipe2, 3);
        }
    }

    return 0;
    
}
