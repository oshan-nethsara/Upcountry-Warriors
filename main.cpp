#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

class Player {
public:
    int registrationNumber;
    string firstName, lastName, dateOfBirth;
    int runsScored;
    vector<int> teamIds;

    Player(int regNum, string fName, string lName, string dob, int runs)
        : registrationNumber(regNum), firstName(fName), lastName(lName), dateOfBirth(dob), runsScored(runs) {}
};

class Team {
public:
    int teamId;
    string teamName;
    vector<int> playerRegistrationNumbers;

    Team(int id, string name) : teamId(id), teamName(name) {}
};

void displayMenu();
void addNewPlayer(vector<Player>& players);
void displayPlayers(const vector<Player>& players);
void manageTeams(vector<Team>& teams, vector<Player>& players);
void addTeam(vector<Team>& teams);
void deleteTeam(vector<Team>& teams, vector<Player>& players);
void editTeam(vector<Team>& teams);
void assignPlayerToTeam(vector<Team>& teams, vector<Player>& players);
void viewTeamDetails(const vector<Team>& teams, const vector<Player>& players);
void searchPlayer(const vector<Player>& players);
void deletePlayer(vector<Player>& players, vector<Team>& teams);
void editPlayer(vector<Player>& players);
bool login();
void logout();
void viewAllTeams(const vector<Team>& teams);
void loadPlayers(vector<Player>& players);
void loadTeams(vector<Team>& teams);
void savePlayers(const vector<Player>& players);
void saveTeams(const vector<Team>& teams);
void loadingScreen();

int main() 
{
    vector<Player> players;
    vector<Team> teams;
    bool loggedIn = false;

    loadingScreen();
    loadPlayers(players);
    loadTeams(teams);

    while (true) {
        if (!loggedIn) {
            loggedIn = login();
            if (!loggedIn) continue;
        }

        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: displayPlayers(players); break;
            case 2: addNewPlayer(players); savePlayers(players); break;
            case 3: manageTeams(teams, players); saveTeams(teams); savePlayers(players); break;
            case 4: searchPlayer(players); break;
            case 5: deletePlayer(players, teams); savePlayers(players); saveTeams(teams); break;
            case 6: editPlayer(players); savePlayers(players); break;
            case 7: logout(); loggedIn = false; break;
            case 8: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n\n";
        }
    }
}

void displayMenu() {
    cout << "\n--- Upcountry Warriors Management System ---\n"
         << "1. Display Players Information\n"
         << "2. Add New Player\n"
         << "3. Manage Teams\n"
         << "4. Search Player\n"
         << "5. Delete Player\n"
         << "6. Edit Player\n"
         << "7. Logout\n"
         << "8. Exit\n"
         << "Enter your choice: ";
}

void addNewPlayer(vector<Player>& players) {
    int regNum, runs;
    string fName, lName, dob;

    cout << "\nEnter Registration Number: ";
    cin >> regNum;

    // Check if the registration number already exists
    auto it = find_if(players.begin(), players.end(), [regNum](const Player& player) {
        return player.registrationNumber == regNum;
    });

    if (it != players.end()) {
        cout << "Registration number already exists! Please enter a unique registration number.\n\n";
        return;
    }

    cout << "Enter First Name: ";
    cin >> fName;
    cout << "Enter Last Name: ";
    cin >> lName;
    cout << "Enter Date of Birth (DD/MM/YYYY): ";
    cin >> dob;
    cout << "Enter Runs Scored: ";
    cin >> runs;

    players.emplace_back(regNum, fName, lName, dob, runs);
    cout << "Player added successfully!\n\n";
}

void displayPlayers(const vector<Player>& players) {
    if (players.empty()) {
        cout << "\nNo players available.\n\n";
        return;
    }

    cout << "\n--- Players Information ---\n"
         << "-------------------------------------------------------------\n"
         << "| RegNum | First Name \t| Last Name \t| Date of Birth | Runs Scored |\n"
         << "-------------------------------------------------------------\n";
    for (const auto& player : players) {
        cout << "| " << player.registrationNumber << " \t| " << player.firstName << " \t| "
             << player.lastName << " \t| " << player.dateOfBirth << " \t| " << player.runsScored << " \t|\n";
    }
    cout << "-------------------------------------------------------------\n\n";
}

void manageTeams(vector<Team>& teams, vector<Player>& players) {
    int choice;
    cout << "\n--- Manage Teams ---\n"
         << "1. Add New Team\n"
         << "2. Assign Player to Team\n"
         << "3. View Team Details\n"
         << "4. View All Teams\n"
         << "5. Delete Team\n"
         << "6. Edit Team\n"
         << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: addTeam(teams); break;
        case 2: assignPlayerToTeam(teams, players); break;
        case 3: viewTeamDetails(teams, players); break;
        case 4: viewAllTeams(teams); break;
        case 5: deleteTeam(teams, players); break;
        case 6: editTeam(teams); break;
        default: cout << "Invalid choice! Try again.\n\n";
    }
}

void addTeam(vector<Team>& teams) {
    string teamName;
    int teamId = teams.size() + 1;

    cout << "Enter Team Name: ";
    cin.ignore();
    getline(cin, teamName);

    teams.emplace_back(teamId, teamName);
    cout << "Team added successfully!\n\n";
}

void deleteTeam(vector<Team>& teams, vector<Player>& players) {
    string teamName;

    cout << "Enter Team Name to delete: ";
    cin.ignore();
    getline(cin, teamName);

    auto teamIt = find_if(teams.begin(), teams.end(), [&teamName](const Team& team) {
        return team.teamName == teamName;
    });

    if (teamIt != teams.end()) {
        for (auto& player : players) {
            player.teamIds.erase(remove(player.teamIds.begin(), player.teamIds.end(), teamIt->teamId), player.teamIds.end());
        }
        teams.erase(teamIt);
        cout << "Team deleted successfully!\n\n";
    } else {
        cout << "Team not found!\n\n";
    }
}

void editTeam(vector<Team>& teams) {
    string oldTeamName, newTeamName;

    cout << "Enter Current Team Name: ";
    cin.ignore();
    getline(cin, oldTeamName);

    auto teamIt = find_if(teams.begin(), teams.end(), [&oldTeamName](const Team& team) {
        return team.teamName == oldTeamName;
    });

    if (teamIt != teams.end()) {
        cout << "Enter New Team Name: ";
        getline(cin, newTeamName);
        teamIt->teamName = newTeamName;
        cout << "Team name updated successfully!\n\n";
    } else {
        cout << "Team not found!\n\n";
    }
}

void assignPlayerToTeam(vector<Team>& teams, vector<Player>& players) {
    int regNum;
    string teamName;

    cout << "Enter Player Registration Number: ";
    cin >> regNum;
    cout << "Enter Team Name: ";
    cin.ignore();
    getline(cin, teamName);

    auto playerIt = find_if(players.begin(), players.end(), [regNum](const Player& player) {
        return player.registrationNumber == regNum;
    });

    if (playerIt != players.end() && playerIt->teamIds.size() < 2) {
        auto teamIt = find_if(teams.begin(), teams.end(), [&teamName](const Team& team) {
            return team.teamName == teamName;
        });

        if (teamIt == teams.end()) {
            cout << "Wrong team name! Please enter a valid team name.\n\n";
        } else {
            playerIt->teamIds.push_back(teamIt->teamId);
            teamIt->playerRegistrationNumbers.push_back(regNum);
            cout << "Player assigned to team successfully!\n\n";
        }
    } else {
        cout << (playerIt == players.end() ? "Player not found!\n\n" : "Player is already assigned to 2 teams!\n\n");
    }
}

void viewTeamDetails(const vector<Team>& teams, const vector<Player>& players) {
    string teamName;

    cout << "Enter Team Name: ";
    cin.ignore();
    getline(cin, teamName);

    auto teamIt = find_if(teams.begin(), teams.end(), [&teamName](const Team& team) {
        return team.teamName == teamName;
    });

    if (teamIt != teams.end()) {
        cout << "\n--- Team Details ---\n"
             << "Team ID: " << teamIt->teamId << "\n"
             << "Team Name: " << teamIt->teamName << "\n"
             << "Players:\n";
        for (const auto& regNum : teamIt->playerRegistrationNumbers) {
            auto playerIt = find_if(players.begin(), players.end(), [regNum](const Player& player) {
                return player.registrationNumber == regNum;
            });
            if (playerIt != players.end()) {
                cout << " - " << playerIt->firstName << " " << playerIt->lastName << " (Reg: " << regNum << ")\n";
            }
        }
    } else {
        cout << "Team not found!\n\n";
    }
}

void viewAllTeams(const vector<Team>& teams) {
    if (teams.empty()) {
        cout << "\nNo teams available.\n\n";
        return;
    }

    cout << "\n--- All Teams ---\n";
    for (const auto& team : teams) {
        cout << "Team ID: " << team.teamId << "\n"
             << "Team Name: " << team.teamName << "\n"
             << "Players: ";
        for (const auto& playerRegNum : team.playerRegistrationNumbers) {
            cout << playerRegNum << " ";
        }
        cout << "\n\n";
    }
}

void searchPlayer(const vector<Player>& players) {
    int searchOption;
    cout << "Search by:\n1. Registration Number\n2. Name\nEnter your choice: ";
    cin >> searchOption;

    if (searchOption == 1) {
        int regNum;
        cout << "Enter Registration Number: ";
        cin >> regNum;
        for (const auto& player : players) {
            if (player.registrationNumber == regNum) {
                cout << "Registration Number: " << player.registrationNumber << "\n"
                     << "Name: " << player.firstName << " " << player.lastName << "\n"
                     << "Date of Birth: " << player.dateOfBirth << "\n"
                     << "Runs Scored: " << player.runsScored << "\n"
                     << "Teams: ";
                for (const auto& teamId : player.teamIds) {
                    cout << teamId << " ";
                }
                cout << "\n\n";
                return;
            }
        }
        cout << "Player not found!\n\n";
    } else if (searchOption == 2) {
        string fName, lName;
        cout << "Enter First Name: ";
        cin >> fName;
        cout << "Enter Last Name: ";
        cin >> lName;
        for (const auto& player : players) {
            if (player.firstName == fName && player.lastName == lName) {
                cout << "Registration Number: " << player.registrationNumber << "\n"
                     << "Name: " << player.firstName << " " << player.lastName << "\n"
                     << "Date of Birth: " << player.dateOfBirth << "\n"
                     << "Runs Scored: " << player.runsScored << "\n"
                     << "Teams: ";
                for (const auto& teamId : player.teamIds) {
                    cout << teamId << " ";
                }
                cout << "\n\n";
                return;
            }
        }
        cout << "Player not found!\n\n";
    } else {
        cout << "Invalid choice! Try again.\n\n";
    }
}

void deletePlayer(vector<Player>& players, vector<Team>& teams) {
    int regNum;
    cout << "Enter Registration Number of the Player to delete: ";
    cin >> regNum;

    auto playerIt = find_if(players.begin(), players.end(), [regNum](const Player& player) {
        return player.registrationNumber == regNum;
    });

    if (playerIt != players.end()) {
        for (auto& team : teams) {
            team.playerRegistrationNumbers.erase(remove(team.playerRegistrationNumbers.begin(), team.playerRegistrationNumbers.end(), regNum), team.playerRegistrationNumbers.end());
        }
        players.erase(playerIt);
        cout << "Player deleted successfully!\n\n";
    } else {
        cout << "Player not found!\n\n";
    }
}

void editPlayer(vector<Player>& players) {
    int regNum;
    cout << "Enter Registration Number of the Player to edit: ";
    cin >> regNum;

    auto playerIt = find_if(players.begin(), players.end(), [regNum](const Player& player) {
        return player.registrationNumber == regNum;
    });

    if (playerIt != players.end()) {
        string fName, lName, dob;
        int runs;

        cout << "Enter New First Name (current: " << playerIt->firstName << "): ";
        cin >> fName;
        cout << "Enter New Last Name (current: " << playerIt->lastName << "): ";
        cin >> lName;
        cout << "Enter New Date of Birth (current: " << playerIt->dateOfBirth << "): ";
        cin >> dob;
        cout << "Enter New Runs Scored (current: " << playerIt->runsScored << "): ";
        cin >> runs;

        playerIt->firstName = fName;
        playerIt->lastName = lName;
        playerIt->dateOfBirth = dob;
        playerIt->runsScored = runs;

        cout << "Player details updated successfully!\n\n";
    } else {
        cout << "Player not found!\n\n";
    }
}

bool login() {
    string username, password;
    int attempts = 3;

    while (attempts > 0) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == "oshan" && password == "oshan2024") {
            cout << "Login successful!\n\n";
            return true;
        } else {
            cout << "Invalid credentials! Try again.\n\n";
            attempts--;
        }
    }
    return false;
}

void logout() {
    cout << "Logged out successfully!\n\n";
}

void loadPlayers(vector<Player>& players) {
    ifstream file("players.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int regNum, runs;
        string fName, lName, dob;
        iss >> regNum >> fName >> lName >> dob >> runs;
        players.emplace_back(regNum, fName, lName, dob, runs);
    }
}

void loadTeams(vector<Team>& teams) {
    ifstream file("teams.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int teamId;
        string teamName;
        iss >> teamId >> teamName;
        Team team(teamId, teamName);

        string playersLine;
        getline(file, playersLine);
        istringstream playersStream(playersLine);
        int playerRegNum;
        while (playersStream >> playerRegNum) {
            team.playerRegistrationNumbers.push_back(playerRegNum);
        }

        teams.push_back(team);
    }
}

void savePlayers(const vector<Player>& players) {
    ofstream file("players.txt");
    for (const auto& player : players) {
        file << player.registrationNumber << " " << player.firstName << " "
             << player.lastName << " " << player.dateOfBirth << " " << player.runsScored << "\n";
    }
}

void saveTeams(const vector<Team>& teams) {
    ofstream file("teams.txt");
    for (const auto& team : teams) {
        file << team.teamId << " " << team.teamName << "\n";
        for (const auto& playerRegNum : team.playerRegistrationNumbers) {
            file << playerRegNum << " ";
        }
        file << "\n";
    }
}

void loadingScreen() {
    cout << "Loading";
    for (int i = 0; i < 3; ++i) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
    }
    cout << "\n\n";
}

