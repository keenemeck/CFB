#ifndef classes_h
#define classes_h

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

class Team;

class Game {

public:

    Game(const vector<string> gameInfo);

    int week;
    int number;
    int winnerPoints;
    int winnerRank = 99;
    int loserPoints;
    int loserRank = 99;
    string date;
    string time;
    string day;
    string winner;
    string loser;
    string location;
    string notes;
    bool occurred = false;

    bool confWin(unordered_map<string, Team>& teams);
    bool beatRanked(unordered_map<string, Team>& teams);
    bool upset(unordered_map<string, Team>& teams);
    bool confChampGame();
    bool confChampWin();
    bool bowlGame();
    bool NY6();
    bool playoffs();
    bool nationalChamps();

};


class Team {

public:

    Team();
    Team(const Team& team2);

    string name;
    string conference;
    string division;
    string color1;
    string color2;

    int wins = 0;
    int losses = 0;

    double points[17] = {};

    double totalPoints = 0;

    vector<Game> games;

    Game getGame(const int index) { return games[index]; }

};

class Conference {

public:

    vector<Team*> teams;

};

class Member {

public:

    string name;
    vector<Team*> teams;

    void add(Team* team);

};


vector<string> split(const string s, const string delimiter);
void printGame(Game& game);
bool sortByWins(const Team* a, const Team* b);
bool sortByPoints(const Team* a, const Team* b);
double rankPoints(const int rank);
void createTeam(Member& member, vector<string> teamList, unordered_map<string, Team>& teams);

#endif