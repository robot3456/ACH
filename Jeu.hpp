#ifndef JEU_HPP
#define JEU_HPP


#include <stdint.h>
#include <string>
#include <vector>

#include "Caisse.hpp"

using namespace std;

#define NB_CAISSES 10

class Jeu{
private:

    int credits;
    bool hypermarcheVide;
    
    uint16_t clientsEnCourses;
    uint16_t clientsEnAttente;
    uint16_t nombreToursJoues;
    
    Caisse *caisses[NB_CAISSES];
    char changementsCaisse[NB_CAISSES];

    struct struct_devis{

        int ouvertureFermetureDeCaisse;
        int clientsEnAttente;
        int caisseOuverte;
        int clientsEnCaisse;

    };

    struct_devis *devis;

    vector<int> getCaissesOuvertes();
    string formaterChangement(char c);

public:

    Jeu();

    bool getHypermarcheVide();
    void setHypermarcheVide(bool state);

    bool hypermarcheEstVide();

    int getCredits();

    void reset();

    int clientsVersCaisse();
    void sortirClientsDesCaisses();

    void ouvrirCaisse(int n);
    void fermerCaisse(int n);

    /**
     * @brief Créer le devis et facture le joueur pour le tour actuel
     * 
     */
    void facturation();

    void afficheEtatsCaisses();
    void afficheBudget();
    void affichePositionClients(); 

    int actionsSurCaisse();
    void changerCaisses();

    void resetDevis();

    /**
     * @brief Affich le devis du tour actuel avec les prix à payer
     * 
     */
    void afficheDevis();

    int mettreClientsEnAttente();
    int metttreClientsEnCaisses();
};


#endif // JEU_HPP