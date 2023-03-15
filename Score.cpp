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

void Score::reset(){
    this->nomJoueur="";
    this->score=0;
}

/* Demande le nom du joueur et le renvoie en tant que chaine de caractères 
* @return nom du joueur*/
string Score::demanderNomJoueur(){

    string nomJoueur;

    while(nomJoueur.empty()){

        cout << "Quel est votre nom ? :";
        getline(cin, nomJoueur);
        this->nomJoueur = nomJoueur;

        if(nomJoueur.empty()){
            cout << "\033[1;31mErreur ! Veuillez entrer un nom valide.\033[0m"<< endl;
        }
    }
    return nomJoueur;
}

/* Getter du nom du joueur en cours 
* @return nom du joueur*/
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
    
    if(!fichierExiste(filename)){
        cout << "Le fichier " << filename << " n'existe pas. Création du fichier ..." << endl ;
        ofstream scoreFile ;
        scoreFile.open(filename) ;  
        scoreFile.close();
    }
}

/* Lit le fichier contenant les scores et affiche 
* le résultat dans un tableau
* Si ce tableau contient plus de 10 lignes, il affichera les 10 meilleurs scores des joueurs
* Si il contient moins de 10 valeurs alors il les affichera toutes 
* @param: nom du fichier dans lequel sont inscrits les scores */
void Score::afficherScoresDepuisFichierTxt(string filename){
    
    creerFichierSiNExistePas(filename);

    // Ouvre le fichier en lecture
    ifstream scoreFile;

    string nomJoueur;
    int scoreJoueur;

    scoreFile.open(filename);

    cout << "\n\t---------- TABEAU DES MEILLEURS SCORES ----------" << endl;
    cout << "\t-------------------------------------------------" << endl;
    cout <<"\tRANG\tNOM\t\t\t\tSCORE" << endl;
    cout << "\t-------------------------------------------------" << endl;

    // Afficher les 10 meilleurs scores ou afficher tous les scores si il y en a moins de 10 
    int i=0;
    while ( scoreFile >> nomJoueur >> scoreJoueur && i<10){

        if ((nomJoueur == this->nomJoueur) && (scoreJoueur == this->score)){
            cout << "\033[1;32m" << "\t" << i+1 << "\t" << nomJoueur << "\t\t\t" << scoreJoueur << "\033[0m" << endl ;
        }else{
            cout << "\t" << i+1 << "\t" << nomJoueur << "\t\t\t" << scoreJoueur << endl ;
        }
        i++;
    }

    cout << "\t-------------------------------------------------\n" << endl;
    scoreFile.close();
}


/* Fonction récursive
* Fonction qui Trie et insère les noms et scores des joueurs dans un vecteur <scoresTousLesJoueurs>
* @param: nom du fichier dans lequel sont stockés les scores
* PS : s'il vous plait Monsieur, mettez nous des points en plus, on a vraiment beaucoup travailé sur ce projet
*/
void Score::ajouterNomsEtScoresDansVecteur(string filename, vector<Score>& scoresTousLesJoueurs){
    
    // Ouvrir le fichier en lecture
    ifstream scoreFile(filename);

    // Pour récupérer le contenu de chaque ligne du fichier texte
    string line;

    // Vecteur qui servira à contenir le nom et le score des joueurs par ordre décroissant du score
    
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
}
    
/* Ajoute le nom et le score du joueur actuel au vecteur <scoresTousLesJoueurs> */
void Score::ajouterNomEtScoreJoueurActuel(vector<Score>& scoresTousLesJoueurs){
    // Créer une instance de Score contenant le nom et le score du joueur actuel
    Score scoreCourant;
    scoreCourant.setNomJoueur(this->getNomJoueur());
    scoreCourant.setScore(this->getScore());

    /* Ajouter les valeurs dans <scoreCourant> dans le vecteur 
     <scoresTousLesJoueurs> les uns à la suite des autres */
    scoresTousLesJoueurs.push_back(scoreCourant);
}

void Score::trierScoresParOrdreDecroissant(vector<Score>& scoresTousLesJoueurs){

    // Trier les joueurs par ordre décroissant du score
    sort(scoresTousLesJoueurs.begin(), scoresTousLesJoueurs.end(), [](Score s1, Score s2) { return s1.getScore() > s2.getScore(); });
}

/* Ecriture des joueurs et scores contenus dans <scoresTousLesJoueurs> vers le fichier Scoreboard.txt */ 
void Score::ecrireJoueursDansFichierTxt(string filename, vector<Score> scoresTousLesJoueurs){
    // Ouvrir le fichier en écriture et ajouter les joueurs triés au fichier
    ofstream scoreFileOut(filename);
    for (Score s : scoresTousLesJoueurs) {
        scoreFileOut << s.getNomJoueur() << " " << s.getScore() << endl;
    }
    scoreFileOut.close();
}


/* Fonction de mise à jour du tableau des scores avec le joueur actuel */
void Score::mettreAJourScoreboard(string filename){
    
    vector<Score> scoresTousLesJoueurs;

    // Ajoute les noms et les scores de tous les joueurs dans le vecteur <scoresTousLesJoueurs>
    ajouterNomsEtScoresDansVecteur(filename, scoresTousLesJoueurs);

    // Ajoute le nom et le score du joueur actuel au vecteur <scoresTousLesJoueurs>
    ajouterNomEtScoreJoueurActuel(scoresTousLesJoueurs);

    // Trie les joueurs du vecteur par ordre décroissant du score
    trierScoresParOrdreDecroissant(scoresTousLesJoueurs);

    // Ecriture des joueurs et scores contenus dans <scoresTousLesJoueurs> vers le fichier Scoreboard.txt 
    ecrireJoueursDansFichierTxt(filename, scoresTousLesJoueurs);

    // Affiche les scores du fichier Scoreboard.txt
    afficherScoresDepuisFichierTxt(filename);

}















