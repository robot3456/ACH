#include "Score.hpp"

#include <iostream>
#include <strings>

Score::Score(){
    int score=0;
}


int Score::getScore(){
    return this->score;
}


void Score::setScore(int newScore){
    this->score = newScore;
}

