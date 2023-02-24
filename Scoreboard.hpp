#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <vector>

class Scoreboard {
public:
    Scoreboard(std::string filename, int max_scores);
    void add_score(std::string name, int score);
    void print_scores();
private:
    std::vector<std::pair<std::string, int>> scores_;
    std::string filename_;
    int max_scores_;
    void read_scores();
    void write_scores();
};

#endif // SCOREBOARD_H
