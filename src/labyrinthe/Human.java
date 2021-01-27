/**
 * 
 */

package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public class Human extends Player {

    public Human(String name, String color, Point position, String[] tresor) {
        super(name, color, position, tresor);
    }

    @Override
    public void jouer(Point noReplaceCase) {
        // pas d'implementation a faire
    }
    
    
}
