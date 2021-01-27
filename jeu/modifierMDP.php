<?php
    session_start();
    if(!isset($_SESSION['user']) || isset($_POST['deconnexion'])) {
        session_destroy();
        header('Location: authentification.php');
        exit();
    }
    $currentPage = 'modifierMDP';

    $bdd = new SQLite3("projetsiam.db");
    $mytable = "utilisateurs";

    $errModif = false;
    $valModif = false;
    if(isset($_POST['submit'])){
        $mdpCrypt = sha1($_POST['ancien']);
        $req = "SELECT id FROM $mytable WHERE pseudo=:pseudo AND mot_de_passe=:mdp";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':pseudo',$_SESSION['user'],SQLITE3_TEXT);
        $stmt->bindParam(':mdp',$mdpCrypt,SQLITE3_TEXT);
        $result = $stmt->execute();

        if(!$result->fetchArray()) {
            $errModif = true;
        }
        else{
            $mdpCrypt = sha1($_POST['nouveau']);
            $req = "UPDATE $mytable SET mot_de_passe=:mdp WHERE pseudo=:pseudo";
            $stmt = $bdd->prepare($req);
            $stmt->bindParam(':pseudo',$_SESSION['user'],SQLITE3_TEXT);
            $stmt->bindParam(':mdp',$mdpCrypt,SQLITE3_TEXT);
            $result = $stmt->execute();
            $valModif = true;
        }
    }
?>

<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Modifier mot de passe</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    </head>
    <body>
        <?php include('navbar.php'); ?>
        <div class="jumbotron text-center">
            <h1>Modification du mot de passe</h1>
        </div>
        <div class="container">
            <form enctype="multipart/form-data" method="post" action="">
                <div class="row">
                    <div class="col">
                        <label for="ancien">Ancien mot de passe</label>
                        <input type="password" id="ancien" name="ancien" class="form-control" placeholder="Saisir votre ancien mot de passe" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
                    </div>
                    <div class="col">
                        <label for="nouveau">Nouveau mot de passe</label>
                        <input type="password" id="nouveau" name="nouveau" class="form-control" placeholder="Saisir votre nouveau mot de passe" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
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
                if($errModif){
                    echo "<div class=\"alert alert-danger\"><strong>Erreur modification !</strong> Ancien mot de passe incorrect</div>";
                }
                elseif($valModif){
                    echo "<div class=\"alert alert-success\"><strong>Succès modification !</strong> Votre mot de passe a bien été modifié</div>";
                }
            ?>
        </div>
    </body>
</html>
