#include "Caisse.hpp"
#include <cstdint>
#include <iostream>
#include <string>

#define CLIENT_EN_CAISSE_DEBUT 0

using namespace std;

/* Constructeur de l'objec caisse contenant les clients en une caisse
* l'etat de la caisse : ouverte (true) / fermée (false)
* et le flag etat_a_changer si il fuat changer l'etat de la caisse au prochain tour
*/
Caisse::Caisse(){
    this->clientsEnCaisse=CLIENT_EN_CAISSE_DEBUT;
    this->ouverte=false;
    this->etatAChanger=false;
}



/* Supprime un client de la caisse */
void Caisse::sortirClient(){
    this->clientsEnCaisse--;
}

/* Affichage graphique des clients en caisse représentés par des étoiles */
string Caisse::afficheInfoCaisse(){

    // retourne "Fermée" en couleur rouge si la caisse est fermée
    if(!this->ouverte){
        return "[\033[1;31mFermée\033[0m]";
    }

    // "info" contient le texte "Ouverte" en couleur verte + "| Clients :" en couleur normale
    string info = "[\033[1;32mOuverte\033[0m] | Clients :";

    for(int i=0; i<this->clientsEnCaisse; i++){
        info.append("*");
    }

    info.append(" \t(");
    info.append(to_string(this->clientsEnCaisse));
    info.append(")");

    return info;

}

/* Fonction utilisée pour connaître l'état d'une caisse
* retourne la valeur (true/false) contenue dans "ouverte" */
bool Caisse::estOuverte(){
    return ouverte;
}

/* Ajoute un client en caisse */
void Caisse::ajouterClientEnCaisse(){
    this->clientsEnCaisse++;
}

/* Fonction utilisée au moment d'ouvrir une caisse 
* Change l'état de "ouverte" à true */
void Caisse::ouvrirCaisse(){
    this->ouverte=true;
}

/* Fonction utilisée au moment d'ouvrir une caisse 
* Change l'état de "ouverte" à false */
void Caisse::fermerCaisse(){
    this->ouverte=false;
}

/* Retourne le nombre de clients contenus dans 1 caisse */
int Caisse::getClientsEnCaisse(){
    return this->clientsEnCaisse;
}

/* Réinitialise le nombre de clients contenus dans 1 caisse à 0 */
void Caisse::resetClientsEnCaisse(){
    this->clientsEnCaisse=0;
}

/* Inverse l'état de "etat_a_changer" afin de savoir si la caisse 
* doit ouvrir ou fermer au prochain tour 
*/
void Caisse::changerEtat(){
    this->etatAChanger=!this->etatAChanger;
}

/* Réinitialise l'état de "etat_a_changer" à false (valeur par défaut)*/
void Caisse::resetChangement(){
    this->etatAChanger=false;
}

/* Affiche sur le coté gauche du terminal et entre crochets,
* les caisses dont l'état va changer au prochain tour
*/
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

/* Retourne la valeur de "etat a changer" */
bool Caisse::aChanger(){
    return this->etatAChanger;
}
/* Inverse l'état d'ouverture actuel de la caisse */
void Caisse::changerCaisse(){
    this->ouverte = !this->ouverte;
}

/* Retourne le nombre de clients sortis */
int Caisse::sortirTousLesClients(){
    uint16_t clientsSortis = this->clientsEnCaisse;
    this->clientsEnCaisse=0;
    return clientsSortis;
}