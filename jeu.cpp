#include "jeu.hpp"

#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

#define STARTING_CREDITS 1000
#define STARTING_CLIENTS_EN_COURSE 100
#define STARTING_CLIENTS_EN_ATTENTE 0

#define PRIX_PAR_CAISSE_OUVERTE 3
#define PRIX_PAR_CLIENT_EN_ATTENTE 2
#define PRIX_PAR_CLIENT_EN_CAISSE 1
#define PRIX_OUVERTURE_FERMETURE_CAISSE 2
#define PRIX_TOUR_DE_JEU 1

jeu::jeu()
{
    //initialisation par défaut du jeu
    this->credits=STARTING_CREDITS;
    this->clients_courses=STARTING_CLIENTS_EN_COURSE;
    this->clients_en_attente=STARTING_CLIENTS_EN_ATTENTE;

    for(int i=0; i<NB_CAISSES; i++)
    {
        this->caisses[i] = new caisse();
        this->changements_caisse[i] = '-';
    }

}

int jeu::clients_vers_caisse(){

    if(clients_courses==0){ return 0; }  //on fait rien si pas de clients qui font des course
    if(clients_courses<0){ return -1; }  //erreur si nombre de clients négatif

    //on décide combien de clients vont aller en caisse

    std::srand(time(NULL));
    
    uint16_t clients_a_placer = 0;

    for(int i=0; i<this->clients_courses; i++)//on itère sur tout les clients
    {
        if(std::rand()%2) //1 chance sur 2 d'aller en caisse, =0 ou 1, si 1 on le met à placer
        {
            clients_a_placer++;
        }
    }

    //on enlève les clients à placer des clients qui font les courses
    this->clients_courses -= clients_a_placer;

    //on créer une liste des caisses ouvertes

    vector<int> caisse_ouvertes = this->get_caisses_ouvertes();
    
    //si aucune caisse ouverte alors tout les clients à placer sont mis en attente
    if(caisse_ouvertes.size()==0)
    {
        this->clients_en_attente+=clients_a_placer;
        return 1; //fonction s'execute avec succès
    }

    int nb_caisse_ouvertes = caisse_ouvertes.size();

    for(int i=0; i<clients_a_placer; i++)
    {
        this->caisses[caisse_ouvertes[rand()%nb_caisse_ouvertes]]->add_client_en_caisse();
    }

    return 1;

}

void jeu::ouvrir_caisse(int n)
{
    caisses[n]->ouvrir_caisse();
}

void jeu::fermer_caisse(int n)
{
    caisses[n]->fermer_caisse();
}

vector<int> jeu::get_caisses_ouvertes()
{
    vector<int> caisse_ouvertes;

    for(int i=0;i<NB_CAISSES; i++)
    {
        if(caisses[i]->isOuverte())
        {
            caisse_ouvertes.push_back(i);
        }
    }
    return caisse_ouvertes;
}

void jeu::facturation()
{
    //Facturation des caisses ouvertes
    vector<int> caisse_ouvertes = get_caisses_ouvertes();

    uint16_t nb_caisses_ouvertes = caisse_ouvertes.size();

    this->credits -= caisse_ouvertes.size()*PRIX_PAR_CAISSE_OUVERTE;

    //Facturation des clients en attente de caisse
    this->credits -= this->clients_en_attente*PRIX_PAR_CLIENT_EN_ATTENTE;

    //Facturation des clients en caisse
    for(int num_caisse : caisse_ouvertes)
    {
        this->credits -= caisses[num_caisse]->get_clients_en_caisse()*PRIX_PAR_CLIENT_EN_CAISSE;
    }

    //Facturation du tour du jeu
    this->credits -= PRIX_TOUR_DE_JEU;

}

void jeu::affiche_etats_caisses()
{
    for(int i=0; i<NB_CAISSES; i++)
    {
        cout << this->caisses[i]->get_changement() << " Caisse " << i+1 << ":\t"<< this->caisses[i]->affiche_info() << endl;
    }   
}

void jeu::affiche_budget()
{
    cout << "Budget: " << this->credits << " crédits." << endl;
}

void jeu::sortir_clients_des_caisses()
{
    vector<int> caisse_ouvertes = get_caisses_ouvertes();
    if(caisse_ouvertes.size()==0)
    {
        return; 
    }

    for(int num_caisse : caisse_ouvertes)
    {
        if(this->caisses[num_caisse]->get_clients_en_caisse()==0)
        {
            continue;
        }
        this->caisses[num_caisse]->sortir_client();
    }

}

void jeu::affiche_position_clients()
{
    vector<int> caisse_ouvertes = get_caisses_ouvertes();
    int clients_en_caisses = 0;
    for(int num_caisse: caisse_ouvertes)
    {
        clients_en_caisses += this->caisses[num_caisse]->get_clients_en_caisse();
    }

    cout << "Clients dans l'hypermarché: " << this->clients_courses << ", en attente de caisse: " << this->clients_en_attente << " et aux caisses: " << clients_en_caisses << ".\n";

}

void jeu::actions_sur_caisse()
{

    string choix;

    while(true)
    {
        cout << "Choisir une caisse à changer[C], Passer et appliquer tout les changements[P] :";
        getline(cin, choix);
        
        if (!choix.empty() && choix[choix.length()-1] == '\n')
        {
            choix.erase(choix.length()-1);
        }

        if(cin.fail())
        {
            cout << "Erreur dans la saisie du choix, veuillez réessayer." << endl;
            cin.clear();
            continue;
        }

        if(choix.length()>=2)
        {
            cout << "Veuillez rentrez une seule lettre." << endl;
            cin.clear();
            continue;
        }
        
        for(auto & c: choix) c = toupper(c);
        cout << "choix : " << choix << endl;
    }
    
}