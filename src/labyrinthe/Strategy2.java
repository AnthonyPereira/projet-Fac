/**
 * 
 */
package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public class Strategy2 extends IA {

	public Strategy2(String name, String color, Point position, String[] tresor) {
		super(name, color, position, tresor);
	}

	@Override
	public void jouer(Point noReplaceCase) {
		strategie2(noReplaceCase);
	}

}
