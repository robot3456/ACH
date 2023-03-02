#include "Score.hpp"

#include <iostream>
#include <fstream>

#define SCORE_FILE "Scoreboard.txt"

using namespace std;

Score::Score(){
    int score=0;
    fstream scoreFile;
}

int Score::getScore(){
    return this->score;
}


void Score::setScore(int newScore){
    this->score = newScore;
}



void Score::createFile(){

    this->scoreFile.open(SCORE_FILE, ios::out);

    if(this->scoreFile.is_open()){
        cout << "Le fichier contenant les scores a correctement ete cree !" << endl;
        this->scoreFile << "bonjour tout le monde";
        this->scoreFile.close();
    }
    else {
        cerr << "ATTENTION ! Le fichier n'a pas ete correctement cree, il y a eu un probleme"  << endl ;
    }
}





void Score::createFileIfNotExists(){

    this->scoreFile.open(SCORE_FILE);

    if (this->scoreFile) {

        // use existing file
        cout<< "success "<< SCORE_FILE <<" found. \n";
        cout<<"\nAppending writing and working with existing file"<<"\n---\n";

        //this->scoreFile.open(SCORE_FILE, fstream::app | fstream::out | fstream::in);


        //this->scoreFile << "Appending writing and working with existing file"<<"\n---\n";
        this->scoreFile << "Appending";
        this->scoreFile.close();
        cout<<"\n";
    } 

    // If file does not exist, Create new file
    else{

        cout << "Cannot open file, file does not exist. Creating new file..";

        this->scoreFile.open(SCORE_FILE,  fstream::in | fstream::out | fstream::trunc);
        this->scoreFile <<"SCORE\t\t NOM\n";
        this->scoreFile << "----------------------------\n";
        this->scoreFile.close();
        cout<<"\n"<<endl;

    }
}