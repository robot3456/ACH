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

#define STARTING_CREDITS 1000
#define STARTING_CLIENTS_EN_COURSE 10
#define STARTING_CLIENTS_EN_ATTENTE 0

#define PRIX_PAR_CAISSE_OUVERTE 3
#define PRIX_PAR_CLIENT_EN_ATTENTE 2
#define PRIX_PAR_CLIENT_EN_CAISSE 1
#define PRIX_OUVERTURE_FERMETURE_CAISSE 2
#define PRIX_TOUR_DE_JEU 1

Jeu::Jeu(){

    //initialisation par défaut du jeu
    this->credits=STARTING_CREDITS;
    this->clientsEnCourses=STARTING_CLIENTS_EN_COURSE;
    this->clientsEnAttente=STARTING_CLIENTS_EN_ATTENTE;

    this->hypermarcheVide=false;
    this->nombreToursJoues=0;

    this->devis = new struct_devis;

    this->errorMessage="";

    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i] = new Caisse();
        this->changementsCaisse[i] = '-';
    }
}


bool Jeu::getHypermarcheVide(){
    return this->hypermarcheVide;
}

void Jeu::setHypermarcheVide(bool newState){
    this->hypermarcheVide = newState;
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
    // this->clients_en_caisse =0;

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

    /*
    On itère sur tout les clients en course, on a une chance de 1/2 pour que le clients
    passe en attente
    */
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

void Jeu::ouvrirCaisse(int n){
    caisses[n]->ouvrirCaisse();
}

void Jeu::fermerCaisse(int n){
    caisses[n]->fermerCaisse();
}

vector<int> Jeu::getCaissesOuvertes(){
    vector<int> caissesOuvertes;

    for(int i=0;i<NB_CAISSES; i++){
        if(caisses[i]->estOuverte()){
            caissesOuvertes.push_back(i);
        }
    }
    return caissesOuvertes;
}


void Jeu::facturation(){

    vector<int> caissesOuvertes = getCaissesOuvertes();
    uint16_t nbCaissesOuvertes = caissesOuvertes.size();
    
    this->devis->caisseOuverte=nbCaissesOuvertes;
    this->devis->clientsEnAttente=this->clientsEnAttente;
    
    this->credits -= caissesOuvertes.size()*PRIX_PAR_CAISSE_OUVERTE;
    this->credits -= this->clientsEnAttente*PRIX_PAR_CLIENT_EN_ATTENTE;

    for(int numCaisse : caissesOuvertes){
        this->devis->clientsEnCaisse+=this->caisses[numCaisse]->getClientsEnCaisse();
        this->credits -= caisses[numCaisse]->getClientsEnCaisse()*PRIX_PAR_CLIENT_EN_CAISSE;
    }

    this->credits -= PRIX_TOUR_DE_JEU;
}

void Jeu::afficheEtatsCaisses(){

    for(int i=0; i<NB_CAISSES; i++){
        cout << this->caisses[i]->getChangement() << " Caisse " << i+1 << ":\t"<< this->caisses[i]->afficheInfoCaisse() << endl;
    }   
}

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

void Jeu::affichePositionClients(){

    vector<int> caissesOuvertes = getCaissesOuvertes();
    int clientsEnCaisses = 0;
    
    for(int numCaisse: caissesOuvertes){
        clientsEnCaisses += this->caisses[numCaisse]->getClientsEnCaisse();
    }
    cout << "Clients dans l'hypermarché: " << this->clientsEnCourses << ", en attente de caisse: " << this->clientsEnAttente << " et aux caisses: " << clientsEnCaisses << ".\n";
}

bool Jeu::actionsSurCaisses(){

    string choix;

    cout << endl;
    cout << "Action sur les caisses ..." << endl;
    cout << this->errorMessage << endl;
    cout << "Choisir une caisse à changer[1-10], Passer et appliquer tout les changements[P] :";
    getline(cin, choix);
    
    //On efface le caractère \n de la chaine pour avoir que le choix de l'utilisateur
    if (!choix.empty() && choix[choix.length()-1] == '\n'){
        choix.erase(choix.length()-1);
    }

    //On vérifie que la saisie a été faite correctement
    if(cin.fail()){
        this->errorMessage= "\033[1;31mErreur dans la saisie du choix, veuillez réessayer.\033[0m";
        cin.clear();
        return false;
    }

    //On met la chaine de caractère en majuscule pour pouvoir entrer "p" ou "P"
    for(auto & c: choix) c = toupper(c);

    if(choix=="P"){
        this->errorMessage="";
        return true;
    }
        
    try{
        
        int choixNumCaisse = stoi(choix);
        if(choixNumCaisse<=NB_CAISSES && choixNumCaisse>=1){
            this->caisses[choixNumCaisse-1]->changerEtat();
            this->errorMessage="";
            return false;
        }

    }catch(exception &err){
        this->errorMessage= "\033[1;31mErreur dans la saisie du choix, veuillez réessayer.\033[0m";
        return false;
    }

    this->errorMessage="\033[1;31mVeuillez selectionner \"[1-10\" ou \'P\'\033[0m";
    return false;

}

void Jeu::changerCaisses(){
    for(int i=0; i<NB_CAISSES; i++){
        if (this->caisses[i]->aChanger()){
            this->caisses[i]->changerCaisse();
            this->credits -= PRIX_OUVERTURE_FERMETURE_CAISSE;
            this->devis->ouvertureFermetureDeCaisse++;

            if(!this->caisses[i]->estOuverte()){
                this->clientsEnAttente+=this->caisses[i]->sortirTousLesClients();
            }
            this->caisses[i]->resetChangement();
        }
    }
}

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

void Jeu::resetDevis(){
    this->devis->clientsEnCaisse=0;
    this->devis->caisseOuverte=0;
    this->devis->clientsEnAttente=0;
    this->devis->ouvertureFermetureDeCaisse=0;
}

void Jeu::afficheDevis(){

    int totalOuvertureFermeture = this->devis->ouvertureFermetureDeCaisse*PRIX_OUVERTURE_FERMETURE_CAISSE;
    int totalCaisseOuverte = this->devis->caisseOuverte*PRIX_PAR_CAISSE_OUVERTE;
    int totalClientsEnAttente = this->devis->clientsEnAttente*PRIX_PAR_CLIENT_EN_ATTENTE;
    int totalClientsEnCaisse = this->devis->clientsEnCaisse*PRIX_PAR_CLIENT_EN_CAISSE;

    int total = 1 + totalOuvertureFermeture + totalCaisseOuverte + totalClientsEnAttente + totalClientsEnCaisse ;

    cout << "-----------------------------------------------------------------" << endl;
    
    cout << "|\t\t\t\t\t\t\tPrix\t|" << endl;
    
    cout << "|\t\t\t\t\t\t\t\t|" << endl;

    cout << "| ouverture/fermetures de caisses :\t" \
    << this->devis->ouvertureFermetureDeCaisse \
    << "  x  " << PRIX_OUVERTURE_FERMETURE_CAISSE << "cr\t= " \
    << totalOuvertureFermeture << "cr\t|" << endl;

    cout << "| caisse(s) ouverte(s) : \t\t" \
    << this->devis->caisseOuverte \
    << "  x  " << PRIX_PAR_CAISSE_OUVERTE << "cr\t= " \
    << totalCaisseOuverte << "cr\t|" << endl;

    cout << "| clients en attente :\t\t\t" \
    << this->devis->clientsEnAttente \
    << "  x  " << PRIX_PAR_CLIENT_EN_ATTENTE << "cr\t= " \
    << totalClientsEnAttente << "cr\t|" << endl;

    cout << "| clients en caisse :\t\t\t" \
    << this->devis->clientsEnCaisse \
    << "  x  " << PRIX_PAR_CLIENT_EN_CAISSE << "cr\t= " \
    << totalClientsEnCaisse << "cr\t|" << endl;

    cout << "| Tour:\t\t\t\t\t\t\t  1cr\t|" << endl;

    cout << "|\t------------------------------------------------\t|" << endl;

    cout << "| Total:\t\t\t\t\t\t  " << total << "cr\t|" << endl;

    cout << "|\t\t\t\t\t\t\t\t|" << endl;

    cout << "-----------------------------------------------------------------" << endl;
}