#include "Score.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Score::Score(){
    this->nomJoueur="";
    this->score=0;
}

string Score::getNomJoueur(){
    // cout << "Votre nom est: " << this->nomJoueur <<endl;
    return this->nomJoueur;
}

void Score::setNomJoueur(string nomJoueur){
    this->nomJoueur = nomJoueur ;
}


int Score::getScore(){
    return this->score;
}


void Score::setScore(int newScore){
    this->score = newScore;
}


bool Score::fileExists(string filename) {
  ifstream file(filename);
  return file.good();
}


void Score::createFileIfNotExists(string filename){
    
    if(!this->fileExists(filename)){
        cout << "Le fichier " << filename << " n'existe pas. Création du fichier ..." << endl ;
        ofstream scoreFile ;
        scoreFile.open(filename) ;  
        scoreFile.close();
    }
}


void Score::writeScoreToFile(string filename){
    this->createFileIfNotExists(filename);
    ofstream scoreFile;
    scoreFile.open(filename, ios_base::app);
    scoreFile << this->nomJoueur << " " << this->score << endl;
    scoreFile.close();
}

void Score::readScoreFromFile(string filename){
    
    this->createFileIfNotExists(filename);

    ifstream scoreFile;
    string nomJoueur;
    int scoreJoueur;

    scoreFile.open(filename);

    cout << "\n\t--------- TABEAU DES SCORES ---------" << endl;
    cout << "\t-------------------------------------" << endl;
    cout <<"\tRANG\tNOM\t\t\tSCORE" << endl;
    cout << "\t-------------------------------------" << endl;

    // while ( scoreFile >> nomJoueur >> scoreJoueur){
    //     cout << "\t" << nomJoueur << "\t\t\t" << scoreJoueur << endl ;
    // }
    int i=0;
    while ( scoreFile >> nomJoueur >> scoreJoueur && i<10){
        cout << "\t" << i+1 << "\t" << nomJoueur << "\t\t\t" << scoreJoueur << endl ;
        i++;
    }

    cout << "\t-------------------------------------\n" << endl;
    scoreFile.close();
}

void Score::TrieEtInsereScoreDansFichierTxt(string filename){
    
    ifstream scoreFile(filename);
    string line;
    vector<Score> scoresTousLesJoueurs;
    
    while (getline(scoreFile, line)) {
        std::stringstream ss(line);
        string nomJoueur;
        int scoreJoueur;
        ss >> nomJoueur >> scoreJoueur;
        Score scoreJoueurFichierTxt;
        scoreJoueurFichierTxt.setNomJoueur(nomJoueur);
        scoreJoueurFichierTxt.setScore(scoreJoueur);
        scoresTousLesJoueurs.push_back(scoreJoueurFichierTxt);
    }
    scoreFile.close();

    Score scoreCourant;
    scoreCourant.setNomJoueur(this->getNomJoueur());
    scoreCourant.setScore(this->getScore());

    scoresTousLesJoueurs.push_back(scoreCourant);

    sort(scoresTousLesJoueurs.begin(), scoresTousLesJoueurs.end(), [](Score s1, Score s2) { return s1.getScore() > s2.getScore(); });

    ofstream scoreFileOut(filename);
    for (Score s : scoresTousLesJoueurs) {
        scoreFileOut << s.getNomJoueur() << " " << s.getScore() << endl;
    }
    scoreFileOut.close();
}




