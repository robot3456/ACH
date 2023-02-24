#include <stdint.h>
#include <vector>

#include "caisse.hpp"

using namespace std;

class jeu
{
private:

    uint16_t credits;
    
    uint16_t clients_course;
    uint16_t clients_en_attente;
    
    caisse *caisses[10];

    vector<int> get_caisses_ouvertes();

public:

    jeu();
    int clients_vers_caisse();
    void sortir_clients_des_caisses();

    void ouvrir_caisse(int n);
    void fermer_caisse(int n);

    void facturation();

    void affiche_etats_caisses();
    void affiche_budget();
};
