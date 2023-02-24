#include "Hypermarche.hpp"
#include <iostream>

Hypermarche::Hypermarche() {
    // Initialise les rayons de l'hypermarché
    rayons_ = {
        {"Fruits et légumes", Rayon("Fruits et légumes")},
        {"Epicerie salée", Rayon("Epicerie salée")},
        {"Epicerie sucrée", Rayon("Epicerie sucrée")},
        {"Boissons", Rayon("Boissons")},
        {"Hygiène et beauté", Rayon("Hygiène et beauté")}
    };
}

void Hypermarche::ajouterProduitAuRayon(const string& nomRayon, const Produit& produit) {


}

void Hypermarche::afficherRayons() const {


}

void Hypermarche::afficherProduitsDuRayon(const string& nomRayon) const {

}

void Hypermarche::acheterProduit(const string& nomRayon, const string& nomProduit) {

}

void Hypermarche::afficherScoreboard() const {
    scoreboard_.afficherClassement();
}

void Hypermarche::ajouterScore(int score) {
    scoreboard_.ajouterScore(score);
}
