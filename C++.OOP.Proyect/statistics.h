#pragma once

struct Statistics
{
    int gamesPlayed = 0;
    int player1Wins = 0;
    int player2Wins = 0;
    int botWins = 0;
};

Statistics loadStatistics()
{
    ifstream file("gameStatistics.json");

    json j;
    file >> j;

    Statistics stats;

    stats.gamesPlayed = j["gamesPlayed"];
    stats.player1Wins = j["player1Wins"];
    stats.player2Wins = j["player2Wins"];
    stats.botWins = j["botWins"];

    return stats;
}

void saveStatistics(const Statistics& stats)
{
    json j;

    j["gamesPlayed"] = stats.gamesPlayed;
    j["player1Wins"] = stats.player1Wins;
    j["player2Wins"] = stats.player2Wins;
    j["botWins"] = stats.botWins;

    ofstream file("gameStatistics.json");

    file << setw(4) << j;
}

