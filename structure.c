#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Pour la fonction sleep
#include <limits.h> // Pour INT_MAX

// Fonction qui calcule les points de vie totaux d'une équipe
int pv_equipe(equipe equipe1) {
    // Additionne les PV (points de vie) des trois membres de l’équipe
    return equipe1.membre1.pv + equipe1.membre2.pv + equipe1.membre3.pv;
}
