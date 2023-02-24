#include "jeu.hpp"

#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

#define NB_CAISSES 10
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
    this->clients_course=STARTING_CLIENTS_EN_COURSE;
    this->clients_en_attente=STARTING_CLIENTS_EN_ATTENTE;

    for(int i=0; i<NB_CAISSES; i++)
    {
        this->caisses[i] = new caisse();
    }

}

int jeu::clients_vers_caisse(){

    if(clients_course==0){ return 0; }  //on fait rien si pas de clients qui font des course
    if(clients_course<0){ return -1; }  //erreur si nombre de clients négatif

    //on décide combien de clients vont aller en caisse

    std::srand(time(NULL));
    
    uint16_t clients_a_placer = 0;

    for(int i=0; i<this->clients_course; i++)//on itère sur tout les clients
    {
        if(std::rand()%2) //1 chance sur 2 d'aller en caisse, =0 ou 1, si 1 on le met à placer
        {
            clients_a_placer++;
        }
    }

    //on enlève les clients à placer des clients qui font les courses
    this->clients_course -= clients_a_placer;

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

void jeu::affiche_caisses()
{
    for(int i=0; i<NB_CAISSES; i++)
    {
        cout << "caisse " << i << endl;
        this->caisses[i]->affiche_info();
    }
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