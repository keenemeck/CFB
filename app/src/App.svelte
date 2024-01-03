<script lang="ts">


    import { Team, fetch, Member, members, sortByWins, sortByPoints } from './scrape.ts';
    import { onMount } from 'svelte';

    let teams = {};
    let memberList = {};

    onMount(async () => {
        try {
        // Fetch and merge data from all three sources
        teams = await fetch();

        for (let i = 0; i < members.length; i++) {
            memberList[i] = members[i];
        }

        // Now you can use the merged data array in your component
        } catch (error) {
        // Handle error, e.g., display an error message
        console.error('Failed to fetch data:', error);
        }
    });

    //TODO: fix
    function sortPoints() {
        //teams.sortByPoints();
    }

    function handleButtonClick() {
        try {  
            for (let member of members) {
                console.log(member.totalPoints);
            }
            console.log(teams[team].wins + "-" + teams[team].losses);
            console.log("Points: " + teams[team].totalPoints);
        } catch {
            console.log("no team of that name is known. check spelling or abbreviation to ensure the team name is the same as is posted")
        }
    }

    let team = "";
    

</script>

<svelte:head>
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=DM+Sans:opsz,wght@9..40,600;9..40,800&family=Nunito:ital,wght@0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;0,1000;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900;1,1000&display=swap" rel="stylesheet"> 
</svelte:head>


<main>

    <div class="memberTeams">
        
        {#each Object.values(memberList) as member, i}

            <div class="member">
                <div class="card" class:gold={i === 0} class:silver={i === 1} class:bronze={i === 2} style="display:flex; justify-content: space-between; height: 72px;">
                    <div class="card-name">{i + 1}. {member.name}</div>
                    <div class="card-points" style="line-height: 82px">{member.totalPoints}</div>
                </div>

                {#each Object.values(member.teams) as team}
                    <div class="card" style="background-color: {team.color1}; color: {team.color2}">
                        <div class="card-logo">
                            <img src="images/{team.name}.png" alt="img"/>
                        </div>
                        <div class="card-text">{team.name}</div>
                        <div class="card-points">{team.totalPoints}</div>
                    </div>
                {/each}
            </div>

        {/each}
        
    </div>

    <button on:click={handleButtonClick}>enter</button>

    <input bind:value={team} placeholder="enter team" />
        
</main>

<style>

    :root {
        background-color: #141c24;
        
    }

    .memberTeams {
        font-family: 'DM Sans';
        font-size: 32px;
        font-weight: bold;
        color: #ffffff;

        display: grid;
        grid-template-columns: 1fr 1fr 1fr;
        place-items: center;

    }

    .member {
        margin-bottom: 32px;
    }
    
    .card {
        font-family: 'DM Sans';
        font-size: 32px;
        font-weight: bold;
        background-color: #00000000;
        color: #ffffff;
    
        line-height: 48px;
        width: 410px;
        height: 48px;
    }
    
    .card-logo {
        padding: 4px 8px 4px 8px;
        float: left;
    }
    
    .card-logo img {
        display: block; /* Make the image a block element */
        height: 40px;
        margin: 0; /* Reset margin to zero */
    }
    
    .card-text {
        float: left;
    }
    
    .card-rank {
        width: 40px;
        text-align: center;
        padding-right: 4px;
        float: right;
    }

    .card-points {

        text-align: center;
        padding-right: 4px;
        float: right;
    }

    .card-name {
        padding-left: 8px;
        font-size: 48px;
        line-height: 72px;
    }

    .card-points {
        padding-right: 8px;
    }

    .gold {
        color: #f4e000;
    }

    .silver {
        color: #bbc6cf;
    }

    .bronze {
        color: #b07932;
    }

</style>