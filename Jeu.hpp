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
    bool hypermarche_vide;
    
    uint16_t clients_courses;
    uint16_t clients_en_attente;
    uint16_t nombre_tours_joues;
    
    Caisse *caisses[NB_CAISSES];
    char changements_caisse[NB_CAISSES];

    struct struct_devis{

        int ouverture_fermeture_de_caisse;
        int clients_en_attente;
        int caisse_ouverte;
        int clients_en_caisse;

    };

    struct_devis *devis;

    vector<int> get_caisses_ouvertes();
    string formater_changement(char c);

public:

    Jeu();

    bool getHypermarcheVide();
    void setHypermarcheVide(bool state);

    bool hypermarche_est_vide();

    int getCredits();

    void reset();

    int clients_vers_caisse();
    void sortir_clients_des_caisses();

    void ouvrir_caisse(int n);
    void fermer_caisse(int n);

    /**
     * @brief Créer le devis et facture le joueur pour le tour actuel
     * 
     */
    void facturation();

    void affiche_etats_caisses();
    void affiche_budget();
    void affiche_position_clients(); 

    int actions_sur_caisse();
    void changer_caisses();

    void reset_devis();

    /**
     * @brief Affich le devis du tour actuel avec les prix à payer
     * 
     */
    void affiche_devis();

    int mettreClientsEnAttente();
    int metttreClientsEnCaisses();
};


#endif // JEU_HPP