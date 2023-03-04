#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Score{
private:

    int score;
    fstream scoreFile;

public:

    Score();

    int getScore();
    void setScore(int newScore);

    bool fileExists(string filename);

    void createFile();
    //void createFileIfNotExists();
    void createFileIfNotExists(string filename);

    void Score::writeScoreToFile(string filename);
    string readScoreFromFile(string filename);


};