#include <iostream>
#include <ostream>

#include "jeu.hpp"

using namespace std;

#define START_MESSAGE "\n\
\t------------------------------------\n \
\t| Bienvenue aux commandes de votre |\n \
\t|         HYPERMARCHE !            |\n \
\t------------------------------------\n\n"


int main(){

    jeu Jeu;
    string restart="o";

    while ( restart=="o"){

        while (!Jeu.getHypermarcheVide() || Jeu.getCredits()<0 ){

            cout << START_MESSAGE;

            Jeu.affiche_etats_caisses();
            Jeu.affiche_budget();
            Jeu.affiche_position_clients();
            Jeu.actions_sur_caisse();
        }

        cout << "Voulez vous recommencer ? o[oui]/n[non]" << endl;
        getline(cin, restart);

    }



    if (Jeu.getHypermarcheVide()){
        cout << "GAGNE" << endl;
    } 
    else {
        cout << "PERDU" << endl;
    }

    cout << "Votre score est :" << Jeu.getCredits() << " credits" << endl ;



    return 0;
}