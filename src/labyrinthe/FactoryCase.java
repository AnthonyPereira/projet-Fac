
package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */

public class FactoryCase {

    public Cross createCross(Point position, boolean[] open, String type) {
        return new Cross(position, open, type);
    }

    public Corner createCorner(Point position, boolean[] open, String type) {
        return new Corner(position, open, type);
    }

    public Line createLine(Point position, boolean[] open, String type) {
        return new Line(position, open, type);
    }
}
