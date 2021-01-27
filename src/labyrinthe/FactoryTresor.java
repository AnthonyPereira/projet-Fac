/**
 * 
 */

package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public class FactoryTresor {

    public TresorObject createTresor(int nbTresors, String name, Point p) {
        return new TresorObject(nbTresors, name, p);
    }

    public Monstre createMonstre(int id, String name, Point p) {
        return new Monstre(id, name, p);
    }

    public Start createStart(int id, String name, Point p) {
        return new Start(id, name, p);
    }
}
