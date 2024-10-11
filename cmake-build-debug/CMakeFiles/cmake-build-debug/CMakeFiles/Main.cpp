
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
     return teams;
}
