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

        int tour=1;

        while (!jeu.hypermarcheEstVide() && (jeu.getCredits()>0)){

            int continuer=-1;

            do{   
                
                cout << "TOUR N°" << tour <<endl;

                jeu.afficheEtatsCaisses();
                jeu.afficheBudget();
                jeu.affichePositionClients();

                continuer = jeu.actionsSurCaisse();
                cout << "\n\n\n\n\n\n" << endl;

            }while(!continuer);

            jeu.changerCaisses();
            
            jeu.facturation();
            jeu.afficheDevis();
            jeu.resetDevis();

            jeu.sortirClientsDesCaisses();
            jeu.mettreClientsEnAttente();
            jeu.metttreClientsEnCaisses();

            cout << endl;

            tour++;
        }

        if(jeu.getHypermarcheVide()){
            cout << "Bien joué! Vous avez gagné!" << endl;
        }else{
            cout << "Dommage. Vous avez perdu..." << endl;
        }

        cout << "Vous avez joue " << tour-1 << " tours" << endl;
        cout << "Votre score est :" << jeu.getCredits() << " credits" << endl ;
        
        score.setScore(jeu.getCredits());


        // // score
        cout << "Quel est votre nom ?: " ;
        getline(cin, nomJoueur);
        score.setNomJoueur(nomJoueur);
        cout << score.getNomJoueur() << endl ;
        // score.TrieEtInsereScoreDansFichierTxt(SCORE_FILE);
        // score.afficherScoresDepuisFichierTxt(SCORE_FILE);

        // Score
        score.mettreAJourScoreboard(SCORE_FILE);

        
        //demander restart
        cout << "Voulez vous recommencer ? o[oui]/n[non] :" ;
        getline(cin, restart);

        if (restart=="o"){
            jeu.reset();
            score.reset();
        }

        // delete &score;
        // delete &jeu;
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