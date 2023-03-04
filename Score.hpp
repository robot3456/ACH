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

    bool fileExists(string filename);

    void createFile(string filename);
    void createFileIfNotExists(string filename);

    void writeScoreToFile(string filename);
    void readScoreFromFile(string filename);

    void TrieEtInsereScoreDansFichierTxt(string filename);

};


#endif // SCORE_HPP