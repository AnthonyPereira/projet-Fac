package labyrinthe;

import java.awt.Point;

public class FactoryPlayer {
    public Player createHuman(String nom,String color, Point position, String[] tresor) {
        return new Human(nom,color,position,tresor);
    }

    public Player createrIA1(String nom, String color,Point position,String[] tresor) {
        return new Strategy1(nom,color,position,tresor);
    }
    public Player createrIA2(String nom, String color,Point position,String[] tresor) {
        return new Strategy2(nom,color,position,tresor);
    }
    public Player createrIA3(String nom, String color,Point position,String[] tresor) {
        return new Strategy3(nom,color,position,tresor);
    }
}
