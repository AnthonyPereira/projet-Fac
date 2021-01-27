<div class="col-md-4">
    <div class="card mb-4 shadow">
        <div class="card-header text-center"><?php echo $row[1]; ?></div>
        <div class="card-body">
            <p class="card-text">Statut : <?php if($row[4]==""){ ?> <span class="font-weight-bold text-white bg-warning">En attente d'un joueur...</span> <?php } else{ ?> <span class="font-weight-bold text-white bg-success">En cours</span> <?php } ?></p>
            <p class="card-text">Liste des joueurs :<br>J1 : <?php echo $row[3]; ?><br>J2 : <?php echo $row[4]; ?></p>
            <p class="card-text">Tour : <?php if($row[4]!=""){ ?><span class="font-weight-bold"><?php echo $row[3+($row[5]%2)]; ?></span> <?php } else{ ?><span class="font-weight-bold text-danger">Partie non débutée</span><?php } ?></p>
            <div class="d-flex justify-content-between align-items-center">
                <form enctype="multipart/form-data" method="post" action="" style="margin-bottom: 0px">
                    <div class="btn-group">
                        <?php
                            if($greenButton=="Rejoindre" || $row[4]!="") {
                        ?>
                        <button type="submit" name="<?php echo $greenButton; ?>" class="btn btn-sm btn-outline-success" value="<?php echo $row[0]; ?>"><?php echo $greenButton; ?></button>
                        <?php
                            }
                            if($_SESSION['user']=="admin"){
                        ?>
                        <button type="submit" name="supprimer" class="btn btn-sm btn-outline-danger" value="<?php echo $row[0]; ?>">Supprimer</button>
                        <?php
                            }
                        ?>
                    </div>
                </form>
                <small class="text-muted"><?php echo $row[2]; ?></small>
            </div>
        </div>
    </div>
</div>