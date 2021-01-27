<?php
    class Montagne {
        private $nom;
        private $position;
        private $image;

        public function __construct($nom, $position, $image){
            $this->nom = $nom;
            $this->image = $image;
            $this->position = $position;
        }

        public function getNom(){
            return $this->nom;
        }

        public function getPosition(){
            return $this->position;
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
    }
?>