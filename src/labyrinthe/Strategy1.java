/**
 * 
 */
package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public class Strategy1 extends IA{

	public Strategy1(String name, String color, Point position, String[] tresor) {
		super(name, color, position, tresor);
	}

	@Override
	public void jouer(Point noReplaceCase) {
		strategie1(noReplaceCase);
	}
	
}
