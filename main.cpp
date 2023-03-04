#include <iostream>
#include <ostream>

#include "Jeu.hpp"
#include "Score.hpp" 

using namespace std;

#define SCORE_FILE "Scoreboard.txt"
#define START_MESSAGE "\n\
\t------------------------------------\n \
\t| Bienvenue aux commandes de votre |\n \
\t|         HYPERMARCHE !            |\n \
\t------------------------------------\n\n"


int main(){

    string nomJoueur;

    Jeu jeu;
    Score score;
    string restart="o";

    cout << START_MESSAGE;


    score.readScoreFromFile(SCORE_FILE) ;


    while ( restart=="o"){

        while (!jeu.hypermarche_est_vide() && (jeu.getCredits()>0)){

            int continuer=-1;

            jeu.sortir_clients_des_caisses();
            jeu.mettreClientsEnAttente();
            jeu.metttreClientsEnCaisses();

            do{   
                jeu.affiche_etats_caisses();
                jeu.affiche_budget();
                jeu.affiche_position_clients();

                continuer = jeu.actions_sur_caisse();
                cout << "\n\n\n\n\n\n" << endl;

            }while(!continuer);

            jeu.changer_caisses();
            jeu.facturation();
            jeu.affiche_devis();

            cout << endl;

        }

        if(jeu.getHypermarcheVide())
        {
            cout << "Bien joué! Vous avez gagné!" << endl;
        }else{
            cout << "Dommage. Vous avez perdu..." << endl;
        }

        cout << "Votre score est :" << jeu.getCredits() << " credits" << endl ;
        
        score.setScore(jeu.getCredits());


        // score
        cout << "Quel est votre nom ?: " ;
        getline(cin, nomJoueur);
        score.setNomJoueur(nomJoueur);
        score.getNomJoueur();
        score.writeScoreToFile(SCORE_FILE);
        score.readScoreFromFile(SCORE_FILE);
        
        //demander restart
        cout << "Voulez vous recommencer ? o[oui]/n[non] :" ;
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