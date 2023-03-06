#include "Devis.hpp"
#include <iostream>

using namespace std;

Devis::Devis(){
    this->resetDevis();
}

void Devis::resetDevis(){
    this->clientsEnCaisse=0;
    this->caisseOuverte=0;
    this->clientsEnAttente=0;
    this->ouvertureFermetureDeCaisse=0;
}

void Devis::afficheDevis(){

    int totalOuvertureFermeture = this->ouvertureFermetureDeCaisse*PRIX_OUVERTURE_FERMETURE_CAISSE;
    int totalCaisseOuverte = this->caisseOuverte*PRIX_PAR_CAISSE_OUVERTE;
    int totalClientsEnAttente = this->clientsEnAttente*PRIX_PAR_CLIENT_EN_ATTENTE;
    int totalClientsEnCaisse = this->clientsEnCaisse*PRIX_PAR_CLIENT_EN_CAISSE;

    int total = 1 + totalOuvertureFermeture + totalCaisseOuverte + totalClientsEnAttente + totalClientsEnCaisse ;

    cout << "-----------------------------------------------------------------" << endl;
    
    cout << "|\t\t\t\t\t\t\tPrix\t|" << endl;
    
    cout << "|\t\t\t\t\t\t\t\t|" << endl;

    cout << "| ouverture/fermetures de caisses :\t" \
    << this->ouvertureFermetureDeCaisse \
    << "  x  " << PRIX_OUVERTURE_FERMETURE_CAISSE << "cr\t= " \
    << totalOuvertureFermeture << "cr\t|" << endl;

    cout << "| caisse(s) ouverte(s) : \t\t" \
    << this->caisseOuverte \
    << "  x  " << PRIX_PAR_CAISSE_OUVERTE << "cr\t= " \
    << totalCaisseOuverte << "cr\t|" << endl;

    cout << "| clients en attente :\t\t\t" \
    << this->clientsEnAttente \
    << "  x  " << PRIX_PAR_CLIENT_EN_ATTENTE << "cr\t= " \
    << totalClientsEnAttente << "cr\t|" << endl;

    cout << "| clients en caisse :\t\t\t" \
    << this->clientsEnCaisse \
    << "  x  " << PRIX_PAR_CLIENT_EN_CAISSE << "cr\t= " \
    << totalClientsEnCaisse << "cr\t|" << endl;

    cout << "| Tour:\t\t\t\t\t\t\t  1cr\t|" << endl;

    cout << "|\t------------------------------------------------\t|" << endl;

    cout << "| Total:\t\t\t\t\t\t  " << total << "cr\t|" << endl;

    cout << "|\t\t\t\t\t\t\t\t|" << endl;

    cout << "-----------------------------------------------------------------" << endl;
}

int Devis::getTotal(){
    int total=0;

    total+=this->caisseOuverte*PRIX_PAR_CAISSE_OUVERTE;
    total+=this->clientsEnCaisse*PRIX_PAR_CLIENT_EN_CAISSE;
    total+=this->clientsEnAttente*PRIX_PAR_CLIENT_EN_ATTENTE;
    total+=this->ouvertureFermetureDeCaisse*PRIX_OUVERTURE_FERMETURE_CAISSE;
    total+=PRIX_TOUR_DE_JEU;

    return total;
}

void Devis::calculerDevis(Caisse *caisses[NB_CAISSES], int nbCaisses, int clientsEnAttente){

    this->resetDevis();

    for(int i=0; i<NB_CAISSES; i++){
        if(caisses[i]->estOuverte())
            this->caisseOuverte++;
        
        if(caisses[i]->aChanger())
            this->ouvertureFermetureDeCaisse++;

        this->clientsEnCaisse+=caisses[i]->getClientsEnCaisse();
    }

    this->clientsEnAttente=clientsEnAttente;

}