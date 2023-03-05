#ifndef SCORE_HPP
#define SCORE_HPP



#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Score{
private:

    string nomJoueur;
    int score;

public:

    Score();

    string getNomJoueur();
    void setNomJoueur(string nomJoueur);

    int getScore();
    void setScore(int newScore);

    bool fichierExiste(string filename);

    void creerFichier(string filename);
    void creerFichierSiNExistePas(string filename);

    void ecrireScoreDansFichierTxt(string filename);
    void lireScoreDepuisFichierTxt(string filename);

    void TrieEtInsereScoreDansFichierTxt(string filename);

};


#endif // SCORE_HPP