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
    this->clients_courses=STARTING_CLIENTS_EN_COURSE;
    this->clients_en_attente=STARTING_CLIENTS_EN_ATTENTE;

    this->hypermarche_vide=false;
    this->nombre_tours_joues=0;

    this->devis = new struct_devis;

    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i] = new Caisse();
        this->changements_caisse[i] = '-';
    }
}


bool Jeu::getHypermarcheVide(){
    return this->hypermarche_vide;
}

void Jeu::setHypermarcheVide(bool newState){
    this->hypermarche_vide = newState;
}


// Duplicata de la fonction affiche_budget()
int Jeu::getCredits(){
    return this->credits;
}

void Jeu::reset(){

    this->credits=STARTING_CREDITS;
    this->hypermarche_vide=false;
    this->clients_courses=STARTING_CLIENTS_EN_COURSE;
    this->clients_en_attente=0;
    // this->clients_en_caisse =0;

    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i]->reset_clients_en_caisse();
        this->caisses[i]->fermer_caisse();
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
    if (this->clients_courses==0)
        return 0;

    /*On renvoie -1 s'il y a un nombre de clients en course négatif*/
    if (this->clients_courses<0)
        return -1;

    /*Initialisation de rand*/
    std::srand(time(NULL));

    /*Variable qui va compter le nombre de clients en course en moins*/
    int clientsEnMoins = 0;

    /*
    On itère sur tout les clients en course, on a une chance de 1/2 pour que le clients
    passe en attente
    */
    for(int i=0; i<this->clients_courses; i++){
        if(std::rand()%2){
            clientsEnMoins++;
            this->clients_en_attente++;
        }
    }

    this->clients_courses-=clientsEnMoins;
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
    if (this->clients_en_attente==0)
        return 0;

    /*On initialise une liste des caisses ouvertes, ainsi que le nombre de caisses ouvertes*/
    vector<int> caisseOuvertes = this->get_caisses_ouvertes();
    int nbCaissesOuvertes = caisseOuvertes.size();

    /*On renvoie 0 s'il y a aucune caisse ouverte*/
    if (nbCaissesOuvertes==0)
        return 0;

    /*On initialise une variable pour choisir une caisse ouverte aléatoire*/
    int caisseOuverteAleatoire;

    /*On itère sur tout les clients en attente, */
    for(int i=0; i<this->clients_en_attente; i++){

        /*On choisit une caisse ouverte aléatoire*/
        caisseOuverteAleatoire = caisseOuvertes[rand()%nbCaissesOuvertes];

        /*On ajoute le client à la caisse aléatoire choisi*/
        this->caisses[caisseOuverteAleatoire]->add_client_en_caisse();
    }

    /*
    Tout les clients en attente on été placé, on remet le nombre de clients en attente à 0
    et on renvoie 1.
    */
    this->clients_en_attente=0;
    return 1;
}

void Jeu::ouvrir_caisse(int n){
    caisses[n]->ouvrir_caisse();
}

void Jeu::fermer_caisse(int n){
    caisses[n]->fermer_caisse();
}

vector<int> Jeu::get_caisses_ouvertes(){
    vector<int> caisse_ouvertes;

    for(int i=0;i<NB_CAISSES; i++){
        if(caisses[i]->est_Ouverte()){
            caisse_ouvertes.push_back(i);
        }
    }
    return caisse_ouvertes;
}


void Jeu::facturation(){

    vector<int> caisse_ouvertes = get_caisses_ouvertes();
    uint16_t nb_caisses_ouvertes = caisse_ouvertes.size();
    
    this->devis->caisse_ouverte=nb_caisses_ouvertes;
    this->devis->clients_en_attente=this->clients_en_attente;
    
    this->credits -= caisse_ouvertes.size()*PRIX_PAR_CAISSE_OUVERTE;
    this->credits -= this->clients_en_attente*PRIX_PAR_CLIENT_EN_ATTENTE;

    for(int num_caisse : caisse_ouvertes){
        this->devis->clients_en_caisse+=this->caisses[num_caisse]->get_clients_en_caisse();
        this->credits -= caisses[num_caisse]->get_clients_en_caisse()*PRIX_PAR_CLIENT_EN_CAISSE;
    }

    this->credits -= PRIX_TOUR_DE_JEU;
}

void Jeu::affiche_etats_caisses(){

    for(int i=0; i<NB_CAISSES; i++){
        cout << this->caisses[i]->get_changement() << " Caisse " << i+1 << ":\t"<< this->caisses[i]->affiche_info() << endl;
    }   
}

void Jeu::affiche_budget(){
    cout << "Budget: " << this->credits << " crédits." << endl;
}

void Jeu::sortir_clients_des_caisses(){
    vector<int> caisse_ouvertes = get_caisses_ouvertes();
    if(caisse_ouvertes.size()==0){
        return; 
    }

    for(int num_caisse : caisse_ouvertes){
        if(this->caisses[num_caisse]->get_clients_en_caisse()==0){
            continue;
        }
        this->caisses[num_caisse]->sortir_client();
    }

}

void Jeu::affiche_position_clients(){

    vector<int> caisse_ouvertes = get_caisses_ouvertes();
    int clients_en_caisses = 0;
    
    for(int num_caisse: caisse_ouvertes){
        clients_en_caisses += this->caisses[num_caisse]->get_clients_en_caisse();
    }
    cout << "Clients dans l'hypermarché: " << this->clients_courses << ", en attente de caisse: " << this->clients_en_attente << " et aux caisses: " << clients_en_caisses << ".\n";
}

int Jeu::actions_sur_caisse(){

    string choix;

    while(true){

        cout << endl;
        cout << "Action sur les caisses ..." << endl;
        cout << "Choisir une caisse à changer[C], Passer et appliquer tout les changements[P] :";
        getline(cin, choix);
        
        if (!choix.empty() && choix[choix.length()-1] == '\n'){
            choix.erase(choix.length()-1);
        }

        if(cin.fail()){
            cout << "Erreur dans la saisie du choix, veuillez réessayer." << endl;
            cin.clear();
            continue;
        }

        if(choix.length()>=2){
            cout << "Veuillez rentrez une seule lettre." << endl;
            cin.clear();
            continue;
        }
        
        for(auto & c: choix) c = toupper(c);

        if(choix == "C"){
            int choix_num_caisse=0;
            string str_choix_num_caisse;

            while(true){
                cout << "Veuillez choisir la caisse à ouvrir/fermer[1-10] : ";
                getline(cin, str_choix_num_caisse);
                
                try{
                    choix_num_caisse=stoi(str_choix_num_caisse);
                    if(choix_num_caisse<=NB_CAISSES && choix_num_caisse>=0){
                        cout << "choix numéro de caisse: " << choix_num_caisse << endl;
                        break;
                    }
                    cout << "Veuillez entrer un nombre entre 0 et 10" << endl;
                }catch (exception &err){
                    cout << "Veuillez entrer un nombre." << endl;
                }
            }
            this->caisses[choix_num_caisse-1]->changer_etat();
            return 0;

        }
        else if(choix == "P"){
            return 1;
        }
        else{
            cout << "Veuillez choisir \"C\" ou \"P\"" << endl;
            return 0;
        }

    }

}

void Jeu::changer_caisses(){
    for(int i=0; i<NB_CAISSES; i++){
        if (this->caisses[i]->a_changer()){
            this->caisses[i]->changer_caisse();
            this->credits -= PRIX_OUVERTURE_FERMETURE_CAISSE;
            this->devis->ouverture_fermeture_de_caisse++;

            if(!this->caisses[i]->est_Ouverte()){
                this->clients_en_attente+=this->caisses[i]->sortir_tout_les_clients();
            }
            this->caisses[i]->reset_changement();
        }
    }
}

bool Jeu::hypermarche_est_vide(){

    if(this->clients_courses>0)
        return false;

    if(this->clients_en_attente>0)
        return false;

    
    for(int i=0; i<NB_CAISSES; i++){
        if (this->caisses[i]->get_clients_en_caisse()>0){
            return false;
        }
    }

    this->hypermarche_vide = true;
    return true;
}

void Jeu::reset_devis(){
    this->devis->clients_en_caisse=0;
    this->devis->caisse_ouverte=0;
    this->devis->clients_en_attente=0;
    this->devis->ouverture_fermeture_de_caisse=0;
}

void Jeu::affiche_devis(){

    int totalOuvertureFermeture = this->devis->ouverture_fermeture_de_caisse*PRIX_OUVERTURE_FERMETURE_CAISSE;
    int totalCaisseOuverte = this->devis->caisse_ouverte*PRIX_PAR_CAISSE_OUVERTE;
    int totalClientsEnAttente = this->devis->clients_en_attente*PRIX_PAR_CLIENT_EN_ATTENTE;
    int totalClientsEnCaisse = this->devis->clients_en_caisse*PRIX_PAR_CLIENT_EN_CAISSE;

    int total = 1+totalOuvertureFermeture+totalCaisseOuverte+totalClientsEnAttente+totalClientsEnCaisse;

    cout << "-----------------------------------------------------------------" << endl;
    
    cout << "|\t\t\t\t\t\t\tPrix\t|" << endl;
    
    cout << "|\t\t\t\t\t\t\t\t|" << endl;

    cout << "| ouverture/fermetures de caisses :\t" \
    << this->devis->ouverture_fermeture_de_caisse \
    << "  x  " << PRIX_OUVERTURE_FERMETURE_CAISSE << "cr\t= " \
    << totalOuvertureFermeture << "cr\t|" << endl;

    cout << "| caisse(s) ouverte(s) : \t\t" \
    << this->devis->caisse_ouverte \
    << "  x  " << PRIX_PAR_CAISSE_OUVERTE << "cr\t= " \
    << totalCaisseOuverte << "cr\t|" << endl;

    cout << "| clients en attente :\t\t\t" \
    << this->devis->clients_en_attente \
    << "  x  " << PRIX_PAR_CLIENT_EN_ATTENTE << "cr\t= " \
    << totalClientsEnAttente << "cr\t|" << endl;

    cout << "| clients en caisse :\t\t\t" \
    << this->devis->clients_en_caisse \
    << "  x  " << PRIX_PAR_CLIENT_EN_CAISSE << "cr\t= " \
    << totalClientsEnCaisse << "cr\t|" << endl;

    cout << "| Tour:\t\t\t\t\t\t\t  1cr\t|" << endl;

    cout << "|\t------------------------------------------------\t|" << endl;

    cout << "| Total:\t\t\t\t\t\t  " << total << "cr\t|" << endl;

    cout << "|\t\t\t\t\t\t\t\t|" << endl;

    cout << "-----------------------------------------------------------------" << endl;
}