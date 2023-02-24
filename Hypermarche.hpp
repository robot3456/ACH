#ifndef HYPERMARCHE_H
#define HYPERMARCHE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Déclaration des énumérations
enum class CaisseEtat { FERME, OUVERT };
enum class ClientEtat { ATTENTE, EN_CAISSE };

// Déclaration des classes
class Caisse;
class Client;
class Hypermarche;

// Déclaration des fonctions
void afficher_accueil();
void afficher_etat_hypermarche(Hypermarche& hypermarche);
void choix_clients(Hypermarche& hypermarche);

// Déclaration des variables globales
const int NBR_CAISSES = 10;
const int NBR_CLIENTS = 100;
const int COUT_TOUR_JEU = 1;
const int COUT_OUVERTURE_FERMETURE_CAISSE = 2;
const int COUT_CAISSE_OUVERTE = 3;
const int COUT_CLIENT_ATTENTE_CAISSE = 2;
const int COUT_CLIENT_EN_CAISSE = 1;

// Déclaration de la classe Caisse
class Caisse {
public:
  Caisse();
  bool est_fermee() const;
  bool est_ouverte() const;
  void ouvrir();
  void fermer();
  void retirer_client();
  bool est_vide() const;
  int nbr_clients_en_attente() const;
  int nbr_clients_en_caisses() const;
  void ajouter_client(Client& client);
private:
  CaisseEtat etat_;
  int nbr_clients_en_attente_;
  std::vector<Client> clients_en_caisses_;
};

// Déclaration de la classe Client
class Client {
public:
  Client(int id);
  int id() const;
  ClientEtat etat() const;
  void passer_en_attente();
  void passer_en_caisses(Caisse& caisse);
private:
  int id_;
  ClientEtat etat_;
  Caisse* caisse_;
};

// Déclaration de la classe Hypermarche
class Hypermarche {
public:
  Hypermarche();
  int budget() const;
  int nbr_clients_en_attente() const;
  int nbr_clients_en_caisses() const;
  int nbr_clients_sortis() const;
  void inc_nbr_clients_sortis();
  void ajouter_client_en_attente(Client& client);
  void retirer_client_en_attente(Client& client);
  void ajouter_caisse(Caisse& caisse);
  void retirer_caisse(Caisse& caisse);

  std::vector<Caisse>& caisses();
  std::vector<Client>& clients();
private:
  int budget_;
  int nbr_clients_sortis_;
  std::vector<Caisse> caisses_;
  std::vector<Client> clients_;
};

#endif // HYPERMARCHE_H
