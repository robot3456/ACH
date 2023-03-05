#include "Score.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/* Constructeur contenant le nom du joueur et son score 
* Nom du joueur vide au départ, score initialisé à 0 */
Score::Score(){
    this->nomJoueur="";
    this->score=0;
}

/* Getter du nom du joueur en cours */
string Score::getNomJoueur(){
    // cout << "Votre nom est: " << this->nomJoueur <<endl;
    return this->nomJoueur;
}

/* Setter du nom du joueur en cours 
* @param: nom du joueur */
void Score::setNomJoueur(string nomJoueur){
    this->nomJoueur = nomJoueur ;
}

/* Getter du score du joueur actuel */
int Score::getScore(){
    return this->score;
}


/* Setter du score du joueur actuel */
void Score::setScore(int newScore){
    this->score = newScore;
}

/* Vérifie que le fichier <filename> existe
* retourne true si il existe, false sinon 
* @param: nom du fichier dont on veut vérifier l'existence
*/
bool Score::fichierExiste(string filename) {
  ifstream file(filename);
  return file.good();
}

/* Crée un fichier <filename> si il n'existe pas 
* @param: nom du fichier à créer
*/
void Score::creerFichierSiNExistePas(string filename){
    
    if(!this->fichierExiste(filename)){
        cout << "Le fichier " << filename << " n'existe pas. Création du fichier ..." << endl ;
        ofstream scoreFile ;
        scoreFile.open(filename) ;  
        scoreFile.close();
    }
}

/* Ecrit le score contenu dans la variable score de l'instance en cours
* @param: nom du fichier dans lequel le score doit être écrit 
*/
void Score::ecrireScoreDansFichierTxt(string filename){
    this->creerFichierSiNExistePas(filename);
    ofstream scoreFile;
    scoreFile.open(filename, ios_base::app);
    scoreFile << this->nomJoueur << " " << this->score << endl;
    scoreFile.close();
}

/* Lit le fichier contenant les scores et affiche 
* le résultat dans un tableau
* Si ce tableau contient plus de 10 lignes, il affichera les 10 meilleurs scores des joueurs
* Si il contient moins de 10 valeurs alors il les affichera toutes 
* @param: nom du fichier dans lequel sont inscrits les scores */
void Score::lireScoreDepuisFichierTxt(string filename){
    
    this->creerFichierSiNExistePas(filename);

    ifstream scoreFile;
    string nomJoueur;
    int scoreJoueur;

    scoreFile.open(filename);

    cout << "\n\t---- TABEAU DES MEILLEURS SCORES ----" << endl;
    cout << "\t-------------------------------------" << endl;
    cout <<"\tRANG\tNOM\t\t\tSCORE" << endl;
    cout << "\t-------------------------------------" << endl;

    // Afficher les 10 meilleurs scores ou afficher tous les scores si il y en a moins de 10 
    int i=0;
    while ( scoreFile >> nomJoueur >> scoreJoueur && i<10){
        cout << "\t" << i+1 << "\t" << nomJoueur << "\t\t\t" << scoreJoueur << endl ;
        i++;
    }

    cout << "\t-------------------------------------\n" << endl;
    scoreFile.close();
}


/* Fonction récursive
* Fonction qui Trie et insère les joueurs dans un fichier texte par ordre décroissant du score
* @param: nom du fichier dans lequel sont stockés les scores
*/
void Score::TrieEtInsereScoreDansFichierTxt(string filename){
    
    // Ouvrir le fichier en lecture
    ifstream scoreFile(filename);

    // Pour récupérer le contenu de chaque ligne du fichier texte
    string line;

    // Vecteur qui servira à contenir le nom et le score des joueurs par ordre décroissant du score
    vector<Score> scoresTousLesJoueurs;
    
    // Lire les joueurs du fichier et les stocker dans un vecteur
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

    // Créer une instance de Score contenant le nom et le score du joueur actuel
    Score scoreCourant;
    scoreCourant.setNomJoueur(this->getNomJoueur());
    scoreCourant.setScore(this->getScore());

    /* Ajouter les valeurs dans <scoreCourant> dans le vecteur 
     <scoresTousLesJoueurs> les uns à la suite des autres */
    scoresTousLesJoueurs.push_back(scoreCourant);

    // Trier les joueurs par ordre décroissant du score
    sort(scoresTousLesJoueurs.begin(), scoresTousLesJoueurs.end(), [](Score s1, Score s2) { return s1.getScore() > s2.getScore(); });

    // Ouvrir le fichier en écriture et ajouter les joueurs triés au fichier
    ofstream scoreFileOut(filename);
    for (Score s : scoresTousLesJoueurs) {
        scoreFileOut << s.getNomJoueur() << " " << s.getScore() << endl;
    }
    scoreFileOut.close();
}




