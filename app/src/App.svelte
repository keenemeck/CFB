<script lang="ts">


    import { Team, fetch, members, sortByWins, sortByPoints } from './scrape.ts';
    import { onMount } from 'svelte';

    let teams = {};

    onMount(async () => {
        try {
        // Fetch and merge data from all three sources
        teams = await fetch();

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
            console.log(teams[team].wins + "-" + teams[team].losses);
            console.log("Points: " + teams[team].totalPoints);
            console.log(teams[team].color1 + " " + teams[team].color2);
        } catch {
            console.log("no team of that name is known. check spelling or abbreviation to ensure the team name is the same as is posted")
        }
        console.log(members);
    }

    let team = "";
    

</script>

<svelte:head>
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=DM+Sans:opsz,wght@9..40,600;9..40,800&family=Nunito:ital,wght@0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;0,1000;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900;1,1000&display=swap" rel="stylesheet"> 
</svelte:head>


<main>

    <button on:click={handleButtonClick}>enter</button>

    <input bind:value={team} placeholder="enter team" />

    <div class="memberTeams">
        
            {#each Object.values(teams) as team (team.name)}
            <div class="card" style="background-color: {team.color1}; color: {team.color2}">
                <div class="card-logo">
                    <img src="images/{team.name}.png" alt="img"/>
                </div>
                <div class="card-text">{team.name}</div>
            </div>
            {/each}

    </div>
        
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
    }
    
    .card {
        font-family: 'DM Sans';
        font-size: 32px;
        font-weight: bold;
        background-color: #99bfe5;
        color: #ffffff;
    
        width: 360px;
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
        line-height: 48px;
        float: left;
    }
    
    .card-rank {
        width: 40px;
        text-align: center;
        padding-right: 4px;
        line-height: 48px;
        float: right;

    }
    
</style>