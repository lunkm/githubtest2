#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Score {
    string playerName;
    int score;
};

void saveScore(const Score& score) {
    ofstream file("scoreboard.txt", ios::app);
    if (file.is_open()) {
        file << score.playerName << " " << score.score << endl;
        file.close();
    } else {
        cout << "Unable to open the scoreboard file." << endl;
    }
}

void updateScoreboard(const string& playerName, int points) {
    Score score;
    score.playerName = playerName;
    score.score = points;
    
    saveScore(score);
}

int main() {
    string playerName;
    int points;
    
    cout << "Enter player name: ";
    cin >> playerName;
    
    cout << "Enter points: ";
    cin >> points;
    
    updateScoreboard(playerName, points);
    
    return 0;
}
