#include <iostream>
#include "Hypermarche.hpp"
#include "Scoreboard.hpp"

int main() {
    // Affichage de l'accueil
    std::cout << "Bienvenue dans le jeu \"Aux commandes de votre hypermarche\" !" << std::endl;
    std::cout << "Le but du jeu est de gerer un hypermarche qui va bientot fermer et de faire sortir tous les clients." << std::endl;
    std::cout << "A chaque tour de jeu, vous pouvez ouvrir ou fermer les caisses de l'hypermarche." << std::endl;
    std::cout << "Les clients ont une probabilite de 50% de passer en caisse." << std::endl;
    std::cout << "Ils choisissent aleatoirement une caisse ouverte, ou attendent qu'une caisse s'ouvre s'il n'y en a pas." << std::endl;
    std::cout << "Chaque caisse ouverte fait diminuer sa file d'un client s'il n'est pas vide." << std::endl;
    std::cout << "Chaque tour de jeu vous coute 1 credit, chaque ouverture/fermeture de caisse vous coute 2 credits," << std::endl;
    std::cout << "chaque caisse ouverte vous coute 3 credits, chaque client en attente de caisse vous coute 2 credits (mcontentement)," << std::endl;
    std::cout << "chaque client qui attend en caisse vous coute 1 credit (impatience)." << std::endl;
    std::cout << "Votre budget de depart est de 1000 credits. Bonne chance !" << std::endl;

    // Initialisation de l'hypermarche et du scoreboard
    Hypermarche hypermarche;
    Scoreboard scoreboard;

    // Boucle de jeu
    while (!hypermarche.estFermee()) {
        hypermarche.jouerTour();
    }

    // Fin du jeu, affichage du score
    int score = hypermarche.getBudget();
    std::cout << "Le jeu est termine. Votre score est de " << score << " credits." << std::endl;

    // Ajout du score au scoreboard si il est suffisamment eleve
    if (scoreboard.ajouterScore(score)) {
        std::string nomJoueur;
        std::cout << "Felicitation ! Vous avez atteint l'un des 10 meilleurs scores." << std::endl;
        std::cout << "Saisissez votre nom pour l'enregistrer : ";
        std::getline(std::cin, nomJoueur);
        scoreboard.enregistrerScore(nomJoueur, score);
    }

    // Affichage des meilleurs scores
    std::cout << "Meilleurs scores :" << std::endl;
    scoreboard.afficherScores();

    return 0;
}
