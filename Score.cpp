#include "Score.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#define nombreEspaces 28

using namespace std;

/**
 * @brief Constructeur contenant le nom du joueur et son score 
 * Nom du joueur vide au départ, score initialisé à 0
 * 
 */
 Score::Score(){
    this->nomJoueur="";
    this->score=0;
}

/**
 * @brief Utilisée si le joueur souhaite recommencer une partie
 * Remise à vide de la chaîne de caractères "nomJoueur" contenant le nom du joueur actuel
 * Remise à zero du score du joueur actuel
 */
void Score::reset(){
    this->nomJoueur="";
    this->score=0;
}

/**
 * @brief Demande le nom du joueur actuel. 
 * Vérifie qu il n'a pas donné une réponse vide
 * 
 * @return string nom du joueur actuel
 */
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

/**
 * @brief Getter du nom du joueur en cours
 * 
 * @return string nom du joueur en cours
 */
string Score::getNomJoueur(){
    // cout << "Votre nom est: " << this->nomJoueur <<endl;
    return this->nomJoueur;
}

/**
 * @brief Setter du nom du joueur en cours
 * 
 * @param nomJoueur nom du joueur en cours
 */
void Score::setNomJoueur(string nomJoueur){
    this->nomJoueur = nomJoueur ;
}

/**
 * @brief Getter du score du joueur actuel 
 * 
 * @return int score du joueur actuel
 */
int Score::getScore(){
    return this->score;
}

/**
 * @brief Setter du score du joueur actuel
 * 
 * @param newScore score du joueur obtenu par le joueur actuel
 */
void Score::setScore(int newScore){
    this->score = newScore;
}

/**
 * @brief Permet de savoir si le fichier <filename> existe.
 * 
 * @param filename nom du fichier dont on veut vérifier l'existence
 * @return true si le fichier a été trouvé
 * @return false si le fichier n'a pas été trouvé
 */
bool Score::fichierExiste(string filename) {
  ifstream file(filename);
  return file.good();
}

/**
 * @brief Crée le fichier <filename> si il n'a pas été trouvé
 * 
 * @param filename nom du fichier à créer 
 */
void Score::creerFichierSiNExistePas(string filename){
    
    if(!fichierExiste(filename)){
        cout << "Le fichier " << filename << " n'existe pas. Création du fichier ..." << endl ;
        ofstream scoreFile ;
        scoreFile.open(filename) ;  
        scoreFile.close();
    }
}

/**
 * @brief Lit le fichier texte contenant les scores et affiche le résultat dans un tableau.
 * Si ce tableau contient plus de 10 joueurs, il affichiera les 10 meilleurs joueurs et leurs scores.
 * Si il contient moins de 10 valeurs alors il les affichiera toutes.
 * @param filename nom du fichier dans lequel sont inscrits les scores.
 */
void Score::afficherScoresDepuisFichierTxt(string filename){
    
    creerFichierSiNExistePas(filename);

    // Ouvre le fichier en lecture
    ifstream scoreFile;

    string nomJoueur;
    int scoreJoueur;

    scoreFile.open(filename);

    cout << "\n\t---------- TABEAU DES MEILLEURS SCORES ----------" << endl;
    cout << "\t-------------------------------------------------" << endl;
    cout <<"\tRANG\tNOM" << string(nombreEspaces, ' ') << "SCORE" << endl;
    cout << "\t-------------------------------------------------" << endl;

    // Afficher les 10 meilleurs scores ou afficher tous les scores si il y en a moins de 10 
    int i=0;
    while ( scoreFile >> nomJoueur >> scoreJoueur && i<10){

        string nombreEspacesFormate(nombreEspaces+3-(nomJoueur.length()) , ' ');

        if ((nomJoueur == this->nomJoueur) && (scoreJoueur == this->score)){
            cout << "\033[1;32m" << "\t" << i+1 << "\t" << nomJoueur << nombreEspacesFormate << scoreJoueur << "\033[0m" << endl ;
        }else{
            cout << "\t" << i+1 << "\t" << nomJoueur << nombreEspacesFormate << scoreJoueur << endl ;
        }
        i++;
    }

    cout << "\t-------------------------------------------------\n" << endl;
    scoreFile.close();
}

/**
 * @brief (Fonction récursive) Trie et insère les noms et scores des joueurs dans un vecteur <scoresTousLesJoueurs>
 * 
 * @param filename nom du fichier dans lequel sont stockés les scores.
 * @param scoresTousLesJoueurs Vecteur contenant tous les joueurs et leur scores associés.
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
    
/**
 * @brief Ajoute le nom et le score du joueur actuel au vecteur <scoresTousLesJoueurs>.
 * 
 * @param scoresTousLesJoueurs Vecteur contenant tous les joueurs et leur scores associés.
 */
void Score::ajouterNomEtScoreJoueurActuel(vector<Score>& scoresTousLesJoueurs){
    // Créer une instance de Score contenant le nom et le score du joueur actuel
    Score scoreCourant;
    scoreCourant.setNomJoueur(this->getNomJoueur());
    scoreCourant.setScore(this->getScore());

    /* Ajouter les valeurs dans <scoreCourant> dans le vecteur 
     <scoresTousLesJoueurs> les uns à la suite des autres */
    scoresTousLesJoueurs.push_back(scoreCourant);
}

/**
 * @brief Trie les éléments (nom du joueur, score) du vecteur <scoresTousLesJoueurs> par ordre décroissant des scores
 * 
 * @param scoresTousLesJoueurs Vecteur contenant tous les joueurs et leur scores associés.
 */
void Score::trierScoresParOrdreDecroissant(vector<Score>& scoresTousLesJoueurs){

    // Trier les joueurs par ordre décroissant du score
    sort(scoresTousLesJoueurs.begin(), scoresTousLesJoueurs.end(), [](Score s1, Score s2) { return s1.getScore() > s2.getScore(); });
}

/** Ecriture des joueurs et scores contenus dans <scoresTousLesJoueurs> vers le fichier Scoreboard.txt */ 

/**
 * @brief Ecris les noms des joueurs et leurs scores associés dans un fichier texte. 
 * 
 * @param filename nom du fichier dans lequel les nom et scores seront inscits.
 * @param scoresTousLesJoueurs Vecteur contenant tous les joueurs et leur scores associés.
 */
void Score::ecrireJoueursDansFichierTxt(string filename, vector<Score> scoresTousLesJoueurs){
    // Ouvrir le fichier en écriture et ajouter les joueurs triés au fichier
    ofstream scoreFileOut(filename);
    for (Score s : scoresTousLesJoueurs) {
        scoreFileOut << s.getNomJoueur() << " " << s.getScore() << endl;
    }
    scoreFileOut.close();
}

/**
 * @brief Met à jour le tableau des scores avec le nom et le score du joueur actuel
 * 
 * @param filename nom du fichier dans lequel les noms et scores seront inscrits
 */
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





