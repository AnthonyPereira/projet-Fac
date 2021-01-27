<?php
    class Joueur {
        private $numJoueur;
        private $nomPion;
        private $nom;
        private $nbMonstres;

        public function __construct($numJoueur, $nomPion, $nom, $nbMonstres){
            $this->numJoueur = $numJoueur;
            $this->nomPion = $nomPion;
            $this->nom = $nom;
            $this->nbMonstres = $nbMonstres;
        }

        public function getNumJoueur(){
            return $this->numJoueur;
        }

        public function getNomPion(){
            return $this->nomPion;
        }

        public function getNom(){
            return $this->nom;
        }

        public function getNbMonstres(){
            return $this->nbMonstres;
        }

        public function setNumJoueur($numJoueur){
            $this->numJoueur = $numJoueur;
        }

        public function setNomPion($nomPion){
            $this->nomPion = $nomPion;
        }

        public function setNom($nom){
            $this->nom = $nom;
        }

        public function setNbMonstres($nbMonstres){
            $this->nbMonstres = $nbMonstres;
        }
    }
?>