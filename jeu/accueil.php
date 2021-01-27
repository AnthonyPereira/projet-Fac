<?php
    session_start();
    if(!isset($_SESSION['user']) || isset($_POST['deconnexion'])) {
        session_destroy();
        header('Location: authentification.php');
        exit();
    }
    $currentPage = 'accueil';

    $bdd = new SQLite3("projetsiam.db");
    $mytable = "parties";

    /*
    $query = "DROP TABLE IF EXISTS $mytable";
    $result = $bdd->exec($query);
    */
    $query = "CREATE TABLE IF NOT EXISTS $mytable(
                        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                        nom TEXT UNIQUE NOT NULL,
                        createur TEXT NOT NULL,
                        joueur1 TEXT,
                        joueur2 TEXT,
                        tour INTEGER NOT NULL,
                        jeu TEXT
                )";
    $result = $bdd->exec($query);

    $errJoin = false;
    if(isset($_POST['Entrer'])) {
        $_SESSION['partie']=$_POST['Entrer'];
        $_SESSION['choixPion']=false;
        $_SESSION['poserPion']=false;
        $_SESSION['poserCase']="";
        $_SESSION['choixCase']="";
        $_SESSION['choixDirection']="";
        $_SESSION['choixCaseDirection']="";
        //$_SESSION['rotationPion']=0;
        //$_SESSION['actionPion']=false;
        header('Location: partie.php');
        exit();
    }
    else if(isset($_POST['supprimer'])) {
        $req = "DELETE FROM $mytable WHERE id=:id";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':id',$_POST['supprimer'],SQLITE3_TEXT);
        $result = $stmt->execute();
    }
    else if(isset($_POST['Rejoindre'])) {
        $req = "SELECT * FROM $mytable WHERE id=:id AND (joueur1 IS NULL OR joueur2 IS NULL)";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':id',$_POST['Rejoindre'],SQLITE3_TEXT);
        $result = $stmt->execute();

        if($row = $result->fetchArray()) {
            if(is_null($row[3])){
                $req = "UPDATE $mytable SET joueur1=:joueur1 WHERE id=:id";
                $stmt = $bdd->prepare($req);
                $stmt->bindParam(':joueur1',$_SESSION['user'],SQLITE3_TEXT);
            }
            else if($row[3]!=$_SESSION['user']){
                $req = "UPDATE $mytable SET joueur2=:joueur2 WHERE id=:id";
                $stmt = $bdd->prepare($req);
                $stmt->bindParam(':joueur2',$_SESSION['user'],SQLITE3_TEXT);
            }
            $stmt->bindParam(':id',$_POST['Rejoindre'],SQLITE3_TEXT);
            $result = $stmt->execute();
        }
        else{
            $errJoin = true;
        }
    }
?>

<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Accueil</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    </head>
    <body>
        <?php include('navbar.php'); ?>
        <div class="bg-light py-5">
            <div class="container">
                <h1 class="text-center pb-5">Vos parties en cours</h1>
                <div class="album">
                    <div class="row">
                        <?php
                            $greenButton = "Entrer";
                            if($_SESSION['user']=="admin"){
                                $req = "SELECT * FROM $mytable WHERE joueur1=:pseudo OR joueur2=:pseudo OR (joueur1 IS NOT NULL AND joueur2 IS NOT NULL) ORDER BY joueur2 DESC";
                            }
                            else{
                                $req = "SELECT * FROM $mytable WHERE joueur1=:pseudo OR joueur2=:pseudo ORDER BY joueur2 DESC";
                            }
                            $stmt = $bdd->prepare($req);
                            $stmt->bindParam(':pseudo',$_SESSION['user'],SQLITE3_TEXT);
                            $result = $stmt->execute();
                            if($row = $result->fetchArray()) {
                                do {
                                    include('card.php');
                                } while ($row = $result->fetchArray());
                            }
                            else {
                        ?>
                        <div class="col-md-12">
                            <div class="alert alert-info"><strong>Aucune partie rejointe !</strong> Rejoignez une partie, ou créez en une via l'onglet "Créer une partie"</div>
                        </div>
                        <?php
                            }
                        ?>
                    </div>
                </div>
            </div>
        </div>
        <div class="bg-white py-5">
            <div class="container">
                <h1 class="text-center pb-5">Rejoindre une partie</h1>
                <div class="album">
                    <div class="row">
                        <?php
                            $greenButton = "Rejoindre";
                            $req = "SELECT * FROM $mytable WHERE joueur1 IS NULL OR joueur2 IS NULL EXCEPT SELECT * FROM $mytable WHERE joueur1=:pseudo OR joueur2=:pseudo";
                            $stmt = $bdd->prepare($req);
                            $stmt->bindParam(':pseudo',$_SESSION['user'],SQLITE3_TEXT);
                            $result = $stmt->execute();
                            if($row = $result->fetchArray()) {
                                do {
                                    include('card.php');
                                } while ($row = $result->fetchArray());
                            }
                            else{
                        ?>
                        <div class="col-md-12">
                            <div class="alert alert-info"><strong>Aucune partie à rejoindre !</strong> Créez une partie via l'onglet "Créer une partie"</div>
                        </div>
                        <?php
                            }

                            if($errJoin){
                        ?>
                        <div class="col-md-12">
                            <div class="alert alert-danger"><strong>Vous n'avez pas rejoint la partie !</strong> La partie est pleine ou a été supprimée par un administrateur</div>
                        </div>
                        <?php
                            }
                        ?>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>
