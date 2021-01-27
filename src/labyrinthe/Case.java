
package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public abstract class Case {

    private Point position;

    private boolean[] open;

    private String type;

    public Case(Point position, boolean[] open2, String type) {
        this.position = position;
        this.open = open2;
        this.type = type;
    }

    /**
     * @return the position
     */
    public Point getPosition() {
        return position;
    }

    public void setPosition(Point position) {
        this.position = position;
    }

    /**
     * @return the type
     */
    public String getType() {
        return type;
    }

    /**
     * @param type the type to set
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * @return the open
     */
    public boolean[] getOpen() {
        return open;
    }

    /**
     * @param open the open to set
     */
    public void setOpen(boolean[] open) {
        this.open = open;
    }

    /**
     * Set the position of the Case above its current position
     */
    public void moveUp() {
        this.position.setLocation(this.position.getX(), this.position.getY() - 1);
    }

    /**
     * Set the position of the Case below its current position
     */
    public void moveDown() {
        this.position.setLocation(this.position.getX(), this.position.getY() + 1);
    }

    /**
     * Set the position of the Case to the left of its current position
     */
    public void moveLeft() {
        this.position.setLocation(this.position.getX() - 1, this.position.getY());
    }

    /**
     * Set the position of the Case to the right of its current position
     */
    public void moveRight() {
        this.position.setLocation(this.position.getX() + 1, this.position.getY());
    }

    public void rightRotation() {
        boolean tmpOpen0 = open[0];
        boolean tmpOpen1 = open[1];
        boolean tmpOpen2 = open[2];
        boolean tmpOpen3 = open[3];

        open[0] = tmpOpen3;
        open[1] = tmpOpen0;
        open[2] = tmpOpen1;
        open[3] = tmpOpen2;
    }

    public void leftRotation() {
        boolean tmpOpen0 = open[0];
        boolean tmpOpen1 = open[1];
        boolean tmpOpen2 = open[2];
        boolean tmpOpen3 = open[3];

        open[0] = tmpOpen1;
        open[1] = tmpOpen2;
        open[2] = tmpOpen3;
        open[3] = tmpOpen0;
    }

}
