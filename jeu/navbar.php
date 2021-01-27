<nav class="navbar navbar-expand-sm bg-dark navbar-dark">
    <span class="navbar-brand mb-0 h1"><?php echo $_SESSION['user'] ?></span>
    <div class="px-1" style="border-left: 2px solid white; height: 40px;"></div>
    <ul class="navbar-nav">
        <li class="nav-item <?php if($currentPage=='accueil'){ echo 'active'; } ?>">
            <a class="nav-link" href="accueil.php">Accueil</a>
        </li>
        <li class="nav-item <?php if($currentPage=='modifierMDP'){ echo 'active'; } ?>">
            <a class="nav-link" href="modifierMDP.php">Modifier mot de passe</a>
        </li>
        <li class="nav-item <?php if($currentPage=='creerPartie'){ echo 'active'; } ?>">
            <a class="nav-link" href="creerPartie.php">Créer une partie</a>
        </li>
        <?php
            if($_SESSION['user']=='admin'){
        ?>
        <li class="nav-item <?php if($currentPage=='creerCpte'){ echo 'active'; } ?>">
            <a class="nav-link" href="creerCpte.php">Créer un compte joueur</a>
        </li>
        <li class="nav-item <?php if($currentPage=='supprimerCpte'){ echo 'active'; } ?>">
            <a class="nav-link" href="supprimerCpte.php">Supprimer un compte joueur</a>
        </li>
        <?php
            }
        ?>
    </ul>
    <form enctype="multipart/form-data" method="post" action="" class="form-inline ml-auto my-sm-0">
        <input type="submit" name="deconnexion" value="Déconnexion" class="btn btn-danger btn-lg navbar-right"/>
    </form>
</nav>