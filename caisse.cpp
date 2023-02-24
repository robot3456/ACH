#include "caisse.hpp"
#include <iostream>
#include <string>

#define CLIENT_EN_CAISSE_DEBUT 0

#define MAX_CLIENTS_A_AFFICHER 10

using namespace std;

caisse::caisse()
{
    this->clients_en_caisse=CLIENT_EN_CAISSE_DEBUT;
    this->ouverte=false;
    this->etat_a_changer=false;
}

void caisse::sortir_client()
{
    this->clients_en_caisse--;
}

string caisse::affiche_info()
{   
    if(!this->ouverte)
    {
        return "Fermée";
    }

    string info = "Ouverte | Clients :";

    if(this->clients_en_caisse <= MAX_CLIENTS_A_AFFICHER)
    {
        for(int i=0; i<this->clients_en_caisse; i++)
        {
            info.append("*");
        }
        return info;
    }else{

        for(int i=0; i<MAX_CLIENTS_A_AFFICHER; i++)
        {
            info.append("*");
        }

        if(this->clients_en_caisse==MAX_CLIENTS_A_AFFICHER)
        {
            return info;
        }

        info.append("(+%d)",this->clients_en_caisse-MAX_CLIENTS_A_AFFICHER);
        return info;
    }
}

bool caisse::isOuverte()
{
    return ouverte;
}

void caisse::add_client_en_caisse()
{
    this->clients_en_caisse++;
}

void caisse::ouvrir_caisse()
{
    this->ouverte=true;
}

void caisse::fermer_caisse()
{
    this->ouverte=false;
}

int caisse::get_clients_en_caisse()
{
    return this->clients_en_caisse;
}

void caisse::changer_etat()
{
    this->etat_a_changer=!this->etat_a_changer;
}

void caisse::reset_changement()
{
    this->etat_a_changer=false;
}

string caisse::get_changement()
{
    if(this->etat_a_changer==this->ouverte)
    {
        return "[\033[1;33m-\033[0m]";
    }
    else
    {
        if(this->ouverte)
        {
            return "[\033[1;31mF\033[0m]";
        }
        else {
            return "[\033[1;32mO\033[0m]";
        }
    }
}