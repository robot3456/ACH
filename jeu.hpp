#include <stdint.h>
#include <string>
#include <vector>

#include "caisse.hpp"

using namespace std;

#define NB_CAISSES 10

class jeu
{
private:

    int credits;
    bool hypermarche_vide;
    
    uint16_t clients_courses;
    uint16_t clients_en_attente;
    uint16_t nombre_tours_joues;
    
    caisse *caisses[NB_CAISSES];
    char changements_caisse[NB_CAISSES];

    vector<int> get_caisses_ouvertes();
    string formater_changement(char c);


public:

    jeu();

    bool getHypermarcheVide();
    void setHypermarcheVide(bool state);

    bool hypermarche_est_vide();

    int getCredits();

    void reset();

    int clients_vers_caisse();
    void sortir_clients_des_caisses();

    void ouvrir_caisse(int n);
    void fermer_caisse(int n);

    void facturation();

    void affiche_etats_caisses();
    void affiche_budget();
    void affiche_position_clients(); 

    int actions_sur_caisse();
    void changer_caisses();
};
