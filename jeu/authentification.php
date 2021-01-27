<?php
    session_start();
    if(isset($_SESSION['user'])) {
        header('Location: accueil.php');
        exit();
    }
    session_destroy();

    $bdd = new SQLite3("projetsiam.db");
    $mytable = "utilisateurs";

    /*
    $query = "DROP TABLE IF EXISTS $mytable";
    $result = $bdd->exec($query);
    */
    $query = "CREATE TABLE IF NOT EXISTS $mytable(
                        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                        pseudo TEXT UNIQUE NOT NULL,
                        mot_de_passe TEXT NOT NULL
                )";
    $result = $bdd->exec($query);

    $req = "SELECT id FROM $mytable WHERE pseudo=:pseudo AND mot_de_passe=:mdp";
    $stmt = $bdd->prepare($req);

    $errAuth = false;
    if(isset($_POST['submit'])){
        $mdpCrypt = sha1($_POST['mdp']);
        $stmt->bindParam(':pseudo',$_POST['pseudo'],SQLITE3_TEXT);
        $stmt->bindParam(':mdp',$mdpCrypt,SQLITE3_TEXT);
        $result = $stmt->execute();

        if(!$result->fetchArray()) {
            $errAuth = true;
        }
        else{
            session_start();
            $_SESSION['user']=$_POST['pseudo'];
            header('Location: accueil.php');
            exit();
        }
    }

    $pseudo = "admin";
    $pwd = sha1("admin");
    $query = "INSERT OR IGNORE INTO $mytable(pseudo, mot_de_passe) VALUES ('$pseudo', '$pwd')";
    $result = $bdd->exec($query);
?>

<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Authentification</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
    </head>
    <body>
        <div class="jumbotron text-center">
            <h1>Authentification Siam</h1>
        </div>
        <div class="container">
            <form enctype="multipart/form-data" method="post" action="">
                <div class="row">
                    <div class="col">
                        <label for="pseudo">Pseudo</label>
                        <input type="text" id="pseudo" name="pseudo" class="form-control" placeholder="Saisir votre pseudo" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
                    </div>
                    <div class="col">
                        <label for="mdp">Mot de Passe</label>
                        <input type="password" id="mdp" name="mdp" class="form-control" placeholder="Saisir votre mot de passe" pattern="[A-Za-z0-9]{1,}" title="Uniquement des lettres (non accentuées) et des chiffres" required/>
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
                if($errAuth){
                    echo "<div class=\"alert alert-danger\"><strong>Erreur authentification !</strong> Pseudo ou mot de passe incorrect</div>";
                }
            ?>
        </div>
    </body>
</html>
