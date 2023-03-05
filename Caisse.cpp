#include "Caisse.hpp"
#include <cstdint>
#include <iostream>
#include <string>

#define CLIENT_EN_CAISSE_DEBUT 0

#define MAX_CLIENTS_A_AFFICHER 20

using namespace std;

Caisse::Caisse(){
    this->clientsEnCaisse=CLIENT_EN_CAISSE_DEBUT;
    this->ouverte=false;
    this->etatAChanger=false;
}

void Caisse::sortirClient(){
    this->clientsEnCaisse--;
}

string Caisse::afficheInfoCaisse(){   
    if(!this->ouverte){
        return "[\033[1;31mFermée\033[0m]";
    }

    string info = "[\033[1;32mOuverte\033[0m] | Clients :";

    if(this->clientsEnCaisse <= MAX_CLIENTS_A_AFFICHER){
        for(int i=0; i<this->clientsEnCaisse; i++){
            info.append("*");
        }
        return info;
    }else{

        for(int i=0; i<MAX_CLIENTS_A_AFFICHER; i++){
            info.append("*");
        }

        if(this->clientsEnCaisse==MAX_CLIENTS_A_AFFICHER){
            return info;
        }

        info.append("(+");
        info.append(to_string(this->clientsEnCaisse-MAX_CLIENTS_A_AFFICHER));
        info.append(")");

        return info;
    }
}

bool Caisse::estOuverte(){
    return ouverte;
}

void Caisse::ajouterClientEnCaisse(){
    this->clientsEnCaisse++;
}

void Caisse::ouvrirCaisse(){
    this->ouverte=true;
}

void Caisse::fermerCaisse(){
    this->ouverte=false;
}

int Caisse::getClientsEnCaisse(){
    return this->clientsEnCaisse;
}

void Caisse::resetClientsEnCaisse(){
    this->clientsEnCaisse=0;
}


void Caisse::changerEtat(){
    this->etatAChanger=!this->etatAChanger;
}

void Caisse::resetChangement(){
    this->etatAChanger=false;
}

string Caisse::getChangement(){
    if(this->etatAChanger==false){
        // Affiche un tiret Jaune
        return "[\033[1;33m-\033[0m]";
    }else{
        if(this->ouverte){
            //Affiche un F en rouge
            return "[\033[1;31mF\033[0m]";
        }else{
            // Affiche un O en vert
            return "[\033[1;32mO\033[0m]";
        }
    }
}

bool Caisse::aChanger(){
    return this->etatAChanger;
}

void Caisse::changerCaisse(){
    this->ouverte = !this->ouverte;
}

int Caisse::sortirTousLesClients(){
    uint16_t clientsSortis = this->clientsEnCaisse;
    this->clientsEnCaisse=0;
    return clientsSortis;
}