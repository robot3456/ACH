#include <iostream>
#include <ostream>

#include "Jeu.hpp"
#include "Score.hpp" 

using namespace std;

#define START_MESSAGE "\n\
\t------------------------------------\n \
\t| Bienvenue aux commandes de votre |\n \
\t|         HYPERMARCHE !            |\n \
\t------------------------------------\n\n"


int main(){

    Jeu jeu;
    string restart="o";

    cout << START_MESSAGE;

    while ( restart=="o"){

        while (!jeu.hypermarche_est_vide() && jeu.getCredits()>0 ){

            int continuer=-1;

            jeu.sortir_clients_des_caisses();
            jeu.clients_vers_caisse();
            
            do{   
                jeu.affiche_etats_caisses();
                jeu.affiche_budget();
                jeu.affiche_position_clients();

                continuer = jeu.actions_sur_caisse();
                cout << "\n\n\n\n\n\n" << endl;

            }while(!continuer);

            jeu.changer_caisses();
            jeu.facturation();

        }

        if(jeu.getHypermarcheVide()){
            cout << "GAGNE" << endl;
        }
        else{
            cout << "PERDU" << endl;
        }
        cout << "Votre score est :" << jeu.getCredits() << " credits" << endl ;





        cout << "Voulez vous recommencer ? o[oui]/n[non]" << endl;
        getline(cin, restart);

        if (restart=="o"){
            jeu.reset();
        }
    
    }

    cout << "\n\
            \t------------------------------------\n \
            \t|        Merci d'avoir joué !      |\n \
            \t|                                  |\n \
            \t|      A bientot aux commandes     |\n \
            \t|      de votre Hypermarche ;)     |\n \
            \t------------------------------------\n\n" << endl ;

    return 0;
}