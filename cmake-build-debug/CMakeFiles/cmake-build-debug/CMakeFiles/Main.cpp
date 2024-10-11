
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

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
        getline(ss, teamName, ',');
        getline(ss, localTown, ',');
        getline(ss, homeStadium, ',');
        // Add the team to the list
        teams.push_back({teamName, localTown, homeStadium});
    }

    file.close();
    return teams;
}

vector<Match> generateFixtures(const vector<FootballTeam>& teams) {
    vector<Match> fixtures;
    int weekend = 1;

    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            fixtures.push_back({teams[i].teamName, teams[j].teamName, teams[i].homeStadium, teams[i].localTown, 1, 0});
            fixtures.push_back({teams[j].teamName, teams[i].teamName, teams[j].homeStadium, teams[j].localTown, 2, 0});
        }
    }

    stable_sort(fixtures.begin(), fixtures.end(), [&teams](const Match& a, const Match& b) {
        return a.town != b.town;
    });

    for (size_t i = 0; i < fixtures.size(); i += 2) {
        fixtures[i].weekend = weekend;
        if (i + 1 < fixtures.size()) {
            fixtures[i + 1].weekend = weekend;
        }
        weekend++;
    }

    return fixtures;
}

void displayFixtures(const vector<Match>& fixtures) {
    for (const auto& match : fixtures) {
        cout << "Weekend #" << match.weekend << ": " << match.homeTeam << " vs " << match.awayTeam
             << " at " << match.stadium << " in " << match.town
             << " (Leg " << match.leg << ")" << endl;
    }
}

void writeFixturesToCSV(const vector<Match>& fixtures, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    file << "Weekend,Home Team,Away Team,Stadium,Town,Leg" << endl;

    for (const auto& match : fixtures) {
        file << match.weekend << "," << match.homeTeam << "," << match.awayTeam << ","
             << match.stadium << "," << match.town << "," << match.leg << endl;
    }

    file.close();
}

int main() {
    string filename = "C:/Users/elmer/Documents/GitHub/GroupProject/cmake-build-debug/CMakeFiles/cmake-build-debug/CMakeFiles/Teams.csv";
    vector<FootballTeam> teams = getTeamsFromCSV(filename);

    if (teams.empty()) {
        cerr << "No teams loaded. Please check your CSV file." << endl;
        return 1;
    }

    vector<Match> fixtures = generateFixtures(teams);
    displayFixtures(fixtures);
    string fixturesFilename = "Fixtures.csv";
    writeFixturesToCSV(fixtures, fixturesFilename);
    cout << "Fixtures written to " << fixturesFilename << endl;
    return 0;

}