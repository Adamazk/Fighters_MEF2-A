#include "affichage.h"

// Nettoie le terminal en utilisant une séquence ANSI
void clear_terminal() {
    printf("\033[H\033[J"); // Séquence ANSI pour nettoyer le terminal
}

// Fonction pour afficher une animation d'attaque entre deux personnages
void afficher_animation_attaque(const char *attaquant, const char *cible) {
    printf("\n");
    // Première étape de l'animation : Attaquant et cible en position initiale
    printf("   ⚔️ %s attaque %s !\n", attaquant, cible);
    printf("   [ %s ]       [ %s ]\n", attaquant, cible);
    printf("      O             O\n");
    printf("     /|\\           /|\\\n");
    printf("     / \\           / \\\n");
    sleep(1); // Pause pour simuler le déroulement de l'animation

    // Deuxième étape de l'animation : L'attaquant se déplace vers la cible
    printf("\n");
    printf("   ⚔️ %s attaque %s !\n", attaquant, cible);
    printf("   [ %s ]       [ %s ]\n", attaquant, cible);
    printf("      O  -->       O\n");
    printf("     /|\\           /|\\\n");
    printf("     / \\           / \\\n");
    sleep(1);

    // Dernière étape : La cible est touchée (symbolisée par 💥)
    printf("\n");
    printf("   ⚔️ %s attaque %s !\n", attaquant, cible);
    printf("   [ %s ]       [ %s ]\n", attaquant, cible);
    printf("      O             💥\n");
    printf("     /|\\           /|\\\n");
    printf("     / \\           / \\\n");
    sleep(1);

    // Résultat de l'attaque
    printf("\n");
    printf("   %s a infligé des dégâts à %s !\n", attaquant, cible);
    printf("\n");
}

// Fonction pour afficher une animation spéciale selon le type d'attaque
void afficher_animation_speciale(const char *attaquant, const char *cible, const char *type) {
    printf("\n");
    printf("   ✨ %s utilise %s sur %s !\n", attaquant, type, cible);

    // Vérification du type d'attaque spéciale
    if (strcmp(type, "Foudre") == 0) {
        // Animation pour une attaque "Foudre"
        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      ⚡             O\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
        sleep(1);

        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      ⚡  -->       O\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
        sleep(1);

        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      ⚡             💥\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
    } else if (strcmp(type, "Tortue") == 0) {
        // Animation pour une attaque "Tortue"
        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      🐢             O\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
        sleep(1);

        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      🐢  -->       O\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
        sleep(1);

        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      🐢             🐌\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
    } else {
        // Animation pour tout autre type d'attaque spéciale
        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      ✨             O\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
        sleep(1);

        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      ✨  -->       O\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
        sleep(1);

        printf("   [ %s ]       [ %s ]\n", attaquant, cible);
        printf("      ✨             💥\n");
        printf("     /|\\           /|\\\n");
        printf("     / \\           / \\\n");
    }
    sleep(1);
    printf("\n");
}

// Affiche le menu pour choisir un mode de jeu
void afficher_menu_mode_de_jeu() {
    clear_terminal(); // Nettoie le terminal avant d'afficher le menu
    printf("=====================================\n");
    printf("         CHOIX DU MODE DE JEU        \n");
    printf("=====================================\n");
    printf("1: Mode 1v1\n"); // Mode combat 1 contre 1
    printf("2: Mode 2v2\n"); // Mode combat 2 contre 2
    printf("3: Mode 3v3\n"); // Mode combat 3 contre 3
    printf("=====================================\n");
    printf("Entrez votre choix : ");
}

// Affiche la liste des personnages disponibles avec leurs statistiques
void afficher_personnages_disponibles(personnage *personnages, int taille) {
    printf("\n=== Personnages Disponibles ===\n");
    for (int i = 0; i < taille; i++) {
        // Affiche les statistiques de chaque personnage
        printf("%d: %s (PV: %d, ATK: %d, DEF: %d, AGI: %d, VIT: %d)\n",
        i + 1, personnages[i].nom, personnages[i].pvmax, personnages[i].att, personnages[i].def, personnages[i].agi, personnages[i].vit);
    }
    printf("===============================\n");
}

// Affiche l'écran d'introduction du jeu
void afficher_introduction() {
    clear_terminal(); // Nettoie le terminal avant l'introduction
    printf("=====================================\n");
    printf("       BIENVENUE DANS CERGIOKU       \n");
    printf("=====================================\n");
    printf("Dans un monde où les ninjas protègent les terres,\n");
    printf("le pays de Cergioku est divisé en 6 clans, chacun\n");
    printf("dirigé par un maître d'un dojo unique symbolisant\n");
    printf("une force élémentaire essentielle à l'équilibre.\n");
    printf("\n");
    printf("Tous les 100 ans, le tournoi des 6 dojos détermine\n");
    printf("le ninja suprême. Préparez-vous à représenter votre\n");
    printf("dojo et à combattre pour la gloire et l'équilibre !\n");
    printf("=====================================\n");
    printf("Appuyez sur Entrée pour continuer...\n");
    getchar(); // Attend que l'utilisateur appuie sur Entrée pour continuer
}

// Affiche le menu principal du jeu
void afficher_menu_principal() {
    clear_terminal(); // Nettoie le terminal avant d'afficher le menu principal
    printf("=====================================\n");
    printf("       WELCOME TO CY FIGHTERS     \n");
    printf("=====================================\n");
    printf("  Appuyez sur Entrée pour commencer  \n");
    printf("=====================================\n");
    getchar(); // Attend que l'utilisateur appuie sur Entrée pour continuer
}
