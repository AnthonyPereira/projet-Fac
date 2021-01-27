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
    $currentPage = 'supprimerCpte';

    $bdd = new SQLite3("projetsiam.db");

    $cpteSuppr = false;
    $errSuppr = false;
    if(isset($_POST['supprimer'])) {
        $mytable = "parties";
        $req = "SELECT id FROM $mytable WHERE joueur1=:joueur1 OR joueur2=:joueur2";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':joueur1',$_POST['supprimer'],SQLITE3_TEXT);
        $stmt->bindParam(':joueur2',$_POST['supprimer'],SQLITE3_TEXT);
        $result = $stmt->execute();

        if(!$result->fetchArray()) {
            $mytable = "utilisateurs";
            $req = "DELETE FROM $mytable WHERE pseudo=:pseudo";
            $stmt = $bdd->prepare($req);
            $stmt->bindParam(':pseudo', $_POST['supprimer'], SQLITE3_TEXT);
            $result = $stmt->execute();
            $cpteSuppr = true;
        }
        else{
            $errSuppr = true;
        }
    }
    $mytable = "utilisateurs";
?>

<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Supprimer compte</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    </head>
    <body>
        <?php include('navbar.php'); ?>
        <div class="jumbotron text-center">
            <h1>Supprimer un compte joueur</h1>
        </div>
        <div class="container">
            <form enctype="multipart/form-data" method="post" action="">
                <div class="row">
                    <div class="col-md-4 offset-md-2">
                        <h5 class="text-center">Nom de l'utilisateur</h5>
                    </div>
                    <div class="col-md-4">
                        <h5 class="text-center">Suppression</h5>
                    </div>
                </div>
                <?php
                    $req = "SELECT * FROM $mytable";
                    $result = $bdd->query($req);
                    while ($row = $result->fetchArray()) {
                ?>
                <br>
                <div class="row">
                    <div class="col-md-4 offset-md-2 align-self-center">
                        <h6 class="text-center"><?php echo $row[1]; ?></h6>
                    </div>
                    <?php
                        if($row[1]!="admin"){
                    ?>
                    <div class="col-md-4 text-center">
                        <button type="submit" name="supprimer" value="<?php echo $row[1]; ?>" class="btn btn-danger">Supprimer</button>
                    </div>
                    <?php
                        }
                        else{
                    ?>
                    <div class="col-md-4 text-center">
                        <h6 class="text-center">Non supprimable</h6>
                    </div>
                    <?php
                        }
                    ?>
                </div>
                <?php
                    }
                ?>
            </form>
            <?php
                if($cpteSuppr){
                    echo "<div class=\"alert alert-success\"><strong>Succès suppression !</strong> Le compte du joueur a bien été supprimé</div>";
                }
                else if($errSuppr){
                    echo "<div class=\"alert alert-danger\"><strong>Erreur suppression !</strong> Vous ne pouvez supprimer un joueur avec une partie en cours</div>";
                }
            ?>
        </div>
    </body>
</html>
