#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

#include "classes.h"

using namespace std;


int main() {

    unordered_map<string, Team> teams;

    string str;

    ifstream apPoll;
    apPoll.open("apPoll.csv");

    getline(apPoll, str);

    vector<vector<string>> poll(15, vector<string>(25));

    while (getline(apPoll, str)) {

        vector<string> s = split(str, ",");

        string name = split(s[3], " (")[0];

        poll[stoi(s[0]) - 1][stoi(s[2]) - 1] = name;

    }

    apPoll.close();

    ifstream teamData;
    teamData.open("teamData.csv");

    unordered_map<string, Conference> conferences;
    Conference allConference;
    
    getline(teamData, str);

    while (getline(teamData, str)) {

        vector<string> s = split(str, ",");

        Team team;
        team.name = s[1].substr(1, s[1].size() - 2);
        team.conference = s[7].substr(1, s[7].size() - 2);
        team.division = s[8].substr(1, s[8].size() - 2);
        team.color1 = s[9].substr(1, s[9].size() - 2);
        team.color2 = s[10].substr(1, s[10].size() - 2);

        teams[team.name] = team;

        conferences[team.conference].teams.push_back(&teams[team.name]);
        allConference.teams.push_back(&teams[team.name]);

    }

    teamData.close();


    ifstream file;
    file.open("data.csv");
    
    getline(file, str);

    auto start = std::chrono::high_resolution_clock::now();

    while (getline(file, str)) {

        Game game(split(str, ","));

        if (game.occurred) {

            if (teams.count(game.winner) == 1) {
                Team *t = &teams[game.winner];
                t->wins++;
                t->games.push_back(game);

                int week = game.week - 1;

                if (game.bowlGame() == true) week = 15;

                t->points[week] = 1 + game.confWin(teams) + game.beatRanked(teams) + game.upset(teams) * 2 + game.confChampGame() * 8 + game.bowlGame() * 2 + game.NY6() * 2;
                t->totalPoints += t->points[week];

            }

            if (teams.count(game.loser) == 1) {
                Team *t = &teams[game.loser];
                t->losses++;
                t->games.push_back(game);

                int week = game.week - 1;

                if (game.bowlGame() == true) week = 15;

                t->points[week] = game.confChampGame() * 3 + game.bowlGame() * 2 + game.NY6() * 2;
                t->totalPoints += t->points[week];

            }

        }

    }

    file.close();

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

    for (int i = 0; i < poll.size(); i++) {
        for (int j = 0; j < poll[0].size(); j++) {
            string team = poll[i][j];
            if (nameTranslations.count(team) == 1) team = nameTranslations[team];
            teams[team].points[i + 1] += rankPoints(j + 1);
            teams[team].totalPoints += rankPoints(j + 1);
            if (i == 0) {
                teams[team].points[0] += rankPoints(j + 1);
                teams[team].totalPoints += rankPoints(j + 1);
            }
        }
    }

    Member Nathan, Taylor, Conner, Logan, Dalton, Ryan, Brandon, Tony, Steve, Jim, Miles, Kelly;


    Steve.add(&teams["Michigan"]);
    Steve.add(&teams["Tennessee"]);
    Steve.add(&teams["Texas Tech"]);
    Steve.add(&teams["South Alabama"]);
    Steve.add(&teams["Coastal Carolina"]);
    Steve.add(&teams["Baylor"]);
    Steve.add(&teams["Army"]);
    Steve.add(&teams["Duke"]);
    Steve.add(&teams["Navy"]);
    Steve.add(&teams["Old Dominion"]);

    Nathan.add(&teams["Clemson"]);
    Nathan.add(&teams["Kansas State"]);
    Nathan.add(&teams["Liberty"]);
    Nathan.add(&teams["Toledo"]);
    Nathan.add(&teams["Maryland"]);
    Nathan.add(&teams["Marshall"]);
    Nathan.add(&teams["Florida Atlantic"]);
    Nathan.add(&teams["Wake Forest"]);
    Nathan.add(&teams["Iowa State"]);
    Nathan.add(&teams["Jacksonville State"]);

    Taylor.add(&teams["USC"]);
    Taylor.add(&teams["North Carolina"]);
    Taylor.add(&teams["SMU"]);
    Taylor.add(&teams["NC State"]);
    Taylor.add(&teams["Fresno State"]);
    Taylor.add(&teams["Syracuse"]);
    Taylor.add(&teams["Oklahoma State"]);
    Taylor.add(&teams["Kent State"]);
    Taylor.add(&teams["Texas State"]);
    Taylor.add(&teams["UMass"]);

    Conner.add(&teams["Penn State"]);
    Conner.add(&teams["Notre Dame"]);
    Conner.add(&teams["Colorado"]);
    Conner.add(&teams["Ole Miss"]);
    Conner.add(&teams["North Texas"]);
    Conner.add(&teams["Buffalo"]);
    Conner.add(&teams["San José State"]);
    Conner.add(&teams["BYU"]);
    Conner.add(&teams["UTEP"]);
    Conner.add(&teams["Hawai'i"]);

    Logan.add(&teams["Ohio State"]);
    Logan.add(&teams["Houston"]);
    Logan.add(&teams["Miami"]);
    Logan.add(&teams["Memphis"]);
    Logan.add(&teams["Georgia Southern"]);
    Logan.add(&teams["Washington State"]);
    Logan.add(&teams["Virginia Tech"]);
    Logan.add(&teams["Nevada"]);
    Logan.add(&teams["Western Michigan"]);
    Logan.add(&teams["Florida International"]);

    createTeam(Dalton, {"LSU", "Washington", "Iowa", "South Carolina", "Arizona State", "San Diego State", "Louisiana Tech", "Southern Mississippi", "Bowling Green", "Temple"}, teams);
    createTeam(Ryan, {"Texas", "Wisconsin", "Louisville", "Air Force", "Western Kentucky", "Eastern Michigan", "Louisiana", "Minnesota", "California", "UNLV"}, teams);
    createTeam(Brandon, {"Alabama", "Utah", "Troy", "Boise State", "Pittsburgh", "Kansas", "Middle Tennessee", "Nebraska", "Tulsa", "Rice"}, teams);
    createTeam(Tony, {"Georgia", "Oregon State", "Oklahoma", "Northern Illinois", "Ball State", "West Virginia", "Kentucky", "Connecticut", "Utah State", "Louisiana Monroe"}, teams);
    createTeam(Jim, {"Auburn", "Texas A&M", "James Madison", "Appalachian State", "UCF", "Florida", "Mississippi State", "Georgia State", "UAB", "South Florida"}, teams);
    createTeam(Miles, {"Florida State", "TCU", "UT San Antonio", "Arkansas State", "Ohio", "Colorado State", "New Mexico State", "Illinois", "Georgia Tech", "Cincinnati"}, teams);
    createTeam(Kelly, {"Oregon", "Tulane", "UCLA", "Arkansas", "Missouri", "Wyoming", "East Carolina", "Miami (OH)", "Michigan State", "Central Michigan"}, teams);

    /*sort(Steve.teams.begin(), Steve.teams.end(), sortByPoints);

    for (auto team: Steve.teams) {
        cout << team->name << ",";
        for (auto week: teams[team->name].points) {
            cout << week << ",";
        }
        cout << team->totalPoints << '\n';
    }*/


    sort(allConference.teams.begin(), allConference.teams.end(), sortByPoints);

    for (auto team: allConference.teams) {
        cout << team->wins << "-" << team->losses << "\t" << team->name << "\t" << team->totalPoints << '\n';
    }

    /*for (auto game: teams["Florida State"].games) {
        printGame(game);
    }*/

    /*for (double week: teams["Florida State"].points) {
        cout << week << " ";
    }*/

    /*sort(conferences["SEC"].teams.begin(), conferences["SEC"].teams.end(), sortByWins);

    for (auto team: conferences["SEC"].teams) {
        cout << team->name << ": " << team->wins << "-" << team->losses << '\n';
    }*/

    
    auto stop = std::chrono::high_resolution_clock::now();

    cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0;
    

    


    return 0;

}