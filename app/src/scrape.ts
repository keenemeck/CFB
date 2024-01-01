import { split } from 'lodash';
import { csv } from 'd3-fetch';

import App from './App.svelte';

const app = new App({
	target: document.body,
});

export default app;

interface MyCSVRow {
    [key: string]: string;
}

export class Team {
    name: string;
    conference: string;
    division: string;
    color1: string;
    color2: string;
    wins: number;
    losses: number;
    games: Game[];
    points: number[];
    totalPoints: number = 0;

    constructor(team2: Team) {
        this.name = team2.name;
        this.conference = team2.conference;
        this.division = team2.division;
        this.color1 = team2.color1;
        this.color2 = team2.color2;
        this.wins = team2.wins;
        this.losses = team2.losses;
        this.games = team2.games;
        this.points = team2.points;
        this.totalPoints = team2.totalPoints;
    }
}

class Conference {
    teams: Team[];

    constructor() {
        this.teams = [];
    }

}


export class Member {
    name: string;
    teams: Team[];
    totalPoints: number;

    constructor(name: string) {
        this.name = name;
        this.teams = [];
        this.totalPoints = 0;
    }

    add(team: Team): void {
        this.teams.push(team);
    }
}

const nameTranslations: { [key: string]: string } = {
    "Texas-El Paso": "UTEP",
    "Southern California": "USC",
    "Alabama-Birmingham": "UAB",
    "San Jose State": "San José State",
    "Nevada-Las Vegas": "UNLV",
    "Massachusetts": "UMass",
    "Louisiana State": "LSU",
    "Southern Methodist": "SMU",
    "Texas Christian": "TCU",
    "Mississippi": "Ole Miss",
    "Miami (FL)": "Miami",
    "Louisiana-Monroe": "Louisiana Monroe",
    "Texas-San Antonio": "UT San Antonio",
    "Hawaii": "Hawai'i",
    "Brigham Young": "BYU",
    "Sam Houston": "Sam Houston State",
    "Middle Tennessee State": "Middle Tennessee",
    "North Carolina State": "NC State",
    "Central Florida": "UCF",
};


let teamDataContent: MyCSVRow[];
let dataContent: MyCSVRow[];
let apPollContent: MyCSVRow[];

export const teams: { [key: string]: Team } = {};

//TODO: functify

const Nathan  = new Member("Nathan");
const Taylor  = new Member("Taylor");
const Conner  = new Member("Conner");
const Logan   = new Member("Logan");
const Dalton  = new Member("Dalton");
const Ryan    = new Member("Ryan");
const Brandon = new Member("Brandon");
const Tony    = new Member("Tony");
const Steve   = new Member("Steve");
const Jim     = new Member("Jim");
const Miles   = new Member("Miles");
const Kelly   = new Member("Kelly");

export const members: Member[] = [Nathan, Taylor, Conner, Logan, Dalton, Ryan, Brandon, Tony, Steve, Jim, Miles, Kelly];

const NathanTeams  = ["Clemson", "Kansas State", "Liberty", "Toledo", "Maryland", "Marshall", "Florida Atlantic", "Wake Forest", "Iowa State", "Jacksonville State"];
const TaylorTeams  = ["USC", "North Carolina", "SMU", "NC State", "Fresno State", "Syracuse", "Oklahoma State", "Kent State", "Texas State", "UMass"];
const ConnerTeams  = ["Penn State", "Notre Dame", "Colorado", "Ole Miss", "North Texas", "Buffalo", "San José State", "BYU", "UTEP", "Hawai'i"];
const LoganTeams   = ["Ohio State", "Houston", "Miami", "Memphis", "Georgia Southern", "Washington State", "Virginia Tech", "Nevada", "Western Michigan", "Florida International"];
const DaltonTeams  = ["LSU", "Washington", "Iowa", "South Carolina", "Arizona State", "San Diego State", "Louisiana Tech", "Southern Mississippi", "Bowling Green", "Temple"];
const RyanTeams    = ["Texas", "Wisconsin", "Louisville", "Air Force", "Western Kentucky", "Eastern Michigan", "Louisiana", "Minnesota", "California", "UNLV"];
const BrandonTeams = ["Alabama", "Utah", "Troy", "Boise State", "Pittsburgh", "Kansas", "Middle Tennessee", "Nebraska", "Tulsa", "Rice"];
const TonyTeams    = ["Georgia", "Oregon State", "Oklahoma", "Northern Illinois", "Ball State", "West Virginia", "Kentucky", "Connecticut", "Utah State", "Louisiana Monroe"];
const SteveTeams   = ["Michigan", "Tennessee", "Texas Tech", "South Alabama", "Coastal Carolina", "Baylor", "Army", "Duke", "Navy", "Old Dominion"];
const JimTeams     = ["Auburn", "Texas A&M", "James Madison", "Appalachian State", "UCF", "Florida", "Mississippi State", "Georgia State", "UAB", "South Florida"];
const MilesTeams   = ["Florida State", "TCU", "UT San Antonio", "Arkansas State", "Ohio", "Colorado State", "New Mexico State", "Illinois", "Georgia Tech", "Cincinnati"];
const KellyTeams   = ["Oregon", "Tulane", "UCLA", "Arkansas", "Missouri", "Wyoming", "East Carolina", "Miami (OH)", "Michigan State", "Central Michigan"];


export async function fetch () {
    teamDataContent = await csv('https://raw.githubusercontent.com/keenemeck/CFB/main/app/src/teamData.csv');

    teamDataContent.slice(0).forEach((row: MyCSVRow) => {

        const {Id, School, Mascot, Abbreviation, AltName1, AltName2, AltName3, Conference, Division, Color, AltColor, Logo0, Logo1, Twitter, LocationVenueId, LocationName, LocationCity, LocationState, LocationZip, LocationCountryCode, LocationTimezone, LocationLatitude, LocationLongitude, LocationElevation, LocationCapacity, LocationYearConstructed, LocationGrass, LocationDome} = row;
    
        const team: Team = {
            name: row.School,
            conference: row.Conference,
            division: row.Division,
            color1: row.Color,
            color2: row.AltColor,
            wins: 0,
            losses: 0,
            games: [],
            points: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            totalPoints: 0,
        };
    
        teams[team.name] = team;
    
        if (!conferences[team.conference]) {
            conferences[team.conference] = { teams: [] };
        }
    
        conferences[team.conference].teams.push(team);
        allConference.teams.push(team);
        
    });
    
    //TODO: functify

    const poll: string[][] = new Array(15).fill([]).map(() => new Array(25).fill(''));

    apPollContent = await csv('https://raw.githubusercontent.com/keenemeck/CFB/main/app/src/apPoll.csv');

    apPollContent.slice(0).forEach((row: MyCSVRow) => {

        const {Wk, Date, Rk, School, Prev, Chng, Conf, ThisWeek} = row;

        const name: string = row.School.replace(/\s*\(.*$/, '');

        const rowIndex: number = parseInt(row.Wk) - 1;
        const columnIndex: number = parseInt(row.Rk) - 1;

        poll[rowIndex][columnIndex] = name;
    });

    for (let i = 0; i < poll.length; i++) {
        for (let j = 0; j < poll[0].length; j++) {
            let team = poll[i][j];
            
            if (nameTranslations.hasOwnProperty(team)) {
                team = nameTranslations[team];
            }
    
            teams[team].points[i + 1] += rankPoints(j + 1);
            teams[team].totalPoints += rankPoints(j + 1);
    
            if (i === 0) {
                teams[team].points[0] += rankPoints(j + 1);
                teams[team].totalPoints += rankPoints(j + 1);
            }
        }
    }

    dataContent = await csv('https://raw.githubusercontent.com/keenemeck/CFB/main/app/src/data.csv');

    dataContent.slice(1).forEach((row: MyCSVRow) => {
        const line: string = row._row;

        const {Rk, Wk, Date, Time, Day, Winner, Pts1, Location, Loser, Pts2, Notes} = row;

        const teamString = Object.values(row).join(',');

        const game = new Game(split(teamString, ','));
    
        if (game.occurred) {
            if (teams.hasOwnProperty(game.winner)) {
                const t = teams[game.winner];
                t.wins++;
                t.games.push(game);
    
                let week = game.week - 1;
    
                if (game.bowlGame()) week = 15;
    
                t.points[week] = Math.max(
                    1 +
                    game.confWin(teams) +
                    game.beatRanked(teams) +
                    game.upset(teams) * 2 +
                    game.confChampGame() * 8 +
                    game.bowlGame() * 2 +
                    game.NY6() * 2, 0);
    
                t.totalPoints += t.points[week];
            }
    
            if (teams.hasOwnProperty(game.loser)) {
                const t = teams[game.loser];
                t.losses++;
                t.games.push(game);
    
                let week = game.week - 1;
    
                if (game.bowlGame()) week = 15;
    
                t.points[week] = Math.max(game.confChampGame() * 3 + game.bowlGame() * 2 + game.NY6() * 2, 0);
                t.totalPoints += t.points[week];
            }
        }
    });

    createTeam(Nathan, NathanTeams, teams);
    createTeam(Taylor, TaylorTeams, teams);
    createTeam(Conner, ConnerTeams, teams);
    createTeam(Logan, LoganTeams, teams);
    createTeam(Dalton, DaltonTeams, teams);
    createTeam(Ryan, RyanTeams, teams);
    createTeam(Brandon, BrandonTeams, teams);
    createTeam(Tony, TonyTeams, teams);
    createTeam(Steve, SteveTeams, teams);
    createTeam(Jim, JimTeams, teams);
    createTeam(Miles, MilesTeams, teams);
    createTeam(Kelly, KellyTeams, teams);

    members.sort((a, b) => b.totalPoints - a.totalPoints);

    return teams;

};


interface Conference {
    teams: Team[];
}

class Game {
    number: number;
    week: number;
    date: string;
    time: string;
    day: string;
    location: string;
    notes: string;
    occurred: boolean;
    winnerPoints: number;
    loserPoints: number;
    winnerRank: number;
    winner: string;
    loserRank: number;
    loser: string;

    constructor(gameInfo: string[]) {
        this.number = parseInt(gameInfo[0]);
        this.week = parseInt(gameInfo[1]);
        this.date = gameInfo[2];
        this.time = gameInfo[3];
        this.day = gameInfo[4];
        this.location = gameInfo[7];
        this.notes = gameInfo[10];
        this.occurred = false;
        this.winnerPoints = -1;
        this.loserPoints = -1;
        this.winnerRank = 99;
        this.loserRank = 99;

        if ((gameInfo[6] || gameInfo[9]) && !(gameInfo[6] == "0" && gameInfo[9] == "0")) {
            this.occurred = true;
            this.winnerPoints = parseInt(gameInfo[6]);
            this.loserPoints = parseInt(gameInfo[9]);
        }

        if (gameInfo[5][0] == '(') {
            if (gameInfo[5][2] == ')') {
                this.winnerRank = parseInt(gameInfo[5][1]);
                this.winner = gameInfo[5].substring(4, gameInfo[5].length);
            } else {
                this.winnerRank = 10 * (parseInt(gameInfo[5][1])) + parseInt(gameInfo[5][2]);
                this.winner = gameInfo[5].substring(5, gameInfo[5].length);
            }
        } else {
            this.winner = gameInfo[5];
        }

        if (gameInfo[8][0] == '(') {
            if (gameInfo[8][2] == ')') {
                this.loserRank = parseInt(gameInfo[8][1]);
                this.loser = gameInfo[8].substring(4, gameInfo[8].length);
            } else {
                this.loserRank = 10 * (parseInt(gameInfo[8][1])) + parseInt(gameInfo[8][2]);
                this.loser = gameInfo[8].substring(5, gameInfo[8].length);
            }
        } else {
            this.loser = gameInfo[8];
        }

        if (nameTranslations.hasOwnProperty(this.winner)) {
            this.winner = nameTranslations[this.winner];
        }
        if (nameTranslations.hasOwnProperty(this.loser)) {
            this.loser = nameTranslations[this.loser];
        }
    }

    confWin(teams: { [key: string]: Team }): number {

        const winnerKey = this.winner as string;
        const loserKey = this.loser as string;

        if (teams.hasOwnProperty(winnerKey) && teams.hasOwnProperty(loserKey)) {
            const winner = teams[winnerKey];
            const loser = teams[loserKey];

            return (winner.conference === loser.conference && winner.conference !== "FBS Independents") ? 1 : 0;
                
        }

        return 0;
    
    }

    // TODO: REDO THIS BASED ON POLL RANK NOT GAME RANK MAYBE?
    beatRanked(teams: { [key: string]: Team }): number {
        return this.loserRank < 99 ? 1 : 0;
    }

    upset(teams: { [key: string]: Team }): number {
        return this.winnerRank > this.loserRank ? 1 : 0;
    }

    confChampGame(): number {
        return this.week == 15 ? 1 : 0;
    }

    bowlGame(): number {
        return this.notes != null && this.notes.includes("Bowl") ? 1 : 0;
    }

    NY6(): number {
        const NY6Bowls: string[] = ["Rose Bowl", "Orange Bowl", "Sugar Bowl", "Cotton Bowl", "Peach Bowl", "Fiesta Bowl"];
        let found = false;
        for (let bowl of NY6Bowls) {
            if (bowl == this.notes) {
                found = true;
            }
        }
        return found ? 1 : 0;
    }

    playoffs(): number {
        return 0;
    }

    nationalChamps(): number {
        return 0;
    }
}


function printGame(game: Game): void {
    if (game.winnerRank < 99) {
        console.log(game.winnerRank + ". ");
    }
    console.log(game.winner + " beat ");
    if (game.loserRank < 99) {
        console.log(game.loserRank + ". ");
    }
    console.log(game.loser + " " + game.winnerPoints + "-" + game.loserPoints + '\n');
}

export function sortByWins(a: Team, b: Team): boolean {
    if (a.wins == b.wins) {
        if (a.losses == b.losses) {
            return (a.name < b.name);
        }
        return (a.losses < b.losses);
    }
    return (a.wins > b.wins);
}

export function sortByPoints(a: Team, b: Team): boolean {
    if (a.totalPoints == b.totalPoints) {
        return (a.name < b.name);
    }
    return (a.totalPoints > b.totalPoints);
}

function rankPoints(rank: number): number {
    if (rank > 10) {
        return 0.25;
    }
    if (rank > 5) {
        return 0.5;
    }
    if (rank > 1) {
        return 0.75;
    }
    return 1;
}

function createTeam(member: Member, teamList: string[], teams: { [key: string]: Team }): void {
    for (let i = 0; i < 10; i++) {
        member.add(teams[teamList[i]]);
        member.totalPoints += teams[teamList[i]].totalPoints;
    }
    member.teams.sort((a, b) => b.totalPoints - a.totalPoints);
}


const conferences: { [key: string]: Conference } = {};
const allConference: Conference = { teams: [] };






// Log the resulting teams, conferences, and allConference
// console.log('Teams:', teams);
// console.log('Conferences:', conferences);
// console.log('All Conference:', allConference);

/*console.log(teams["NC State"].totalPoints);
console.log(Steve.totalPoints);*/