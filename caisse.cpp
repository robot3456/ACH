#include "caisse.hpp"
#include <iostream>

#define CLIENT_EN_CAISSE_DEBUT 0

using namespace std;

caisse::caisse()
{
    this->clients_en_caisse=CLIENT_EN_CAISSE_DEBUT;
    this->ouverte=false;
}

int caisse::sortir_client()
{
    if(this->clients_en_caisse==0){ return 0; }
    if(this->clients_en_caisse<0){ return -1; }
    this->clients_en_caisse--;
    return 1;
}

void caisse::affiche_clients_en_caisse()
{
    cout << "nombre de clients en caisse : " << this->clients_en_caisse << endl;
}


void caisse::affiche_ouverte()
{
    if(this->ouverte) { cout << "caisse ouverte" << endl; }
    else { cout << "caisse fermé" << endl; }
}

void caisse::affiche_info()
{   
    if(this->ouverte)
    {
        cout << "ouverte | ";
    }else{
        cout << "fermée | ";
    }
    cout << this->clients_en_caisse << " clients" << endl;
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