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
    void affiche_caisses();

    void ouvrir_caisse(int n);
    void fermer_caisse(int n);

    void facturation();

    void afficher_etats_caisses();
    
};
