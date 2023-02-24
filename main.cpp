#include <iostream>

#include "jeu.hpp"

using namespace std;

#define START_MESSAGE "\n\
\t------------------------------------\n \
\t| Bienvenue aux commandes de votre |\n \
\t|         HYPERMARCHE !            |\n \
\t------------------------------------\n\n"


int main(){

    jeu Jeu;

    cout << START_MESSAGE;

    Jeu.affiche_etats_caisses();

    Jeu.affiche_budget();

    return 0;
}