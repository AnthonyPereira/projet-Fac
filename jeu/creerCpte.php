<?php
    session_start();
    if(!isset($_SESSION['user']) || isset($_POST['deconnexion'])) {
        session_destroy();
        header('Location: authentification.php');
        exit();
    }
    if($_SESSION['user']!="admin"){
        header('Location: accueil.php');
        exit();
    }
    $currentPage = 'creerCpte';

    $bdd = new SQLite3("projetsiam.db");
    $mytable = "utilisateurs";

    $errCreat = false;
    $valCreat = false;
    if(isset($_POST['submit'])){
        $req = "SELECT id FROM $mytable WHERE pseudo=:pseudo";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':pseudo',$_POST['pseudo'],SQLITE3_TEXT);
        $result = $stmt->execute();

        if(!$result->fetchArray()) {
            $mdpCrypt = sha1($_POST['mdp']);
            $req = "INSERT INTO $mytable(pseudo, mot_de_passe) VALUES (:pseudo, :mdp)";
            $stmt = $bdd->prepare($req);
            $stmt->bindParam(':pseudo',$_POST['pseudo'],SQLITE3_TEXT);
            $stmt->bindParam(':mdp',$mdpCrypt,SQLITE3_TEXT);
            $result = $stmt->execute();
            $valCreat = true;
        }
        else{
            $errCreat = true;
        }
    }
?>

<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Créer compte</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    </head>
    <body>
        <?php include('navbar.php'); ?>
        <div class="jumbotron text-center">
            <h1>Créer un compte joueur</h1>
        </div>
        <div class="container">
            <form enctype="multipart/form-data" method="post" action="">
                <div class="row">
                    <div class="col">
                        <label for="pseudo">Pseudo du nouveau joueur</label>
                        <input type="text" id="pseudo" name="pseudo" class="form-control" placeholder="Saisir un pseudo pour le nouveau joueur" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
                    </div>
                    <div class="col">
                        <label for="mdp">Mot de passe du nouveau joueur</label>
                        <input type="password" id="mdp" name="mdp" class="form-control" placeholder="Saisir un mot de passe pour le nouveau joueur" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
                    </div>
                </div>
                <br>
                <div class="row">
                    <div class="col-sm-3"></div>
                    <div class="col-sm-6">
                        <input type="submit" name="submit" value="Valider" class="btn btn-primary btn-block"/>
                    </div>
                </div>
            </form>
            <?php
                if($errCreat){
                    echo "<div class=\"alert alert-danger\"><strong>Erreur création !</strong> Ce pseudo existe déjà</div>";
                }
                elseif($valCreat){
                    echo "<div class=\"alert alert-success\"><strong>Succès création !</strong> Le joueur a bien été ajouté</div>";
                }
            ?>
        </div>
    </body>
</html>
