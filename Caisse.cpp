#include "Caisse.hpp"
#include <cstdint>
#include <iostream>
#include <string>

#define CLIENT_EN_CAISSE_DEBUT 0

#define MAX_CLIENTS_A_AFFICHER 20

using namespace std;

Caisse::Caisse(){
    this->clients_en_caisse=CLIENT_EN_CAISSE_DEBUT;
    this->ouverte=false;
    this->etat_a_changer=false;
}

void Caisse::sortir_client(){
    this->clients_en_caisse--;
}

string Caisse::affiche_info(){   
    if(!this->ouverte){
        return "Fermée";
    }

    string info = "Ouverte | Clients :";

    if(this->clients_en_caisse <= MAX_CLIENTS_A_AFFICHER){
        for(int i=0; i<this->clients_en_caisse; i++){
            info.append("*");
        }
        return info;
    }else{

        for(int i=0; i<MAX_CLIENTS_A_AFFICHER; i++){
            info.append("*");
        }

        if(this->clients_en_caisse==MAX_CLIENTS_A_AFFICHER){
            return info;
        }

        info.append("(+");
        info.append(to_string(this->clients_en_caisse-MAX_CLIENTS_A_AFFICHER));
        info.append(")");

        return info;
    }
}

bool Caisse::est_Ouverte(){
    return ouverte;
}

void Caisse::add_client_en_caisse(){
    this->clients_en_caisse++;
}

void Caisse::ouvrir_caisse(){
    this->ouverte=true;
}

void Caisse::fermer_caisse(){
    this->ouverte=false;
}

int Caisse::get_clients_en_caisse(){
    return this->clients_en_caisse;
}

void Caisse::reset_clients_en_caisse(){
    this->clients_en_caisse=0;
}


void Caisse::changer_etat(){
    this->etat_a_changer=!this->etat_a_changer;
}

void Caisse::reset_changement(){
    this->etat_a_changer=false;
}

string Caisse::get_changement(){
    if(this->etat_a_changer==false){
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

bool Caisse::a_changer(){
    return this->etat_a_changer;
}

void Caisse::changer_caisse(){
    this->ouverte = !this->ouverte;
}

int Caisse::sortir_tout_les_clients(){
    uint16_t clients_sortis = this->clients_en_caisse;
    this->clients_en_caisse=0;
    return clients_sortis;
}