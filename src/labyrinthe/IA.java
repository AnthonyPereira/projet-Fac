/**
 * 
 */
package labyrinthe;

import java.awt.Point;
import java.security.SecureRandom;

/**
 * @author Pierre-Louis
 *
 */
public abstract class IA extends Player{
	private int difficulte;
    private SecureRandom random = new SecureRandom();

	public IA(String name, String color, Point position, String[] tresor) {
		super(name, color, position, tresor);
	}
	
	public abstract void jouer(Point noReplaceCase);

	/**
	 * @return the difficulte
	 */
	public int getDifficulte() {
		return difficulte;
	}

	/**
	 * @param difficulte the difficulte to set
	 */
	public void setDifficulte(int difficulte) {
		this.difficulte = difficulte;
	}
	
	public boolean verifPotentialMove(Point posPlayer){
	    for(int i=0;i<this.getNbCaseDispo();i++) {
            if(this.getTabCase()[i].getPosition().equals(posPlayer)) {
                return false;
            }
        }
        
        return !(posPlayer.getX()<0 || posPlayer.getY()<0 || posPlayer.getX()>6 || posPlayer.getY()>6);
	}
	
	public void locatePotentialMove(Case[][] plateau, Point posPlayer) {
	    if(!verifPotentialMove(posPlayer)) {
	        return;
	    }
        
        Case actualCase = Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()][(int)posPlayer.getY()];
        boolean[] tabOpen = actualCase.getOpen();
        this.addCase(actualCase);
        for(int i=0; i<tabOpen.length; i++) {
            if(tabOpen[i]) {
                if (i == 0 && posPlayer.getX()!=0 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()-1][(int)posPlayer.getY()].getOpen())[2]) {
                    // Nord
                    posPlayer.setLocation(posPlayer.getX()-1, posPlayer.getY());
                    locatePotentialMove(plateau, posPlayer);
                    posPlayer.setLocation(posPlayer.getX()+1, posPlayer.getY());
                }
                else if (i == 1 && posPlayer.getY()!=6 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()][(int)posPlayer.getY()+1].getOpen())[3]) {
                    // Est
                    posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()+1);
                    locatePotentialMove(plateau, posPlayer);
                    posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()-1);
                }
                else if (i == 2 && posPlayer.getX()!=6 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()+1][(int)posPlayer.getY()].getOpen())[0]) {
                    // Sud
                    posPlayer.setLocation(posPlayer.getX()+1, posPlayer.getY());
                    locatePotentialMove(plateau, posPlayer);
                    posPlayer.setLocation(posPlayer.getX()-1, posPlayer.getY());
                }
                else if (i == 3 && posPlayer.getY()!=0 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()][(int)posPlayer.getY()-1].getOpen())[1]) {
                    // Ouest
                    posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()-1);
                    locatePotentialMove(plateau, posPlayer);
                    posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()+1);
                }
            }
        }
	}
	
	public Point poseRandom(Point noReplaceCase) {
	    Point point = new Point(0,0);
        int[] cote = {0,6};
        int[] rangee = {1, 3, 5};
        int x;
        int y;
        while(point.getLocation().equals(noReplaceCase.getLocation()) || (point.getX() == 0 && point.getY()==0)) {
            int coter = this.random.nextInt(2);
            if (coter == 0) {
                x = cote[this.random.nextInt(2)];
                y = rangee[this.random.nextInt(3)];
            }
            else {
                y = cote[this.random.nextInt(2)];
                x = rangee[this.random.nextInt(3)];
            }
            point.setLocation(x, y);
        }
        return point;
	}
	
	public void strategie1(Point noReplaceCase){
		//choisir ou mettre la case
	    
		Case newCase = Plateau.getInstance().insertCase(poseRandom(noReplaceCase),Plateau.getInstance().getLastCase(),Plateau.getInstance().getLastTresor());
		Plateau.getInstance().setLastCase(newCase);
		
		//choisir un endroit ou aller
		this.resetTabCase(); 
		locatePotentialMove(Plateau.getInstance().getTabPlateau(), this.getPosition());
		move(getTabCase()[this.random.nextInt(this.getNbCaseDispo())].getPosition());
		this.resetTabCase(); 
		
	}
	
    
	public void strategie3(Point noReplaceCase) {
	    Point poseTresor;
		Point dif = new Point();
		Point min = new Point(49,49);
		Point casePlusProche = new Point();
		Case newCase = Plateau.getInstance().insertCase(poseRandom(noReplaceCase), Plateau.getInstance().getLastCase(), Plateau.getInstance().getLastTresor());
		Plateau.getInstance().setLastCase(newCase);
		if(this.getActualTresor() > 5) {
            poseTresor = this.getPositionDepart();
        }
        else {
            poseTresor = Plateau.getInstance().posTresor(this.actualTresor());
        }
		this.resetTabCase();
		locatePotentialMove(Plateau.getInstance().getTabPlateau(), this.getPosition());
		for(int i=0;i<this.getNbCaseDispo();i++) {
		    dif.setLocation(Math.abs(poseTresor.getX() - getTabCase()[i].getPosition().getX()), Math.abs(poseTresor.getY() - getTabCase()[i].getPosition().getY()) );
            if(min.getX()==49 && min.getY()==49 || min.getX()+min.getY() > dif.getX()+dif.getY()) {
                min=(Point) dif.clone();
                casePlusProche=getTabCase()[i].getPosition();
            }
		}
		this.resetTabCase();
		move(casePlusProche);		
	}
	
	public void strategie2(Point noReplaceCase) {
		if(this.random.nextFloat() < 0.5) {
			strategie3(noReplaceCase);
		}
		else {
			strategie1(noReplaceCase);
		}
	}
	
}
