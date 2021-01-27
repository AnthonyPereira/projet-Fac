<?php
include('Joueur.php');
include('Monstre.php');
include('Montagne.php');

class Jeu{
    private $plateau;
    private $tour;
    private $joueur1;
    private $joueur2;
    private $win1;
    private $win2;

    public function __construct($tour, $joueur1, $joueur2){
        $this->plateau = array(array(null,null,null,null,null),
            array(null,null,null,null,null),
            array(null,new Montagne("Montagne", array(2,1), "rocher.gif"),new Montagne("Montagne", array(2,2), "rocher.gif"),new Montagne("Montagne", array(2,3), "rocher.gif"),null),
            array(null,null,null,null,null),
            array(null,null,null,null,null));
        $this->tour = $tour;
        $this->joueur1 = $joueur1;
        $this->joueur2 = $joueur2;
        $this->win1 = 0;
        $this->win2 = 0;
    }

    public function getPlateau(){
        return $this->plateau;
    }

    public function getTour(){
        return $this->tour;
    }

    public function getJoueur1(){
        return $this->joueur1;
    }

    public function getJoueur2(){
        return $this->joueur2;
    }

    public function setPlateau($plateau){
        $this->plateau = $plateau;
    }

    public function setTour($tour){
        $this->tour = $tour;
    }

    public function setJoueur1($joueur1){
        $this->joueur1 = $joueur1;
    }

    public function setJoueur2($joueur2){
        $this->joueur2 = $joueur2;
    }

    public function countMemeDirection($pos, $direction, $poser){
        if($poser){
            return 1+$this->countMemeDirection($pos,$direction,false);
        }
        if($this->plateau[$pos[0]][$pos[1]] != null && $this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" && $this->countDirectionOpposed($pos, $direction) > 0){
            return -1;
        }
        if($direction == 2){
            if($pos[0]<4 && $this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == $direction)){
                $pos[0]++;
                return 1+$this->countMemeDirection($pos, $direction, false);
            }
        }
        else if($direction == 0){
            if($pos[0]>0 && $this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == $direction)){
                $pos[0]--;
                return 1+$this->countMemeDirection($pos, $direction, false);
            }
        }
        else if($direction == 1){
            if($pos[1]<4 && $this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == $direction)){
                $pos[1]++;
                return 1+$this->countMemeDirection($pos, $direction, false);
            }
        }
        else if($direction == 3){
            if($pos[1]>0 && $this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == $direction)){
                $pos[1]--;
                return 1+$this->countMemeDirection($pos, $direction, false);
            }
        }
        return 0;
    }

    public function countDirectionOpposed($pos, $direction){
        $count = 0;

        if($direction == 2){
            while($pos[0]<4 && $this->plateau[$pos[0]][$pos[1]] != null){
                if($this->plateau[$pos[0]][$pos[1]] != null && $this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne"){
                    $count+=0.6;
                }
                else if($this->plateau[$pos[0]][$pos[1]]!=null && ($this->plateau[$pos[0]][$pos[1]]->getNom()=="Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == 0)) {
                    $count++;
                }
                $pos[0]++;
            }
        }
        else if($direction == 0){
            while($pos[0]>0 && $this->plateau[$pos[0]][$pos[1]] != null) {
                if($this->plateau[$pos[0]][$pos[1]] != null && $this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne"){
                    //on ne fait rien
                }
                else if ($this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == 2)) {
                    $count+=0.6;
                }
                $pos[0]--;
            }
        }
        else if($direction == 1){
            while($pos[1]<4 && $this->plateau[$pos[0]][$pos[1]] != null) {
                if($this->plateau[$pos[0]][$pos[1]] != null && $this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne"){
                    //on ne fait rien
                }
                else if ($this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == 3)) {
                    $count+=0.6;
                }
                $pos[1]++;
            }
        }
        else if($direction == 3){
            if($this->plateau[$pos[0]][$pos[1]] != null){
                while($pos[1]>0 && $this->plateau[$pos[0]][$pos[1]] != null) {
                    if($this->plateau[$pos[0]][$pos[1]] != null && $this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne"){
                        //on ne fait rien
                    }
                    else if ($this->plateau[$pos[0]][$pos[1]] != null && ($this->plateau[$pos[0]][$pos[1]]->getNom() == "Montagne" || $this->plateau[$pos[0]][$pos[1]]->getDirection() == 1)) {
                        $count+=0.6;
                    }

                    $pos[1]--;
                }
            }
        }
        return $count;
    }

    public function swap($pos1, $pos2){
        $tmp = $this->plateau[$pos1[0]][$pos1[1]];
        $this->plateau[$pos1[0]][$pos1[1]] = $this->plateau[$pos2[0]][$pos2[1]];
        $this->plateau[$pos2[0]][$pos2[1]] = $tmp;
    }

    public function push($pos, $direction, $poser){
        $savePos = $pos;
        $memeDir = $this->countMemeDirection($pos, $direction, $poser);
        $pos = $savePos;
        $dirOpo = $this->countDirectionOpposed($pos, $direction);
        $pos = $savePos;
        if($memeDir>$dirOpo) {

            //NORD
            if($direction == 0){
                $newPos=$pos;
                while($pos[0]>0 && $this->plateau[$pos[0]][$pos[1]]!=null){
                    $pos = $newPos;
                    $newPos[0]--;
                }
                if($pos[0] == 0 && $this->plateau[$pos[0]][$pos[1]] !=null){
                    if($this->plateau[$pos[0]][$pos[1]]->getNom()=="Montagne"){
                        $i=1;
                        while($this->plateau[$pos[0]+$i][$pos[1]]->getNom()=="Montagne" || $this->plateau[$pos[0]+$i][$pos[1]]->getDirection()!=$direction){
                            $i++;
                        }
                        if($this->plateau[$pos[0]+$i][$pos[1]]->getNom() == "Elephant"){
                            $this->win1 =1;
                        }
                        else {
                            $this->win2 = 1;
                        }
                    }
                    else {
                        $this->sortirPion($pos);
                    }
                }
                $pos = $newPos;
                while($pos[0]<$savePos[0]){
                    $newPos[0]++;
                    if($this->plateau[$newPos[0]][$newPos[1]] != null){
                        $this->swap($newPos,$pos);
                    }
                    $pos = $newPos;
                }
                return true;
            }
            //SUD
            if($direction == 2){
                $newPos=$pos;
                while($pos[0]<4 && $this->plateau[$pos[0]][$pos[1]]!=null){
                    $pos = $newPos;
                    $newPos[0]++;
                }
                if($pos[0] == 4 && $this->plateau[$pos[0]][$pos[1]] !=null){
                    if($this->plateau[$pos[0]][$pos[1]]->getNom()=="Montagne"){
                        $i=1;
                        while($this->plateau[$pos[0]-$i][$pos[1]]->getNom()=="Montagne"|| $this->plateau[$pos[0]-$i][$pos[1]]->getDirection()!=$direction){
                            $i++;
                        }
                        if($this->plateau[$pos[0]-$i][$pos[1]]->getNom() == "Elephant"){
                            $this->win1 =1;
                        }
                        else {
                            $this->win2 = 1;
                        }
                    }
                    else {
                        $this->sortirPion($pos);
                    }
                }
                $pos = $newPos;
                while($pos[0]>$savePos[0]){
                    $newPos[0]--;
                    if($this->plateau[$newPos[0]][$newPos[1]] != null){
                        $this->swap($newPos,$pos);
                    }
                    $pos = $newPos;
                }
                return true;
            }
            //EST
            if($direction == 1){
                $newPos=$pos;
                while($pos[1]<4 && $this->plateau[$pos[0]][$pos[1]]!=null){
                    $pos = $newPos;
                    $newPos[1]++;
                }
                if($pos[1] == 4 && $this->plateau[$pos[0]][$pos[1]] !=null){
                    if($this->plateau[$pos[0]][$pos[1]]->getNom()=="Montagne"){
                        $i=1;
                        while($this->plateau[$pos[0]][$pos[1]-$i]->getNom()=="Montagne" || $this->plateau[$pos[0]][$pos[1]-$i]->getDirection()!=$direction){
                            $i++;
                        }
                        if($this->plateau[$pos[0]][$pos[1]-$i]->getNom() == "Elephant"){
                            $this->win1 =1;
                        }
                        else {
                            $this->win2 = 1;
                        }
                    }
                    else {
                        $this->sortirPion($pos);
                    }
                }
                $pos = $newPos;
                while($pos[1]>$savePos[1]){
                    $newPos[1]--;
                    if($this->plateau[$newPos[0]][$newPos[1]] != null){
                        $this->swap($newPos,$pos);
                    }
                    $pos = $newPos;
                }
                return true;
            }

            //OUEST
            if($direction == 3){
                $newPos=$pos;
                while($pos[1]>0 && $this->plateau[$pos[0]][$pos[1]]!=null){
                    $pos = $newPos;
                    $newPos[1]--;
                }
                if($pos[1] == 0 && $this->plateau[$pos[0]][$pos[1]] !=null){
                    if($this->plateau[$pos[0]][$pos[1]]->getNom()=="Montagne"){
                        $i=1;
                        while($this->plateau[$pos[0]][$pos[1]+$i]->getNom()=="Montagne" || $this->plateau[$pos[0]][$pos[1]+$i]->getDirection()!=$direction){
                            $i++;
                        }
                        if($this->plateau[$pos[0]][$pos[1]+$i]->getNom() == "Elephant"){
                            $this->win1 =1;
                        }
                        else {
                            $this->win2 = 1;
                        }
                    }
                    else {
                        $this->sortirPion($pos);
                    }
                }
                $pos = $newPos;
                while($pos[1]<$savePos[1]){
                    $newPos[1]++;
                    if($this->plateau[$newPos[0]][$newPos[1]] != null){
                        $this->swap($newPos,$pos);
                    }
                    $pos = $newPos;
                }
                return true;
            }

        }
        return false;
    }


    public function poserPion($direction, $pos){
        if (($pos[0] == 0 || $pos[0] == 4 || $pos[1] == 0 || $pos[1] == 4)) { //&& ($this->tour < 2 && !(($pos[0] == 0 && $pos[1] == 2) || ($pos[0] == 4 && $pos[1] == 2)))
            if ($this->plateau[$pos[0]][$pos[1]] != null) {
                if(($pos[0]==0 && $direction!=2) && ($pos[0]==4 && $direction!=0) && ($pos[1]==4 && $direction!=3) && ($pos[1]==0 && $direction!=1)){
                    return false;
                }
                $savePos = $pos;
                $resultPush = $this->push($pos, $direction, true);
                $pos = $savePos;
                if ($resultPush) {
                    if($this->tour%2 == 0){
                        $this->plateau[$pos[0]][$pos[1]] = new Monstre("Elephant",$pos,$direction,"1".$direction.".gif");
                        $this->joueur1->setNbMonstres($this->joueur1->getNbMonstres() - 1);
                    }
                    else if($this->tour%2 == 1){
                        $this->plateau[$pos[0]][$pos[1]] = new Monstre("Rhino",$pos,$direction,"2".$direction.".gif");
                        $this->joueur2->setNbMonstres($this->joueur2->getNbMonstres() - 1);
                    }
                    return true;
                }
            }
            else{
                if($this->tour%2 == 0){
                    $this->plateau[$pos[0]][$pos[1]] = new Monstre("Elephant",$pos,$direction,"1".$direction.".gif");
                    $this->joueur1->setNbMonstres($this->joueur1->getNbMonstres() - 1);
                }
                else if($this->tour%2 == 1){
                    $this->plateau[$pos[0]][$pos[1]] = new Monstre("Rhino",$pos,$direction,"2".$direction.".gif");
                    $this->joueur2->setNbMonstres($this->joueur2->getNbMonstres() - 1);
                }
                return true;
            }

        }
        return false;
    }

    public function sortirPion($pos){
        if( $this->plateau[$pos[0]][$pos[1]]->getNom() == "Elephant"){
            $this->joueur1->setNbMonstres($this->joueur1->getNbMonstres() + 1);
        }
        else if( $this->plateau[$pos[0]][$pos[1]]->getNom() == "Rhino"){
            $this->joueur2->setNbMonstres($this->joueur2->getNbMonstres() + 1);
        }
        $this->plateau[$pos[0]][$pos[1]] = null;
    }

    public function move($pos, $direction){
        $newPos = $pos;
        if($direction == $this->plateau[$pos[0]][$pos[1]]->getDirection()) {
            $resultPush = $this->push($pos, $direction, false);
        }
        $pos = $newPos;
        if($direction == 0 && $this->plateau[$pos[0]-1][$pos[1]] == null){
            $newPos[0]--;
            $this->swap($pos,$newPos);
            return true;
        }
        else if($direction == 1 && $this->plateau[$pos[0]][$pos[1]+1] == null){
            $newPos[1]++;
            $this->swap($pos,$newPos);
            return true;
        }
        else if($direction == 2 && $this->plateau[$pos[0]+1][$pos[1]] == null){
            $newPos[0]++;
            $this->swap($pos,$newPos);
            return true;
        }
        else if($direction == 3 && $this->plateau[$pos[0]][$pos[1]-1] == null){
            $newPos[1]--;
            $this->swap($pos,$newPos);
            return true;
        }
        return false;
    }

    public function checkWin(){
        if($this->win1 == 1){
            return $this->joueur1;
        }
        else if($this->win2 == 1){
            return $this->joueur2;
        }
        return null;
    }
}
?>
