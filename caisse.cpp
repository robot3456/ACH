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
