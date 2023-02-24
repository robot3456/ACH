#include "Scoreboard.hpp"
#include <fstream>
#include <algorithm>

using namespace std;

Scoreboard::Scoreboard() {
    // On initialise le tableau des scores à zéro
    for (int i = 0; i < NB_SCORES; i++) {
        scores[i] = 0;
        names[i] = " ";
    }
}

void Scoreboard::addScore(int score, string name) {
    // On ajoute le score et le nom à la fin des tableaux
    scores[NB_SCORES - 1] = score;
    names[NB_SCORES - 1] = name;

    // On trie les tableaux en ordre décroissant de scores
    for (int i = 0; i < NB_SCORES - 1; i++) {
        for (int j = i + 1; j < NB_SCORES; j++) {
            if (scores[j] > scores[i]) {
                swap(scores[i], scores[j]);
                swap(names[i], names[j]);
            }
        }
    }
}

void Scoreboard::saveScores() {
    ofstream file("scores.txt");
    if (file) {
        for (int i = 0; i < NB_SCORES; i++) {
            file << names[i] << " " << scores[i] << endl;
        }
        file.close();
    }
}

void Scoreboard::loadScores() {
    ifstream file("scores.txt");
    if (file) {
        for (int i = 0; i < NB_SCORES; i++) {
            file >> names[i] >> scores[i];
        }
        file.close();
    }
}

void Scoreboard::printScores() {
    cout << "===== TOP SCORES =====" << endl;
    for (int i = 0; i < NB_SCORES; i++) {
        cout << i + 1 << ". " << names[i] << " - " << scores[i] << endl;
    }
    cout << "======================" << endl;
}
