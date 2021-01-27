/**
 * 
 */
package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public class Strategy3 extends IA {

	public Strategy3(String name, String color, Point position, String[] tresor) {
		super(name, color, position, tresor);
	}

	@Override
	public void jouer(Point noReplaceCase) {
		strategie3(noReplaceCase);
	}
	
}
