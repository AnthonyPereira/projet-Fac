<?php
    session_start();
    if(!isset($_SESSION['user'])) {
        session_destroy();
        header('Location: authentification.php');
        exit();
    }
    if(!isset($_SESSION['partie']) || isset($_POST['menu'])){
        header('Location: accueil.php');
        exit();
    }

    include('classes/Jeu.php');

    $bdd = new SQLite3("projetsiam.db");
    $mytable = "parties";

    $req = "SELECT * FROM $mytable WHERE id=:id";
    $stmt = $bdd->prepare($req);
    $stmt->bindParam(':id',$_SESSION['partie'],SQLITE3_TEXT);
    $result = $stmt->execute();

    $row = $result->fetchArray();
    if(!$row) {
        header('Location: accueil.php');
        exit();
    }
    elseif ($row[6]==""){
        $jeu = new Jeu($row[5], new Joueur(1, 'Elephant', $row[3], 5), new Joueur(2, 'Rhino', $row[4], 5));
        $plateau = $jeu->getPlateau();
        $jeuSerialize = base64_encode(serialize($jeu));
        $req = "UPDATE $mytable SET jeu=:jeu WHERE id=:id";
        $stmt = $bdd->prepare($req);
        $stmt->bindParam(':jeu',$jeuSerialize,SQLITE3_TEXT);
        $stmt->bindParam(':id',$_SESSION['partie'],SQLITE3_TEXT);
        $result = $stmt->execute();
        $finPartie = null;
    }
    else {
        $jeu = unserialize(base64_decode($row[6]));
        $plateau = $jeu->getPlateau();
        $finPartie = $jeu->checkWin();
        if($finPartie != null){
            $finPartie = $finPartie->getNumJoueur();
        }
    }

    if($_SESSION['user']=="admin"){
        if(!isset($_SESSION['tourPrecedent'])){
            $_SESSION['tourPrecedent']=$row[5];
        }
        elseif($_SESSION['tourPrecedent']!=$row[5]){
            $_SESSION['choixPion']=false;
            $_SESSION['poserPion']=false;
            $_SESSION['poserCase']="";
            $_SESSION['choixCase']="";
            $_SESSION['choixDirection']="";
            $_SESSION['choixCaseDirection']="";
        }
    }

    $bonJoueur = $row[($row[5]%2)+3]==$_SESSION['user'] || $_SESSION['user']=="admin";
    if($bonJoueur){
        if (isset($_POST['inputPoserPion'])){
            $_SESSION['poserPion']=true;
            $_SESSION['rotationPion']=0;
        }
        elseif (isset($_POST['inputCasePoser'])){
            $_SESSION['poserCase']=$_POST['inputCasePoser'];
        }
        elseif (isset($_POST['inputChoixPion'])){
            $_SESSION['choixPion']=true;
            $_SESSION['choixCase']=$_POST['inputChoixPion'];
            $_SESSION['rotationPion']=$plateau[intval($_SESSION['choixCase'][0])][intval($_SESSION['choixCase'][1])]->getDirection();
        }
        elseif (isset($_POST['inputChoixDirection'])){
            $_SESSION['choixDirection']=intval($_POST['inputChoixDirection'][0]);
            $_SESSION['choixCaseDirection']=$_POST['inputChoixDirection'][1].$_POST['inputChoixDirection'][2];
        }
        elseif (isset($_POST['tourner'])){
            if($_SESSION['poserPion'] || $_SESSION['choixPion']){
                $_SESSION['rotationPion']+=1;
                if($_SESSION['rotationPion']==4){
                    $_SESSION['rotationPion']=0;
                }
            }
        }
        elseif (isset($_POST['valider']) || isset($_POST['inputSortirPion'])){
            $modifJeu = false;
            if(isset($_POST['inputSortirPion'])){
                $jeu->sortirPion($_SESSION['choixCase']);
                $modifJeu=true;
            }
            elseif($_SESSION['poserPion'] && $_SESSION['poserCase']!="") {
                $jeu->poserPion($_SESSION['rotationPion'], array(intval($_SESSION['poserCase'][0]), intval($_SESSION['poserCase'][1])));
                $modifJeu=true;
            }
            elseif($_SESSION['choixCase']){
                if($plateau[intval($_SESSION['choixCase'][0])][intval($_SESSION['choixCase'][1])]->getDirection()!=$_SESSION['rotationPion']){
                    $plateau[intval($_SESSION['choixCase'][0])][intval($_SESSION['choixCase'][1])]->setDirection($_SESSION['rotationPion']);
                    $plateau[intval($_SESSION['choixCase'][0])][intval($_SESSION['choixCase'][1])]->setImage((($row[5]%2)+1).$_SESSION['rotationPion'].".gif");
                    $jeu->setPlateau($plateau);
                    $modifJeu=true;
                }
                if($_SESSION['choixCaseDirection']!=""){
                    $jeu->move(array(intval($_SESSION['choixCase'][0]), intval($_SESSION['choixCase'][1])), $_SESSION['choixDirection']);
                    $modifJeu=true;
                }
            }
            if($modifJeu==true){
                $jeu->setTour($jeu->getTour()+1);
                $tour = $row[5]+1;
                $jeuSerialize = base64_encode(serialize($jeu));
                $req = "UPDATE $mytable SET jeu=:jeu, tour=:tour WHERE id=:id";
                $stmt = $bdd->prepare($req);
                $stmt->bindParam(':jeu',$jeuSerialize,SQLITE3_TEXT);
                $stmt->bindParam(':tour',$tour,SQLITE3_TEXT);
                $stmt->bindParam(':id',$_SESSION['partie'],SQLITE3_TEXT);
                $result = $stmt->execute();
                $_SESSION['choixPion']=false;
                $_SESSION['poserPion']=false;
                $_SESSION['poserCase']="";
                $_SESSION['choixCase']="";
                $_SESSION['choixDirection']="";
                $_SESSION['choixCaseDirection']="";
                header('Location: partie.php');
                exit();
            }
        }
        elseif (isset($_POST['annuler'])){
            $_SESSION['choixPion']=false;
            $_SESSION['poserPion']=false;
            $_SESSION['poserCase']="";
            $_SESSION['choixCase']="";
            $_SESSION['choixDirection']="";
            $_SESSION['choixCaseDirection']="";
        }
    }
    else{
        $_SESSION['choixPion']=false;
        $_SESSION['poserPion']=false;
        $_SESSION['poserCase']="";
        $_SESSION['choixCase']="";
        $_SESSION['choixDirection']="";
        $_SESSION['choixCaseDirection']="";
    }

    if($_SESSION['user']=="admin"){
        $_SESSION['tourPrecedent']=$row[5];
    }
?>

<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Partie</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
        <link rel="stylesheet" href="style/style.css">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    </head>
    <body class="bg-light">
        <form enctype="multipart/form-data" method="post" action="">
            <div class="container-fluid">
                <div class="row">
                    <div class="col-md-2">
                        <input type="submit" name="menu" value="Revenir au menu principal" class="btn btn-outline-dark allMargin"/>
                    </div>
                    <div class="col-md-8">
                        <?php
                            if($finPartie == null){
                        ?>
                                <div class="text-center allMargin">
                                    <h1>Tour : Joueur <?php echo ($row[5]%2)+1; ?></h1>
                                </div>
                        <?php
                            }
                        ?>
                    </div>
                </div>
            </div>
            <div class="container">
                <?php
                    if($finPartie != null){
                ?>
                        <div class="text-center allMargin">
                            <h1>Victoire du Joueur <?php echo $finPartie; ?> !</h1>
                        </div>
                <?php
                    }
                    else{
                ?>
                <div class="row">
                    <div class="col-md-3">
                        <p class="font-weight-bold">Joueur 1 : <?php echo $row[3]; ?></p>
                        <?php
                            for ($i = 0; $i < $jeu->getJoueur1()->getNbMonstres(); $i++) {
                                echo "<img src='img/10.gif'>";
                            }
                            if (($row[5]%2)==0 && ($_SESSION['user']==$row[3] || $_SESSION['user']=="admin") && $_SESSION['choixPion']==false && $_SESSION['poserPion']==false && $jeu->getJoueur1()->getNbMonstres()>0){
                                echo "<input type='submit' name='inputPoserPion' value='Poser un pion' class='btn btn-info allMargin'/>";
                            }
                            elseif (($row[5]%2)==0 && ($_SESSION['user']==$row[3] || $_SESSION['user']=="admin") && $_SESSION['poserPion']==true){
                                echo "<p class='font-weight-bold bigTopMargin'>Pion qui va être placé :</p>";
                                $val = "img/1".$_SESSION['rotationPion'].".gif";
                                echo "<img src='$val' id='posRes1' class='reserveJ1'>";
                            }
                            elseif (($row[5]%2)==0 && ($_SESSION['user']==$row[3] || $_SESSION['user']=="admin") && $_SESSION['choixPion']==true){
                                echo "<p class='font-weight-bold bigTopMargin'>Orientation du pion choisi :</p>";
                                $val = "img/1".$_SESSION['rotationPion'].".gif";
                                echo "<img src='$val' id='posRes1' class='reserveJ1'>";
                                if ($_SESSION['choixCaseDirection']=="" && (intval($_SESSION['choixCase'][0])==0 || intval($_SESSION['choixCase'][0])==4 || intval($_SESSION['choixCase'][1])==0 || intval($_SESSION['choixCase'][1])==4)){
                                    echo "<input type='submit' name='inputSortirPion' value='Sortir le pion' class='btn btn-info allMargin'/>";
                                }
                            }
                        ?>
                    </div>
                    <div class="col-md-6">
                        <table id="monPlateau">
                            <?php
                                for ($i = 0; $i < 5; $i++) {
                                    echo "<tr>";
                                    for ($j = 0; $j < 5; $j++) {
                                        $val = $plateau[$i][$j];
                                        if ($val!="") {
                                            $img = $val->getImage();
                                        }
                            ?>
                                        <td id='$i$j' <?php if($val!=""){ echo "style='background-image: url(img/$img);'"; } ?>>
                            <?php
                                        if ($_SESSION['poserPion']){
                                            if($i==0 || $i==4 || $j==0 || $j==4){
                            ?>
                                                <input type='submit' name='inputCasePoser' value='<?php echo $i.$j ?>' class='inputChoix <?php if($_SESSION['poserCase']==$i.$j){ echo "inputChoixValider"; } ?>'/>
                            <?php
                                            }
                                        }
                                        elseif (!$_SESSION['poserPion'] && !$_SESSION['choixPion']){
                                            if($val!="" && ($row[5]%2)==0 && ($_SESSION['user']==$row[3] || $_SESSION['user']=="admin") && $val->getNom()=="Elephant"){
                            ?>
                                                <input type='submit' name='inputChoixPion' value='<?php echo $i.$j ?>' class='inputChoix'/>
                            <?php
                                            }
                                            elseif($val!="" && ($row[5]%2)==1 && ($_SESSION['user']==$row[4] || $_SESSION['user']=="admin") && $val->getNom()=="Rhino"){
                            ?>
                                                <input type='submit' name='inputChoixPion' value='<?php echo $i.$j ?>' class='inputChoix'/>
                            <?php
                                            }
                                        }
                                        elseif ($_SESSION['choixPion']){
                                            if ($_SESSION['choixCase']==$i.$j) {
                            ?>
                                                <input type='submit' name='inputChoixPion' value='<?php echo $i.$j ?>' class='inputChoix inputChoixValider'/>
                            <?php
                                            }
                                            elseif($_SESSION['choixCaseDirection']=="" && ($_SESSION['choixCase']==($i+1).$j || $_SESSION['choixCase']==($i-1).$j || $_SESSION['choixCase']==$i.($j+1) || $_SESSION['choixCase']==$i.($j-1))){
                            ?>
                                                <input type='submit' name='inputChoixDirection' value='<?php if($_SESSION['choixCase']==($i+1).$j){ echo "0".$i.$j; } elseif($_SESSION['choixCase']==($i-1).$j){ echo "2".$i.$j; } elseif($_SESSION['choixCase']==$i.($j+1)){ echo "3".$i.$j; } else{ echo "1".$i.$j; } ?>' class='inputChoix'/>
                            <?php
                                            }
                                            elseif($_SESSION['choixCaseDirection']!="" && $_SESSION['choixCaseDirection']==$i.$j){
                            ?>
                                                <input type='submit' name='inputChoixDirection' value='<?php if($_SESSION['choixCase']==($i+1).$j){ echo "0".$i.$j; } elseif($_SESSION['choixCase']==($i-1).$j){ echo "2".$i.$j; } elseif($_SESSION['choixCase']==$i.($j+1)){ echo "3".$i.$j; } else{ echo "1".$i.$j; } ?>' class='inputChoix inputChoixValider'/>
                            <?php
                                            }
                                        }
                                        echo "</td>";
                                    }
                                    echo "</tr>";
                                }
                            ?>
                        </table>
                    </div>
                    <div class="col-md-3">
                        <p class="font-weight-bold text-right">Joueur 2 : <?php echo $row[4]; ?></p>
                        <?php
                            for ($i = 0; $i < $jeu->getJoueur2()->getNbMonstres(); $i++) {
                                echo "<img src='img/20.gif' class='float-right'>";
                            }
                            if (($row[5]%2)==1 && ($_SESSION['user']==$row[4] || $_SESSION['user']=="admin") && $_SESSION['choixPion']==false && $_SESSION['poserPion']==false && $jeu->getJoueur2()->getNbMonstres()>0){
                                echo "<input type='submit' name='inputPoserPion' value='Poser un pion' class='btn btn-info allMargin float-right'/>";
                            }
                            elseif (($row[5]%2)==1 && ($_SESSION['user']==$row[4] || $_SESSION['user']=="admin") && $_SESSION['poserPion']==true){
                                echo "<p class='font-weight-bold bigTopMargin bigLeftMargin float-right'>Pion qui va être placé :</p><br>";
                                $val = "img/2".$_SESSION['rotationPion'].".gif";
                                echo "<img src='$val' id='posRes2' class='float-right'>";
                            }
                            elseif (($row[5]%2)==1 && ($_SESSION['user']==$row[4] || $_SESSION['user']=="admin") && $_SESSION['choixPion']==true){
                                echo "<p class='font-weight-bold bigTopMargin bigLeftMargin float-right'>Orientation du pion choisi :</p>";
                                $val = "img/2".$_SESSION['rotationPion'].".gif";
                                echo "<img src='$val' id='posRes2' class='float-right'>";
                                if ($_SESSION['choixCaseDirection']=="" && (intval($_SESSION['choixCase'][0])==0 || intval($_SESSION['choixCase'][0])==4 || intval($_SESSION['choixCase'][1])==0 || intval($_SESSION['choixCase'][1])==4)){
                                    echo "<input type='submit' name='inputSortirPion' value='Sortir le pion' class='btn btn-info allMargin float-right'/>";
                                }
                            }
                        ?>
                    </div>
                </div>
                <?php
                    if ((($row[5]%2)==0 && $_SESSION['user']==$row[3]) || (($row[5]%2)==1 && $_SESSION['user']==$row[4]) || $_SESSION['user']=="admin"){
                ?>
                <div class="row justify-content-center">
                    <div class="col-md-2"></div>
                    <div class="col-md-2">
                        <button class="btn btn-secondary btn-block topMargin" id="tourner" name="tourner">Tourner</button>
                    </div>
                    <div class="col-md-2"></div>
                </div>
                <div class="row justify-content-center">
                    <div class="col-md-3">
                        <input type="submit" name="annuler" value="Annuler" class="btn btn-danger btn-block bigTopMargin"/>
                    </div>
                    <div class="col-md-1"></div>
                    <div class="col-md-3">
                        <input type="submit" name="valider" value="Valider" class="btn btn-success btn-block bigTopMargin" id="valider"/>
                    </div>
                </div>
                <?php
                        }
                    }
                ?>
            </div>
        </form>
    </body>
</html>
