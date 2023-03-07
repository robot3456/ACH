#include "Jeu.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <limits>

using namespace std;

/* Constructeur de la classe Jeu contenant les variables :
* credits : le nombre de crédits attribués initialement au joueur
* clientsEnCourses : le nombre de clients initialement dans le magasin 
* clientsEnAttente : le nombre de clients en attente de caisse 
* hypermarcheVide : true si il y a 0 personnes dans l'hypermarche (caisses comprises) / false sinon 
* nombreToursJoues : le nombre de tours du joueur 
*/
Jeu::Jeu(){

    //initialisation par défaut du jeu
    this->credits=STARTING_CREDITS;
    this->clientsEnCourses=STARTING_CLIENTS_EN_COURSE;
    this->clientsEnAttente=STARTING_CLIENTS_EN_ATTENTE;

    this->hypermarcheVide=false;
    this->tour=1;

    this->devis.resetDevis();

    this->errorMessage="";

    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i] = new Caisse();
        this->changementsCaisse[i] = '-';
    }
}


/* Destructeur de la classe Jeu */
Jeu::~Jeu(){}

bool Jeu::getHypermarcheVide(){
    return this->hypermarcheVide;
}

void Jeu::setHypermarcheVide(bool newState){
    this->hypermarcheVide = newState;
}

/* Getter du tour actuel */
int Jeu::getTour(){
    return this->tour;
}

/* Setter pour changer la valeur du tour */
void Jeu::setTour(int tourActuel){
    this->tour=tourActuel;
}

/* Retourne le nombre de credits */
int Jeu::getCredits(){
    return this->credits;
}

/* Réinitialise les valeurs à celles au départ 
afin de pouvoir recommencer une nouvelle partie */
void Jeu::reset(){

    this->credits=STARTING_CREDITS;
    this->hypermarcheVide=false;
    this->clientsEnCourses=STARTING_CLIENTS_EN_COURSE;
    this->clientsEnAttente=0;

    // Pour chaque caisse, remettre le nombre de clients à 0
    // et fermer la caisse (passée à l'état "false")
    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i]->resetClientsEnCaisse();
        this->caisses[i]->fermerCaisse();
    }
}


/*  
*   Fonction qui met un nombre aléatoir de clients en attente
*   Renvoie:
*       le nombre de clients qui sont mis en attente
*       -1, Erreur il y a un nombre négatif de clients en coursr -> Impossible
*/
int Jeu::mettreClientsEnAttente()
{
    /*On renvoie 0 direct si aucun clients ne fait les courses*/
    if (this->clientsEnCourses==0)
        return 0;

    /*On renvoie -1 s'il y a un nombre de clients en course négatif*/
    if (this->clientsEnCourses<0)
        return -1;

    /*Initialisation de rand*/
    std::srand(time(NULL));

    /*Variable qui va compter le nombre de clients en course en moins*/
    int clientsEnMoins = 0;

    /* On itère sur tout les clients en course, on a une chance de 1/2 pour que le clients
    passe en attente */
    for(int i=0; i<this->clientsEnCourses; i++){
        if(std::rand()%2){
            clientsEnMoins++;
            this->clientsEnAttente++;
        }
    }

    this->clientsEnCourses-=clientsEnMoins;
    return clientsEnMoins;
}


/*
*   Fonction qui envoie les clients en attente dans des caisses ouvertes
*   Renvoie:
*       0,  si aucun clients n'a été envoyé en caisse
*       1,  si les clients en attente on été envoyé en caisse
*       -1, s'il y a eu un problème
*/
int Jeu::metttreClientsEnCaisses()
{
    /*On renvoie 0 s'il y a aucun clients en attente*/
    if (this->clientsEnAttente==0)
        return 0;

    /*On initialise une liste des caisses ouvertes, ainsi que le nombre de caisses ouvertes*/
    vector<int> caisseOuvertes = this->getCaissesOuvertes();
    int nbCaissesOuvertes = caisseOuvertes.size();

    /*On renvoie 0 s'il y a aucune caisse ouverte*/
    if (nbCaissesOuvertes==0)
        return 0;

    /*On initialise une variable pour choisir une caisse ouverte aléatoire*/
    int caisseOuverteAleatoire;

    /*On itère sur tout les clients en attente, */
    for(int i=0; i<this->clientsEnAttente; i++){

        /*On choisit une caisse ouverte aléatoire*/
        caisseOuverteAleatoire = caisseOuvertes[rand()%nbCaissesOuvertes];

        /*On ajoute le client à la caisse aléatoire choisi*/
        this->caisses[caisseOuverteAleatoire]->ajouterClientEnCaisse();
    }

    /*
    Tout les clients en attente on été placé, on remet le nombre de clients en attente à 0
    et on renvoie 1.
    */
    this->clientsEnAttente=0;
    return 1;
}

/* Ouvre la caisse d'indice n */
void Jeu::ouvrirCaisse(int n){
    caisses[n]->ouvrirCaisse();
}

/* Ferme la caisse d'indice n */
void Jeu::fermerCaisse(int n){
    caisses[n]->fermerCaisse();
}

/* Retourne un vecteur contenant le numero de toutes les caisses ouvertes */
vector<int> Jeu::getCaissesOuvertes(){
    vector<int> caissesOuvertes;

    for(int i=0;i<NB_CAISSES; i++){

        // Si la caisse est ouverte, ajouter son indice à la fin du vecteur <caissesOuvertes>
        if(caisses[i]->estOuverte()){
            caissesOuvertes.push_back(i);
        }
    }
    return caissesOuvertes;
}

/* Supprime le montant du devis au crédit du joueur */
void Jeu::facturation(){
    this->credits-=this->devis.getTotal();
}

void Jeu::afficheEtatsCaisses(){
    for(int i=0; i<NB_CAISSES; i++){
        cout << this->caisses[i]->getChangement() << " Caisse " << i+1 << ":\t"<< this->caisses[i]->afficheInfoCaisse() << endl;
    }   
}

/* Affiche le budget du joueur */
void Jeu::afficheBudget(){
    cout << "Budget: " << this->credits << " crédits." << endl;
}


void Jeu::sortirClientsDesCaisses(){
    vector<int> caissesOuvertes = getCaissesOuvertes();
    if(caissesOuvertes.size()==0){
        return; 
    }

    for(int num_caisse : caissesOuvertes){
        if(this->caisses[num_caisse]->getClientsEnCaisse()==0){
            continue;
        }
        this->caisses[num_caisse]->sortirClient();
    }

}

/* Affiche le nombre total de clients à chaque stade de l'hypermarché */
void Jeu::affichePositionClients(){

    vector<int> caissesOuvertes = getCaissesOuvertes();
    int clientsEnCaisses = 0;
    
    for(int numCaisse: caissesOuvertes){
        clientsEnCaisses += this->caisses[numCaisse]->getClientsEnCaisse();
    }
    cout << "Clients dans l'hypermarché: " << this->clientsEnCourses << ", en attente de caisse: " << this->clientsEnAttente << " et aux caisses: " << clientsEnCaisses << ".\n";
}

/* Demande au joueur les actions qu'il souhaite effectuer sur chaque caisse */
bool Jeu::actionsSurCaisses(){

    string choix;

    cout << endl;
    cout << "Action sur les caisses ..." << endl;
    cout << this->errorMessage << endl;
    cout << "Choisir une caisse à changer[1-10] ou tous les ouvrir[A], Passer et appliquer tout les changements[P] :";
    getline(cin, choix);
    
    // Suppression du caractère \n de la chaine pour obtenir uniquement le choix de l'utilisateur
    if (!choix.empty() && choix[choix.length()-1] == '\n'){
        choix.erase(choix.length()-1);
    }

    // Vérification que la saisie a été faite correctement
    if(cin.fail()){
        this->errorMessage= "\033[1;31mErreur dans la saisie du choix, veuillez réessayer.\033[0m";
        cin.clear();
        return false;
    }

    // Mise en majuscules de la chaine de caractère afin de pouvoir entrer "p" ou "P" (case insensitive)
    for(auto & c: choix) c = toupper(c);

    if(choix=="P"){
        this->errorMessage="";
        return true;
    }
    
    if(choix=="A"){
        for(int i=0; i<NB_CAISSES; i++){
            if(!this->caisses[i]->estOuverte())
                this->caisses[i]->changerEtat();
        }
        return false;
    }

    // Si la saisie de l'utilisateur est valide, alors on effectue les actions qu'il souhaite sur les caisses
    try{
        int choixNumCaisse = stoi(choix);
        if(choixNumCaisse<=NB_CAISSES && choixNumCaisse>=1){
            this->caisses[choixNumCaisse-1]->changerEtat();
            this->errorMessage="";
            return false;
        }

    // Sinon on gère l'exception en demandant une nouvelle saisie
    }catch(exception &err){
        this->errorMessage= "\033[1;31mErreur dans la saisie du choix, veuillez réessayer.\033[0m";
        return false;
    }

    // Demande à l'utilisateur d'entrer une saisie valide
    this->errorMessage="\033[1;31mVeuillez selectionner \"[1-10\" ou \'P\'\033[0m";
    return false;

}

/* Inversion de l'état des caisses sélectionnées par le joueur */
void Jeu::changerCaisses(){
    for(int i=0; i<NB_CAISSES; i++){

        if (this->caisses[i]->aChanger()){
            this->caisses[i]->changerCaisse();

            if(!this->caisses[i]->estOuverte()){
                this->clientsEnAttente+=this->caisses[i]->sortirTousLesClients();
            }
            this->caisses[i]->resetChangement();
        }
    }
}

/* Si l'hypermarché est vide, retourne true. False sinon */
bool Jeu::hypermarcheEstVide(){

    if(this->clientsEnCourses>0)
        return false;

    if(this->clientsEnAttente>0)
        return false;

    
    for(int i=0; i<NB_CAISSES; i++){
        if (this->caisses[i]->getClientsEnCaisse()>0){
            return false;
        }
    }

    this->hypermarcheVide = true;
    return true;
}

/* Calcule et affiche le devis */
void Jeu::afficheDevis(){

    this->devis.calculerDevis(this->caisses, NB_CAISSES, this->clientsEnAttente);
    this->devis.afficheDevis();
}