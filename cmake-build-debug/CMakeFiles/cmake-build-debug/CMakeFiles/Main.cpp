
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
// For shuffling teams
using namespace std;

// Defines structure for team
struct FootballTeam {
    string teamName;
    string localTown;
    string homeStadium;
};

struct Match {
    string homeTeam;
    string awayTeam;
    string stadium;
    string town;
    int leg; // 1 for home, 2 for away
    int weekend;
};

// Function to read teams from csv
vector<FootballTeam> getTeamsFromCSV(const string& filename) {
    vector<FootballTeam> teams;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return teams;
    }

    string line;

    // Skip the header line
    getline(file, line);

    // Read the CSV line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string teamName, localTown, homeStadium;

        // Assuming the CSV format is: teamName,localTown,homeStadium
        getline(ss, teamName, ',');
        getline(ss, localTown, ',');
        getline(ss, homeStadium, ',');

        // Add the team to the list
        teams.push_back({teamName, localTown, homeStadium});
    }

    file.close();
    return teams;
}

// Function to generate fixtures
vector<Match> generateFixtures(const vector<FootballTeam>& teams) {
    vector<Match> fixtures;
    int weekend = 1;

    // Generate matches (home and away)
    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            // Match 1: Team[i] plays at home
            fixtures.push_back({teams[i].teamName, teams[j].teamName, teams[i].homeStadium, teams[i].localTown, 1, 0});

            // Match 2: Team[j] plays at home
            fixtures.push_back({teams[j].teamName, teams[i].teamName, teams[j].homeStadium, teams[j].localTown, 2, 0});
        }
    }

    // Sort fixtures such that same town teams play later (to enforce rule 1)
    stable_sort(fixtures.begin(), fixtures.end(), [&teams](const Match& a, const Match& b) {
        return a.town != b.town; // Non-same town matches come first
    });

    // Schedule matches 4 teams per weekend (2 matches)
    for (size_t i = 0; i < fixtures.size(); i += 2) {
        fixtures[i].weekend = weekend;
        if (i + 1 < fixtures.size()) {
            fixtures[i + 1].weekend = weekend;
        }
        weekend++;
    }

    return fixtures;
}
