#include <iostream>

#include "jeu.hpp"

using namespace std;

int main(){

    jeu Jeu;

    Jeu.affiche_caisses();

    Jeu.ouvrir_caisse(3);
    Jeu.ouvrir_caisse(6);

    Jeu.clients_vers_caisse();

    cout << endl << endl;

    Jeu.affiche_caisses();

    return 0;
}