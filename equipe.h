ifndef EQUIPE_H
#define EQUIPE_H


// Fonctions de gestion d'équipe
int pv_equipe(equipe equipe1);
personnage* vitesse_equipe_membre(equipe *equipe);
void creer_equipe(equipe *equipe, personnage *personnages, int taille, int mode);
void afficher_personnages_disponibles(personnage *personnages, int taille);

#endif /* EQUIPE_H */
