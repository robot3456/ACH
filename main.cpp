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


    score.afficherScoresDepuisFichierTxt(SCORE_FILE) ;


    while ( restart=="o"){

        jeu.setTour(1);

        while (!jeu.hypermarcheEstVide() && (jeu.getCredits()>0)){

            bool continuer=false;


            // Demande à l'utilisateur le numéro de caisse à changer, tant que celui ci n'appuie pas sur "P"
            do{   
                
                cout << "TOUR N°" << jeu.getTour() << "\n" << endl;

                jeu.afficheDevis();

                jeu.afficheEtatsCaisses();
                jeu.afficheBudget();
                jeu.affichePositionClients();

                continuer = jeu.actionsSurCaisses();
                cout << "\n\n\n\n\n\n" << endl;

            }while(!continuer);

            jeu.changerCaisses();
            
            jeu.facturation();

            jeu.sortirClientsDesCaisses();
            jeu.mettreClientsEnAttente();
            jeu.metttreClientsEnCaisses();

            cout << endl;

            jeu.setTour(jeu.getTour() + 1);
        }

        if(jeu.getHypermarcheVide()){
            cout << "\033[1;32mBien joué! Vous avez gagné!\033[0m" << endl;
        }else{
            cout << "\033[1;31mDommage. Vous avez perdu...\033[0m" << endl;
        }

        cout << "Vous avez joue " << jeu.getTour()-1 << " tours" << endl;
        cout << "Votre score est :" << jeu.getCredits() << " credits" << endl ;
        
        score.setScore(jeu.getCredits());


        // Score

        score.demanderNomJoueur();
        score.mettreAJourScoreboard(SCORE_FILE);

        
        // Demande si le joueur veur refaire une partie
        cout << "Voulez vous recommencer ? o[oui]/n[non] :" ;
        getline(cin, restart);

        if (restart=="o"){
            jeu.reset();
            score.reset();
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