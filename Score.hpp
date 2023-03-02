#include <string>
#include <fstream>

using namespace std;

class Score{
private:

    int score;
    fstream scoreFile;

public:

    Score();

    int getScore();
    void setScore(int newScore);

    void createFile();
    void createFileIfNotExists();

};