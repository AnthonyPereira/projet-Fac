<?php
    session_start();
    if(!isset($_SESSION['user']) || isset($_POST['deconnexion'])) {
        session_destroy();
        header('Location: authentification.php');
        exit();
    }
    $currentPage = 'creerPartie';

    $bdd = new SQLite3("projetsiam.db");
    $mytable = "parties";

    $errCreat = false;
    $valCreat = false;
    if(isset($_POST['submit'])){
        $req = "SELECT id FROM $mytable WHERE nom=:nom";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':nom',$_POST['nomPartie'],SQLITE3_TEXT);
        $result = $stmt->execute();

        if(!$result->fetchArray()) {
            if(!empty($_POST['rejoindre'])) { //coché
                $req = "INSERT INTO $mytable(nom, createur, joueur1, tour) VALUES (:nom, :createur, :joueur1, :tour)";
                $stmt = $bdd->prepare($req);
                $stmt->bindParam(':joueur1',$_SESSION['user'],SQLITE3_TEXT);
            }
            else { //pas coché
                $req = "INSERT INTO $mytable(nom, createur, tour) VALUES (:nom, :createur, :tour)";
                $stmt = $bdd->prepare($req);
            }
            $tour = rand(0,1);
            $stmt->bindParam(':nom',$_POST['nomPartie'],SQLITE3_TEXT);
            $stmt->bindParam(':createur',$_SESSION['user'],SQLITE3_TEXT);
            $stmt->bindParam(':tour',$tour,SQLITE3_INTEGER);
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
        <title>Créer partie</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    </head>
    <body>
        <?php include('navbar.php'); ?>
        <div class="jumbotron text-center">
            <h1>Créer une nouvelle partie</h1>
        </div>
        <div class="container">
            <form enctype="multipart/form-data" method="post" action="">
                <div class="row">
                    <div class="col">
                        <label for="nomPartie">Nom de la partie</label>
                        <input type="text" id="nomPartie" name="nomPartie" class="form-control" placeholder="Saisir le nom de la partie" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
                    </div>
                    <div class="col text-center">
                        <br>
                        <input type="checkbox" id="rejoindre" name="rejoindre" value="rejoindre">
                        <label for="rejoindre"> Rejoindre la partie nouvellement créée</label>
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
                    echo "<div class=\"alert alert-danger\"><strong>Erreur création !</strong> Une partie existante porte déjà ce nom</div>";
                }
                elseif($valCreat){
                    echo "<div class=\"alert alert-success\"><strong>Succès création !</strong> La partie a bien été créée</div>";
                }
            ?>
        </div>
    </body>
</html>
