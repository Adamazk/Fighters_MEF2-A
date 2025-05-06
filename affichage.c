#include "affichage.h"

void clear_terminal() {
    printf("\033[H\033[J"); // Séquence ANSI pour nettoyer le terminal
}

void afficher_animation_attaque(const char *attaquant, const char *cible) {
    printf("\n");
    printf("   ⚔️ %s attaque %s !\n", attaquant, cible);
    printf("   [ %s ]       [ %s ]\n", attaquant, cible);
    printf("      O             O\n");
    printf("     /|\\           /|\\\n");
    printf("     / \\           / \\\n");
    sleep(1);

    printf("\n");
    printf("   ⚔️ %s attaque %s !\n", attaquant, cible);
    printf("   [ %s ]       [ %s ]\n", attaquant, cible);
    printf("      O  -->       O\n");
    printf("     /|\\           /|\\\n");
    printf("     / \\           / \\\n");
    sleep(1);

    printf("\n");
    printf("   ⚔️ %s attaque %s !\n", attaquant, cible);
    printf("   [ %s ]       [ %s ]\n", attaquant, cible);
    printf("      O             💥\n");
    printf("     /|\\           /|\\\n");
    printf("     / \\           / \\\n");
    sleep(1);

    printf("\n");
    printf("   %s a infligé des dégâts à %s !\n", attaquant, cible);
    printf("\n");
}

void afficher_animation_speciale(const char *attaquant, const char *cible, const char *type) {
    printf("\n");
    printf("   ✨ %s utilise %s sur %s !\n", attaquant, type, cible);
    if (strcmp(type, "Foudre") == 0) {
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

void afficher_menu_mode_de_jeu() {
    clear_terminal();
    printf("=====================================\n");
    printf("         CHOIX DU MODE DE JEU        \n");
    printf("=====================================\n");
    printf("1: Mode 1v1\n");
    printf("2: Mode 2v2\n");
    printf("3: Mode 3v3\n");
    printf("=====================================\n");
    printf("Entrez votre choix : ");
}

void afficher_personnages_disponibles(personnage *personnages, int taille) {
    printf("\n=== Personnages Disponibles ===\n");
    for (int i = 0; i < taille; i++) {
        printf("%d: %s (PV: %d, ATK: %d, DEF: %d, AGI: %d, VIT: %d)\n",
        i + 1, personnages[i].nom, personnages[i].pvmax, personnages[i].att, personnages[i].def, personnages[i].agi, personnages[i].vit);
    }
    printf("===============================\n");
}

void afficher_introduction() {
    clear_terminal();
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
    getchar(); // Attendre que l'utilisateur appuie sur Entrée
}

void afficher_menu_principal() {
    clear_terminal();
    printf("=====================================\n");
    printf("       WELCOME TO CY FIGHTERS     \n");
    printf("=====================================\n");
    printf("  Appuyez sur Entrée pour commencer  \n");
    printf("=====================================\n");
    getchar(); // Attendre que l'utilisateur appuie sur Entrée
}
