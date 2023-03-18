#include "Devis.hpp"
#include <iostream>

using namespace std;

/**
 * @brief Constructeur par défaut de la classe Devis
 * 
 */
Devis::Devis(){
    resetDevis();
}

/**
 * @brief Réinitialise les attributs de la classe "Devis" et les met à 0
 * 
 */
void Devis::resetDevis(){
    this->clientsEnCaisse=0;
    this->caisseOuverte=0;
    this->clientsEnAttente=0;
    this->ouvertureFermetureDeCaisse=0;
}

/**
 * @brief Affiche le devis sous forme d'un tableau
 * 
 */
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

/**
 * @brief Calcul le nombre total de crédits à payer pour le tour actuel
 * 
 * @return int Total des crédits à payer
 */
int Devis::getTotal(){
    int total=0;

    total+=this->caisseOuverte*PRIX_PAR_CAISSE_OUVERTE;
    total+=this->clientsEnCaisse*PRIX_PAR_CLIENT_EN_CAISSE;
    total+=this->clientsEnAttente*PRIX_PAR_CLIENT_EN_ATTENTE;
    total+=this->ouvertureFermetureDeCaisse*PRIX_OUVERTURE_FERMETURE_CAISSE;
    total+=PRIX_TOUR_DE_JEU;

    return total;
}

/**
 * @brief Calcul le devis à payer à partir des des variables du jeu
 * 
 * @param caisses Liste des caisses
 * @param nbCaisses Nombre de caisses dans la liste. Représente le nombre total de caisses dans l'hypermarché
 * @param clientsEnAttente Nombre de clients en attente au tour actuel
 */
void Devis::calculerDevis(Caisse *caisses[NB_CAISSES], int nbCaisses, int clientsEnAttente){

    // Remise à zero de touts les attributs de classe de l'instance en cours
    this->resetDevis();

    // Boucle qui itère sur chaque caisse
    for(int i=0; i<NB_CAISSES; i++){

        // Si la caisse d'indice i est ouverte, on incrémente "caisseOuverte"
        if(caisses[i]->estOuverte())
            this->caisseOuverte++;
        // Si l'état de la caisse d'indice i est à changer, on incrémente la valeur de "ouvertureFermetureDeCaisse"
        if(caisses[i]->aChanger()){
            this->ouvertureFermetureDeCaisse++;

            /* On incrémente aussi caisseOuverte si on ouvre une caisse fermé */
            if (!caisses[i]->estOuverte())
                this->caisseOuverte++;
        }
            

        // Calcul du nombre total de clients en caisse
        this->clientsEnCaisse+=caisses[i]->getClientsEnCaisse();
    }

    this->clientsEnAttente=clientsEnAttente;

}