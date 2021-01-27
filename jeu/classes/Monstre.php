<?php
    class Monstre {
        private $nom;
        private $position;
        private $direction;
        private $image;

        public function __construct($nom, $position, $direction, $image){
            $this->direction = $direction;
            $this->image = $image;
            $this->position = $position;
            $this->nom = $nom;
        }

        public function getNom(){
            return $this->nom;
        }

        public function getPosition(){
            return $this->position;
        }

        public function getDirection(){
            return $this->direction;
        }

        public function getImage(){
            return $this->image;
        }

        public function setNom($nom){
            $this->nom = $nom;
        }

        public function setPosition($position){
            $this->position = $position;
        }

        public function setDirection($direction){
            $this->direction = $direction;
        }

        public function setImage($image){
            $this->image = $image;
        }
    }
?>