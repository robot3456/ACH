#include "Caisse.hpp"

#define PRIX_PAR_CAISSE_OUVERTE 3
#define PRIX_PAR_CLIENT_EN_ATTENTE 2
#define PRIX_PAR_CLIENT_EN_CAISSE 1
#define PRIX_OUVERTURE_FERMETURE_CAISSE 2
#define PRIX_TOUR_DE_JEU 1

#define NB_CAISSES 10

class Devis{

private:

    int ouvertureFermetureDeCaisse;
    int clientsEnAttente;
    int caisseOuverte;
    int clientsEnCaisse;

public:

    Devis();
    ~Devis();

    void resetDevis();

    /**
     * @brief Affich le devis du tour actuel avec les prix à payer
     * 
     */
    void afficheDevis();
    
    int getTotal();

    void calculerDevis(Caisse *caisses[], int nbCaisses, int clientsEnAttente);

};