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

    cout << START_MESSAGE;

    while ( restart=="o"){

        while (!Jeu.hypermarche_est_vide() && Jeu.getCredits()>0 ){

            int continuer=-1;

            Jeu.sortir_clients_des_caisses();
            Jeu.clients_vers_caisse();
            do
            {   
                Jeu.affiche_etats_caisses();
                Jeu.affiche_budget();
                Jeu.affiche_position_clients();

                continuer = Jeu.actions_sur_caisse();
                cout << "\n\n\n\n\n\n" << endl;

            }while(!continuer);

            Jeu.changer_caisses();
            Jeu.facturation();

            // if (Jeu.getCredits() <= 0){
            //     Jeu.getCredits() = 0;
            // }

        }

        cout << "Voulez vous recommencer ? o[oui]/n[non]" << endl;
        getline(cin, restart);

        if (restart=="o"){
            Jeu.reset();
        }

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