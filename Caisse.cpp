#include "Caisse.hpp"

#define CLIENT_EN_CAISSE_DEBUT 0

using namespace std;

/**
 * @brief Constructeur de l'objet Caisse. Contient les clients dans une caisse
 * l'etat de la caisse : ouverte (true) / fermée (false)
 * et le flag etatAChanger qui indique si l'etat de la caisse doit être changé au prochain tour
 */
Caisse::Caisse(){
    this->clientsEnCaisse=CLIENT_EN_CAISSE_DEBUT;
    this->ouverte=false;
    this->etatAChanger=false;
}

/**
 * @brief Supprime un client de la caisse
 */
void Caisse::sortirClient(){
    this->clientsEnCaisse--;
}

/**
 * @brief Utilisée pour l'affichage graphique de l'état de la caisse au tour actuel
 * et le nombre de clients en caisse 
 * 
 * @return string "[Fermée]" (en rouge)   -- OU --  
 * "[Ouverte]" (en vert) + "| Clients :" + un nombre d'étoiles correspondant au nombre de clients en caisse + nombre de clients
 */
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


/**
 * @brief Indique l'état de l'attribut de classe "ouverte"
 * 
 * @return true si la caisse est ouverte
 * @return false si la caisse est fermée
 */
bool Caisse::estOuverte(){
    return ouverte;
}

/**
 * @brief Ajoute un client dans 1 caisse
 * 
 */
void Caisse::ajouterClientEnCaisse(){
    this->clientsEnCaisse++;
}

/**
 * @brief Utilisée au moment d'ouvrir une caisse
 * Change l'état de l'attribut de classe "ouverte" à true
 */
void Caisse::ouvrirCaisse(){
    this->ouverte=true;
}

/**
 * @brief Utilisée au moment de fermer une caisse
 * Change l'état de l'attribut de classe "ouverte" à false
 */
void Caisse::fermerCaisse(){
    this->ouverte=false;
}

/**
 * @brief Getter du nombre de clients dans 1 caisse
 * 
 * @return int nombre de clients contenus dans 1 caisse
 */
int Caisse::getClientsEnCaisse(){
    return this->clientsEnCaisse;
}

/**
 * @brief Réinitialise le nombre de clients contenus dans 1 caisse à 0
 * 
 */
void Caisse::resetClientsEnCaisse(){
    this->clientsEnCaisse=0;
}

/**
 * @brief Inverse l'état de "etatAChanger" afin de savoir si la caisse 
 * doit ouvrir ou fermer au prochain tour 
 */
void Caisse::changerEtat(){
    this->etatAChanger=!this->etatAChanger;
}

/**
 * @brief Réinitialise l'état de "etat_a_changer" à false (valeur par défaut)
 * 
 */
void Caisse::resetChangement(){
    this->etatAChanger=false;
}

/**
 * @brief Permet d'obtenir une chaîne de caractères qui indique si l'état de la caisse va changer au prochain tour 
 * Contient :  
 * "[-]" (Etat identique au tour actuel )
 * "[F]" (Fermée au tour suivant)
 * "[O]" (Ouverte au tour suivant)
 * 
 * @return string "[-]" OU "[F]" OU "[O]"
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

/**
 * @brief Getter de la valeur de "etatAChanger"
 * 
 * @return true si la caisse doit changer d'état au prochain tour
 * @return false si la caisse conserve son etat actuel au prochain tour
 */
bool Caisse::aChanger(){
    return this->etatAChanger;
}

/**
 * @brief Inverse l'état (d'ouverte à fermée / de fermée à ouverte) de la caisse actuelle
 * 
 */
void Caisse::changerCaisse(){
    this->ouverte = !this->ouverte;
}

/**
 * @brief Obtenir le nombre de clients totaux sortis d'une caisse (contenus dans l'attribut "clientsSortis")
 * 
 * @return int nombre de clients sortis de la caisse
 */
int Caisse::sortirTousLesClients(){
    uint16_t clientsSortis = this->clientsEnCaisse;
    this->clientsEnCaisse=0;
    return clientsSortis;
}