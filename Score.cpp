#include "Score.hpp"

#include <iostream>
#include <fstream>


using namespace std;

Score::Score(){
    this->nomJoueur="";
    this->score=0;
}

void Score::getNomJoueur(){
    cout << "Votre nom est: " << this->nomJoueur <<endl;
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
    cout <<"\tNOM\t\t\t SCORE" << endl;
    cout << "\t-------------------------------------" << endl;

    while ( scoreFile >> nomJoueur >> scoreJoueur){
        cout << "\t" << nomJoueur << "\t\t\t" << scoreJoueur << endl ;
    }

    cout << "\t-------------------------------------\n" << endl;
    scoreFile.close();
}

