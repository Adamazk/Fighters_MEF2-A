#include "structures.h"

int pv_equipe(equipe equipe1) {
    return equipe1.membre1.pv + equipe1.membre2.pv + equipe1.membre3.pv;
}

personnage* vitesse_equipe_membre(equipe *equipe) {
    personnage *resultat = &equipe->membre1;
    if (equipe->membre2.vit > resultat->vit){
        resultat = &equipe->membre2;
    }
    if (equipe->membre3.vit > resultat->vit){
        resultat = &equipe->membre3;
    }
    return resultat;
}
