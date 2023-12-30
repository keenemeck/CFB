#include "classes.h"

vector<string> split(const string s, const string delimiter) {

    int start = 0;
    int end;
    
    string token;
    vector<string> result;

    while ((end = s.find(delimiter, start)) != string::npos) {
        token = s.substr(start, end - start);
        start = end + delimiter.length();
        result.push_back(token);
    }

    result.push_back(s.substr(start));

    return result;

}

unordered_map<string, string> nameTranslations = {
    {"Texas-El Paso", "UTEP"},
    {"Southern California", "USC"},
    {"Alabama-Birmingham","UAB"},
    {"San Jose State","San José State"},
    {"Nevada-Las Vegas","UNLV"},
    {"Massachusetts","UMass"},
    {"Louisiana State","LSU"},
    {"Southern Methodist","SMU"},
    {"Texas Christian","TCU"},
    {"Mississippi","Ole Miss"},
    {"Miami (FL)","Miami"},
    {"Louisiana-Monroe","Louisiana Monroe"},
    {"Texas-San Antonio","UT San Antonio"},
    {"Hawaii","Hawai'i"},
    {"Brigham Young","BYU"},
    {"Sam Houston","Sam Houston State"},
    {"Middle Tennessee State","Middle Tennessee"},
    {"North Carolina State","NC State"},
    {"Central Florida","UCF"}
};

Game::Game(const vector<string> gameInfo) {

    number = stoi(gameInfo[0]);
    week = stoi(gameInfo[1]);
    date = gameInfo[2];
    time = gameInfo[3];
    day = gameInfo[4];
    location = gameInfo[7];
    notes = gameInfo[10];

    // Stores scores if game happened
    if (!(gameInfo[6].empty() && gameInfo[9].empty()) && !(gameInfo[6] == "0" && gameInfo[9] == "0")) {
        occurred = true;
        winnerPoints = stoi(gameInfo[6]);
        loserPoints = stoi(gameInfo[9]);
    }

    // Strips rank from school name
    if (gameInfo[5][0] == '(') {
        if (gameInfo[5][2] == ')') {
            winnerRank = gameInfo[5][1] - 48;
            winner = gameInfo[5].substr(4, gameInfo[5].size());
        } else {
            winnerRank = 10 * (gameInfo[5][1] - 48) + gameInfo[5][2] - 48;
            winner = gameInfo[5].substr(5, gameInfo[5].size());
        }
    } else winner = gameInfo[5];

    if (gameInfo[8][0] == '(') {
        if (gameInfo[8][2] == ')') {
            loserRank = gameInfo[8][1] - 48;
            loser = gameInfo[8].substr(4, gameInfo[8].size());
        } else {
            loserRank = 10 * (gameInfo[8][1] - 48) + gameInfo[8][2] - 48;
            loser = gameInfo[8].substr(5, gameInfo[8].size());
        }
    } else loser = gameInfo[8];

    // Translates names
    if (nameTranslations.count(winner) == 1) winner = nameTranslations[winner];
    if (nameTranslations.count(loser) == 1) loser = nameTranslations[loser];
   
}

bool Game::confWin(unordered_map<string, Team>& teams) {
    
    return (teams[winner].conference == teams[loser].conference) && teams[winner].conference != "FBS Independents";

}

bool Game::beatRanked(unordered_map<string, Team>& teams) {
    
    return loserRank < 99;

}

bool Game::upset(unordered_map<string, Team>& teams) {
    
    return winnerRank > loserRank;

}

bool Game::confChampGame() {
    
    return week == 15;

}

bool Game::bowlGame() {

    return notes.find("Bowl") != string::npos;

}

bool Game::NY6() {

    vector<string> NY6Bowls = {"Rose Bowl", "Orange Bowl", "Sugar Bowl", "Cotton Bowl", "Peach Bowl", "Fiesta Bowl"};

    bool found = false;

    for (auto bowl: NY6Bowls) {
        if (bowl == notes) found = true;
    }

    return found;

}

bool Game::playoffs() {
    
    return false;

}

bool Game::nationalChamps() {
    
    return false;

}


Team::Team() {}

Team::Team(const Team& team2) {

    name = team2.name;
    conference = team2.conference;
    division = team2.division;
    color1 = team2.color1;
    color2 = team2.color2;

    wins = team2.wins;
    losses = team2.losses;

    games = team2.games;

}

void Member::add(Team* team) {

    teams.push_back(team);

}

void printGame(Game& game) {

    if (game.winnerRank < 99) cout << game.winnerRank << ". ";
    cout << game.winner << " beat ";
    if (game.loserRank < 99) cout << game.loserRank << ". ";

    cout << game.loser << " " << game.winnerPoints << "-" << game.loserPoints << '\n';

}

bool sortByWins(const Team* a, const Team* b) {

    if (a->wins == b->wins) {
        if (a->losses == b->losses) return (a->name < b->name);
        return (a->losses < b->losses);
    }
    return (a->wins > b->wins);

}

bool sortByPoints(const Team* a, const Team* b) {

    if (a->totalPoints == b->totalPoints) return (a->name < b->name);
    return (a->totalPoints > b->totalPoints);

}

double rankPoints(const int rank) {

    if (rank > 10) return 0.25;
    if (rank > 5) return 0.5;
    if (rank > 1) return 0.75;
    return 1;

}

void createTeam(Member& member, vector<string> teamList, unordered_map<string, Team>& teams) {

    for (int i = 0; i < 10; i++) {
        member.add(&teams[teamList[i]]);
    }

}