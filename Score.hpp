#ifndef SCORE_HPP
#define SCORE_HPP


#include <string>
#include <vector>

using namespace std;

class Score{
private:

    string nomJoueur;
    int score;

public:

    Score();

    void reset();

    string demanderNomJoueur();

    string getNomJoueur();
    void setNomJoueur(string nomJoueur);

    int getScore();
    void setScore(int newScore);

    bool fichierExiste(string filename);

    void creerFichier(string filename);
    void creerFichierSiNExistePas(string filename);

    void afficherScoresDepuisFichierTxt(string filename);

    // Ajouts
    void ajouterNomsEtScoresDansVecteur(string filename, vector<Score>& scoresTousLesJoueurs);
    void ajouterNomEtScoreJoueurActuel(vector<Score>& scoresTousLesJoueurs);
    void trierScoresParOrdreDecroissant(vector<Score>& scoresTousLesJoueurs);
    void ecrireJoueursDansFichierTxt(string filename, vector<Score> scoresTousLesJoueurs);
    void mettreAJourScoreboard(string filename);

};

#endif // SCORE_HPP