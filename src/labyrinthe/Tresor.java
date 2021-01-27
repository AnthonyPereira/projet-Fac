/**
 * 
 */

package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public abstract class Tresor {

    private int id;

    private String nom;

    private Point position;

    public Tresor(int id, String nom, Point position) {
        this.id = id;
        this.nom = nom;
        this.position = position;
    }

    /**
     * @return the position
     */
    public Point getPosition() {
        return position;
    }

    /**
     * @param position the position to set
     */
    public void setPosition(Point position) {
        this.position = position;
    }

    /**
     * @return the nom
     */
    public String getNom() {
        return nom;
    }

    /**
     * @param nom the nom to set
     */
    public void setNom(String nom) {
        this.nom = nom;
    }

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

}
