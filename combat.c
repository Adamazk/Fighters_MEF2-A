#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Pour la fonction sleep
#include <limits.h> // Pour INT_MAX

// Fonction pour lire un entier depuis l'entrée standard avec validation
int lire_entier() {
    char buffer[256];
    char *endptr;

    // Lire la ligne entrée par l'utilisateur
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    // Supprimer le retour à la ligne à la fin
    buffer[strcspn(buffer, "\n")] = 0;

    // Vérifier si la chaîne est vide
    if (strlen(buffer) == 0) {
        return -1;
    }

    // Convertir la chaîne en nombre entier
    long val = strtol(buffer, &endptr, 10);

    // Vérifier si la conversion a réussi
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return -1;
    }

    return (int)val;
}

// Fonction qui lit un entier entre min et max, avec messages de validation
int lire_entier_avec_validation(int min, int max) {
    int valeur;
    while (1) {
        valeur = lire_entier();
        if (valeur >= min && valeur <= max) {
            return valeur;
        }
        printf("Veuillez entrer un nombre valide entre %d et %d : ", min, max);
    }
}

// Fonction qui applique une attaque d’un personnage à un autre
void attaque(personnage *attaquant, personnage *cible) {
    // Vérifie si la cible est déjà morte
    if (cible->pv <= 0) {
        printf("%s est déjà mort(e) et ne peut pas être attaqué(e) !\n", cible->nom);
        return;
    }

    // Animation d'attaque (visuel)
    afficher_animation_attaque(attaquant->nom, cible->nom);

    // Calcul des dégâts infligés
    int degats = (attaquant->att / cible->def) + (attaquant->agi / 2);

    // Sauvegarde des PV avant l'attaque pour l'affichage
    int pv_avant = cible->pv;

    // Réduction des PV de la cible
    cible->pv -= degats;
    if (cible->pv < 0){
        cible->pv = 0;
    }

    // Affichage des effets de l'attaque
    printf("💔 %s attaque %s et inflige %d dégâts !\n", attaquant->nom, cible->nom, degats);
    printf("PV de %s : %d --> %d\n", cible->nom, pv_avant, cible->pv);

    // Affichage de la mort si PV atteint 0
    if (cible->pv == 0) {
        printf("☠️ %s est mort(e) !\n", cible->nom);
    }
}

// Fonction qui applique une technique spéciale à une cible
void appliquer_special(technique_speciale *special, personnage *attaquant, personnage *cible) {
    // Chaque effet est associé à une animation et modifie une stat

    if (strcmp(special->nom, "Frappe du Néant") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Néant");
        int att_avant = cible->att;
        cible->att -= cible->att * 25 / 100;
        printf("📉 L'attaque de %s a été réduite : %d --> %d\n", cible->nom, att_avant, cible->att);

    } else if (strcmp(special->nom, "Poids de l'Ombre") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Ombre");
        int vit_avant = cible->vit;
        cible->vit -= cible->vit * 30 / 100;
        printf("🐢 La vitesse de %s a été réduite : %d --> %d\n", cible->nom, vit_avant, cible->vit);

    } else if (strcmp(special->nom, "Vitesse de l'Ombre") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Ombre");
        int vit_avant = attaquant->vit;
        attaquant->vit += attaquant->vit * 30 / 100;
        printf("⚡ La vitesse de %s a été augmentée : %d --> %d\n", attaquant->nom, vit_avant, attaquant->vit);

    // ⚡ Attaques d’Adamar
    } else if (strcmp(special->nom, "Foudre Perforante") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Foudre");
        int agi_avant = cible->agi;
        cible->agi -= cible->agi * 20 / 100;
        printf("📉 L'agilité de %s a été réduite : %d --> %d\n", cible->nom, agi_avant, cible->agi);

    } else if (strcmp(special->nom, "Courant Déstabilisant") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Tortue");
        int vit_avant = cible->vit;
        cible->vit -= cible->vit * 25 / 100;
        printf("🐢 La vitesse de %s a été réduite : %d --> %d\n", cible->nom, vit_avant, cible->vit);

    } else if (strcmp(special->nom, "Éclair Foudroyant") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Foudre");
        int att_avant = attaquant->att;
        attaquant->att += attaquant->att * 25 / 100;
        printf("⚡ L'attaque de %s a été augmentée : %d --> %d\n", attaquant->nom, att_avant, attaquant->att);

    // 🌱 Attaques de Yassel
    } else if (strcmp(special->nom, "Morsure des Racines") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Racines");
        int vit_avant = cible->vit;
        cible->vit -= cible->vit * 35 / 100;
        printf("🌱 La vitesse de %s a été réduite : %d --> %d\n", cible->nom, vit_avant, cible->vit);

    } else if (strcmp(special->nom, "Souffle de la Terre") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Terre");
        int att_avant = cible->att;
        cible->att -= cible->att * 20 / 100;
        printf("📉 L'attaque de %s a été réduite : %d --> %d\n", cible->nom, att_avant, cible->att);

    } else if (strcmp(special->nom, "Bénédiction du Bambou") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Bambou");
        int def_avant = attaquant->def;
        attaquant->def += attaquant->def * 30 / 100;
        printf("🛡️ La défense de %s a été augmentée : %d --> %d\n", attaquant->nom, def_avant, attaquant->def);

    // 🪨 Attaques de Raynor
    } else if (strcmp(special->nom, "Choc Sismique") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Sismique");
        int def_avant = cible->def;
        cible->def -= cible->def * 30 / 100;
        printf("📉 La défense de %s a été réduite : %d --> %d\n", cible->nom, def_avant, cible->def);

    } else if (strcmp(special->nom, "Roc Déstabilisant") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Roc");
        int agi_avant = cible->agi;
        cible->agi -= cible->agi * 25 / 100;
        printf("📉 L'agilité de %s a été réduite : %d --> %d\n", cible->nom, agi_avant, cible->agi);

    } else if (strcmp(special->nom, "Bouclier de Terre") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Bouclier");
        int def_avant = attaquant->def;
        attaquant->def += attaquant->def * 40 / 100;
        printf("🛡️ La défense de %s a été augmentée : %d --> %d\n", attaquant->nom, def_avant, attaquant->def);

    // 🌀 Attaques de Tymion
    } else if (strcmp(special->nom, "Choc Distorisonnel") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Distorsion");
        int att_avant = cible->att;
        cible->att -= cible->att * 20 / 100;
        printf("📉 L'attaque de %s a été réduite : %d --> %d\n", cible->nom, att_avant, cible->att);

    } else if (strcmp(special->nom, "Vortex Magnétique") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Vortex");
        int vit_avant = cible->vit;
        cible->vit -= cible->vit * 30 / 100;
        printf("🐢 La vitesse de %s a été réduite : %d --> %d\n", cible->nom, vit_avant, cible->vit);

    } else if (strcmp(special->nom, "Éclat Astral") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Astral");
        int vit_avant = attaquant->vit;
        attaquant->vit += attaquant->vit * 30 / 100;
        printf("⚡ La vitesse de %s a été augmentée : %d --> %d\n", attaquant->nom, vit_avant, attaquant->vit);

    // 🔥 Attaques de Joaka
    } else if (strcmp(special->nom, "Brûlure Mentale") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Brûlure");
        int agi_avant = cible->agi;
        cible->agi -= cible->agi * 25 / 100;
        printf("📉 L'agilité de %s a été réduite : %d --> %d\n", cible->nom, agi_avant, cible->agi);

    } else if (strcmp(special->nom, "Explosion Incandescente") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Explosion");
        int def_avant = cible->def;
        cible->def -= cible->def * 20 / 100;
        printf("📉 La défense de %s a été réduite : %d --> %d\n", cible->nom, def_avant, cible->def);

    } else if (strcmp(special->nom, "Flamme Enflammée") == 0) {
        afficher_animation_speciale(attaquant->nom, cible->nom, "Flamme");
        int att_avant = attaquant->att;
        attaquant->att += attaquant->att * 35 / 100;
        printf("🔥 L'attaque de %s a été augmentée : %d --> %d\n", attaquant->nom, att_avant, attaquant->att);
    }
}


int combat(equipe equipe1, equipe equipe2, int mode) {
    int cible = -1, choix = -1, tour = 1;
    personnage *attaquant = NULL, *cible_personnage = NULL;

    // Calcul initial des points de vie totaux pour chaque équipe
    equipe1.pv = pv_equipe(equipe1);
    equipe2.pv = pv_equipe(equipe2);

    while (equipe1.pv > 0 && equipe2.pv > 0) {
        clear_terminal(); // Nettoyage de l'écran entre chaque tour
        printf("\n--- Tour %d ---\n", tour);
        printf("PV Équipe %s: %d | PV Équipe %s: %d\n", equipe1.nom, equipe1.pv, equipe2.nom, equipe2.pv);

        // Affichage des PV des membres de l'équipe 1 selon le mode (1v1, 2v2, 3v3)
        printf("Équipe %s:\n", equipe1.nom);
        if (mode >= 1 && equipe1.membre1.pv > 0) {
            printf("  %s: %d/%d PV\n", equipe1.membre1.nom, equipe1.membre1.pv, equipe1.membre1.pvmax);
        }
        if (mode >= 2 && equipe1.membre2.pv > 0) {
            printf("  %s: %d/%d PV\n", equipe1.membre2.nom, equipe1.membre2.pv, equipe1.membre2.pvmax);
        }
        if (mode == 3 && equipe1.membre3.pv > 0) {
            printf("  %s: %d/%d PV\n", equipe1.membre3.nom, equipe1.membre3.pv, equipe1.membre3.pvmax);
        }

        // Affichage des PV des membres de l'équipe 2
        printf("Équipe %s:\n", equipe2.nom);
        if (mode >= 1 && equipe2.membre1.pv > 0) {
            printf("  %s: %d/%d PV\n", equipe2.membre1.nom, equipe2.membre1.pv, equipe2.membre1.pvmax);
        }
        if (mode >= 2 && equipe2.membre2.pv > 0) {
            printf("  %s: %d/%d PV\n", equipe2.membre2.nom, equipe2.membre2.pv, equipe2.membre2.pvmax);
        }
        if (mode == 3 && equipe2.membre3.pv > 0) {
            printf("  %s: %d/%d PV\n", equipe2.membre3.nom, equipe2.membre3.pv, equipe2.membre3.pvmax);
        }

        // Détermination de l'équipe qui joue selon le tour
        if (tour % 2) {
            printf("Au tour de l'équipe %s\n", equipe1.nom);
            attaquant = vitesse_equipe_membre(&equipe1); // Choix du plus rapide vivant
        } else {
            printf("Au tour de l'équipe %s\n", equipe2.nom);
            attaquant = vitesse_equipe_membre(&equipe2);
        }

        // Choix d'action
        printf("Que voulez-vous faire ?\n");
        printf("1: Attaquer\n");
        printf("2: %s - %s\n", attaquant->spe1.nom, attaquant->spe1.description);
        printf("3: %s - %s\n", attaquant->spe2.nom, attaquant->spe2.description);
        printf("4: %s - %s\n", attaquant->spe3.nom, attaquant->spe3.description);

        choix = lire_entier_avec_validation(1, 4);

        if (choix == 1) {
            // Choix de la cible en fonction du tour
            printf("Quelle cible ?\n");
            if (tour % 2) {
                if (mode >= 1 && equipe2.membre1.pv > 0){ 
                    printf("1: %s\n", equipe2.membre1.nom);
                }
                if (mode >= 2 && equipe2.membre2.pv > 0){
                    printf("2: %s\n", equipe2.membre2.nom);
                }
                if (mode == 3 && equipe2.membre3.pv > 0){
                    printf("3: %s\n", equipe2.membre3.nom);
                }
            } else {
                if (mode >= 1 && equipe1.membre1.pv > 0){
                    printf("1: %s\n", equipe1.membre1.nom);
                }
                if (mode >= 2 && equipe1.membre2.pv > 0){
                    printf("2: %s\n", equipe1.membre2.nom);
                }
                if (mode == 3 && equipe1.membre3.pv > 0){
                    printf("3: %s\n", equipe1.membre3.nom);
                }
            }

            cible = lire_entier_avec_validation(1, mode); // Lecture choix cible

            // Attribution du pointeur vers le personnage cible
            if (tour % 2) {
                if (cible == 1) {
                    cible_personnage = &equipe2.membre1;
                } else if (cible == 2) {
                    cible_personnage = &equipe2.membre2;
                } else {
                    cible_personnage = &equipe2.membre3;
                }
            } else {
                if (cible == 1) {
                    cible_personnage = &equipe1.membre1;
                } else if (cible == 2) {
                    cible_personnage = &equipe1.membre2;
                } else {
                    cible_personnage = &equipe1.membre3;
                }
            }

            attaque(attaquant, cible_personnage); // Action d'attaque
        } else if (choix == 2) {
            appliquer_special(&attaquant->spe1, attaquant, cible_personnage); // Spéciale 1
        } else if (choix == 3) {
            appliquer_special(&attaquant->spe2, attaquant, cible_personnage); // Spéciale 2
        } else if (choix == 4) {
            appliquer_special(&attaquant->spe3, attaquant, cible_personnage); // Spéciale 3
        }

        // Mise à jour des PV totaux
        equipe1.pv = pv_equipe(equipe1);
        equipe2.pv = pv_equipe(equipe2);
        tour++; // Changement de tour
    }

    clear_terminal();
    // Affichage du gagnant
    if (equipe1.pv <= 0) {
        printf("L'équipe %s a gagné !\n", equipe2.nom);
        return 2;
    } else {
        printf("L'équipe %s a gagné !\n", equipe1.nom);
        return 1;
    }
}


// Fonction de combat en 1 contre 1
int combat_1v1(personnage *perso1, personnage *perso2) {
    int tour = 1;

    // Boucle principale du combat
    while (perso1->pv > 0 && perso2->pv > 0) {
        clear_terminal(); // Nettoyer l'écran à chaque tour
        printf("\n--- Tour %d ---\n", tour);
        printf("%s: %d/%d PV | %s: %d/%d PV\n", perso1->nom, perso1->pv, perso1->pvmax, perso2->nom, perso2->pv, perso2->pvmax); 

        personnage *attaquant;
        personnage *cible;

        // Alterner les tours entre les deux personnages
        if (tour % 2) {
            attaquant = perso1;
            cible = perso2;
        } else {
            attaquant = perso2;
            cible = perso1;
        }

        // Affichage des actions disponibles
        printf("Au tour de %s\n", attaquant->nom);
        printf("Que voulez-vous faire ?\n");
        printf("1: Attaquer\n");
        printf("2: %s - %s\n", attaquant->spe1.nom, attaquant->spe1.description);
        printf("3: %s - %s\n", attaquant->spe2.nom, attaquant->spe2.description);
        printf("4: %s - %s\n", attaquant->spe3.nom, attaquant->spe3.description);

        // Lecture du choix du joueur
        int choix = lire_entier_avec_validation(1, 4);

        // Exécuter l'action choisie
        if (choix == 1) {
            attaque(attaquant, cible);
        } else if (choix == 2) {
            appliquer_special(&attaquant->spe1, attaquant, cible);
        } else if (choix == 3) {
            appliquer_special(&attaquant->spe2, attaquant, cible);
        } else if (choix == 4) {
            appliquer_special(&attaquant->spe3, attaquant, cible);
        }

        tour++;
    }

    // Fin du combat : affichage du gagnant
    clear_terminal();
    if (perso1->pv <= 0) {
        printf("%s a gagné !\n", perso2->nom);
        return 2;
    } else {
        printf("%s a gagné !\n", perso1->nom);
        return 1;
    }
}

// Fonction de combat en 2 contre 2
int combat_2v2(equipe equipe1, equipe equipe2) {
    // Désactiver le troisième membre des équipes pour un combat 2v2
    equipe1.membre3.pv = 0;
    equipe2.membre3.pv = 0;

    int cible, choix, tour = 1;
    personnage *attaquant, *cible_personnage;

    // Initialiser les PV totaux des équipes
    equipe1.pv = equipe1.membre1.pv + equipe1.membre2.pv;
    equipe2.pv = equipe2.membre1.pv + equipe2.membre2.pv;

    // Boucle principale du combat
    while (equipe1.pv > 0 && equipe2.pv > 0) {
        clear_terminal(); // Nettoyer l’écran
        printf("\n--- Tour %d ---\n", tour);
        printf("PV Équipe %s: %d | PV Équipe %s: %d\n", equipe1.nom, equipe1.pv, equipe2.nom, equipe2.pv);

        // Affichage des membres et leurs PV
        printf("Équipe %s:\n", equipe1.nom);
        if (equipe1.membre1.pv > 0){
            printf("  %s: %d/%d PV\n", equipe1.membre1.nom, equipe1.membre1.pv, equipe1.membre1.pvmax);
        } 
        if (equipe1.membre2.pv > 0){
            printf("  %s: %d/%d PV\n", equipe1.membre2.nom, equipe1.membre2.pv, equipe1.membre2.pvmax);
        } 
        printf("Équipe %s:\n", equipe2.nom);
        if (equipe2.membre1.pv > 0){
            printf("  %s: %d/%d PV\n", equipe2.membre1.nom, equipe2.membre1.pv, equipe2.membre1.pvmax);
        } 
        if (equipe2.membre2.pv > 0){
            printf("  %s: %d/%d PV\n", equipe2.membre2.nom, equipe2.membre2.pv, equipe2.membre2.pvmax);
        } 

        // Choisir l’équipe qui joue ce tour
        if (tour % 2) {
            printf("Au tour de l'équipe %s\n", equipe1.nom);
            attaquant = vitesse_equipe_membre(&equipe1); // Choix du plus rapide
            while (attaquant->pv <= 0) { // Sauter les personnages morts
                if (attaquant == &equipe1.membre1) {
                    attaquant = &equipe1.membre2;
                } else {
                    attaquant = &equipe1.membre1;
                }
            }
        } else {
            printf("Au tour de l'équipe %s\n", equipe2.nom);
            attaquant = vitesse_equipe_membre(&equipe2);
            while (attaquant->pv <= 0) {
                if (attaquant == &equipe2.membre1) {
                    attaquant = &equipe2.membre2;
                } else {
                    attaquant = &equipe2.membre1;
                }
            }
        }

        // Choix d'action par le joueur
        printf("Que voulez-vous faire ?\n");
        printf("1: Attaquer\n");
        printf("2: %s - %s\n", attaquant->spe1.nom, attaquant->spe1.description);
        printf("3: %s - %s\n", attaquant->spe2.nom, attaquant->spe2.description);
        printf("4: %s - %s\n", attaquant->spe3.nom, attaquant->spe3.description);
        choix = lire_entier_avec_validation(1, 4);

        // Sélection et exécution de l'action choisie
        if (choix == 1) {
            printf("Quelle cible ?\n");
            if (tour % 2) {
                if (equipe2.membre1.pv > 0){
                    printf("1: %s\n", equipe2.membre1.nom);
                } 
                if (equipe2.membre2.pv > 0){
                    printf("2: %s\n", equipe2.membre2.nom);
                } 
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe2.membre1 : &equipe2.membre2;
            } else {
                if (equipe1.membre1.pv > 0){
                    printf("1: %s\n", equipe1.membre1.nom);
                }
                if (equipe1.membre2.pv > 0){
                    printf("2: %s\n", equipe1.membre2.nom);
                } 
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe1.membre1 : &equipe1.membre2;
            }
            attaque(attaquant, cible_personnage);
        } else if (choix == 2) {
            // Spéciale 1
            printf("Choisissez une cible:\n");
            if (tour % 2) {
                if (equipe2.membre1.pv > 0) printf("1: %s\n", equipe2.membre1.nom);
                if (equipe2.membre2.pv > 0) printf("2: %s\n", equipe2.membre2.nom);
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe2.membre1 : &equipe2.membre2;
            } else {
                if (equipe1.membre1.pv > 0) printf("1: %s\n", equipe1.membre1.nom);
                if (equipe1.membre2.pv > 0) printf("2: %s\n", equipe1.membre2.nom);
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe1.membre1 : &equipe1.membre2;
            }
            appliquer_special(&attaquant->spe1, attaquant, cible_personnage);
        } else if (choix == 3) {
            // Spéciale 2
            printf("Choisissez une cible:\n");
            if (tour % 2) {
                if (equipe2.membre1.pv > 0) printf("1: %s\n", equipe2.membre1.nom);
                if (equipe2.membre2.pv > 0) printf("2: %s\n", equipe2.membre2.nom);
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe2.membre1 : &equipe2.membre2;
            } else {
                if (equipe1.membre1.pv > 0) printf("1: %s\n", equipe1.membre1.nom);
                if (equipe1.membre2.pv > 0) printf("2: %s\n", equipe1.membre2.nom);
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe1.membre1 : &equipe1.membre2;
            }
            appliquer_special(&attaquant->spe2, attaquant, cible_personnage);
        } else {
            // Spéciale 3
            printf("Choisissez une cible:\n");
            if (tour % 2) {
                if (equipe2.membre1.pv > 0) printf("1: %s\n", equipe2.membre1.nom);
                if (equipe2.membre2.pv > 0) printf("2: %s\n", equipe2.membre2.nom);
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe2.membre1 : &equipe2.membre2;
            } else {
                if (equipe1.membre1.pv > 0) printf("1: %s\n", equipe1.membre1.nom);
                if (equipe1.membre2.pv > 0) printf("2: %s\n", equipe1.membre2.nom);
                cible = lire_entier_avec_validation(1, 2);
                cible_personnage = (cible == 1) ? &equipe1.membre1 : &equipe1.membre2;
            }
            appliquer_special(&attaquant->spe3, attaquant, cible_personnage);
        }

        // Mise à jour des PV totaux après chaque action
        equipe1.pv = equipe1.membre1.pv + equipe1.membre2.pv;
        equipe2.pv = equipe2.membre1.pv + equipe2.membre2.pv;
        tour++;
    }

    // Affichage du résultat final
    clear_terminal();
    if (equipe1.pv <= 0) {
        printf("L'équipe %s a gagné !\n", equipe2.nom);
        return 2;
    } else {
        printf("L'équipe %s a gagné !\n", equipe1.nom);
        return 1;
    }
}
