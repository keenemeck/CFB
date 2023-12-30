<script lang="ts">

    import { teams } from './scrape.ts';

    function handleButtonClick() {
        console.log("test");
    }

</script>

<svelte:head>
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=DM+Sans:opsz,wght@9..40,600;9..40,800&family=Nunito:ital,wght@0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;0,1000;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900;1,1000&display=swap" rel="stylesheet"> 
</svelte:head>


<main>

    <button on:click={handleButtonClick}>
        test
    </button>



    <div class="memberTeams">
        <div class="card" style="background-color: #00274c; color: #FFCB05">
            <div class="card-logo">
                <img src="images/Michigan.png" alt="img"/>
            </div>
            <div class="card-text">Michigan</div>
            <div class="card-rank">1</div>
        </div>

        <div class="card" style="background-color: #4b2e83; color: #e8e3d3">
            <div class="card-logo">
                <img src="images/Washington.png" alt="img"/>
            </div>
            <div class="card-text">Washington</div>
            <div class="card-rank">2</div>
        </div>

        <div class="card" style="background-color: #EE7524; color: #f0f0f0">
            <div class="card-logo">
                <img src="images/Texas.png" alt="img"/>
            </div>
            <div class="card-text">Texas</div>
            <div class="card-rank">3</div>
        </div>

        <div class="card" style="background-color: #690014; color: #f1f2f3">
            <div class="card-logo">
                <img src="images/Alabama.png" alt="img"/>
            </div>
            <div class="card-text">Alabama</div>
            <div class="card-rank">4</div>
        </div>

        <div class="card" style="background-color: #782F40; color: #ceb888">
            <div class="card-logo">
                <img src="images/Florida State.png" alt="img"/>
            </div>
            <div class="card-text">Florida State</div>
            <div class="card-rank">5</div>
        </div>

        <div class="card" style="background-color: #F1B82D; color: #000000">
            <div class="card-logo">
                <img src="images/Missouri.png" alt="img"/>
            </div>
            <div class="card-text">Mizzou</div>
            <div class="card-rank">9</div>
        </div>
    </div>

    <div class="card">
        <div class="card-logo">
            <img src="images/North Carolina.png" alt="img"/>
        </div>
        <div class="card-text">North Carolina</div>
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