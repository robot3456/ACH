#ifndef JEU_HPP
#define JEU_HPP


#include <stdint.h>
#include <string>
#include <vector>

#include "Caisse.hpp"
#include "Devis.hpp"

using namespace std;

#define NB_CAISSES 10
#define STARTING_CREDITS 1000
#define STARTING_CLIENTS_EN_COURSE 100
#define STARTING_CLIENTS_EN_ATTENTE 0


class Jeu{
private:

    int credits;
    bool hypermarcheVide;
    
    uint16_t clientsEnCourses;
    uint16_t clientsEnAttente;
    uint16_t nombreToursJoues;
    
    Caisse *caisses[NB_CAISSES];
    char changementsCaisse[NB_CAISSES];

    string errorMessage;

    Devis devis;

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

    bool actionsSurCaisses();
    void changerCaisses();

    void afficheDevis();

    int mettreClientsEnAttente();
    int metttreClientsEnCaisses();
};


#endif // JEU_HPP