package labyrinthe;

import java.awt.Point;

/**
 * @author Pierre-Louis
 *
 */
public abstract class Player {
	private String name;
	private String color;
	private Point position;
	private Point positionDepart;
	private String[] tresor;
	private Case[] tabCase;
	private int nbCaseDispo;
    private int actualTresor;

    public int getNbCaseDispo() {
        return nbCaseDispo;
    }


    
    public void setNbCaseDispo(int nbCaseDispo) {
        this.nbCaseDispo = nbCaseDispo;
    }


	
	public Player(String name, String color, Point position, String[] tresor) {
		this.name = name;
		this.color = color;
		this.position = position;
		this.positionDepart = new Point(position);
		this.tresor = tresor;
		this.actualTresor = 0;
		this.tabCase= new Case[49];
		this.nbCaseDispo = 0;
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
		this.position.setLocation(position);
	}
	
    public Point getPositionDepart() {
        return positionDepart;
    }

    /**
	 * @return the tresor
	 */
	public String[] getTresor() {
		return tresor;
	}
	
	public String actualTresor() {
		return tresor[actualTresor];
	}
	
	public int getActualTresor() {
	    return actualTresor;
	}
	
	/**
	 * @param tresor the tresor to set
	 */
	public void setTresor(String[] tresor) {
		this.tresor = tresor;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return the color
	 */
	public String getColor() {
		return color;
	}

	/**
	 * @param color the color to set
	 */
	public void setColor(String color) {
		this.color = color;
	}
	
	public Case[] getTabCase() {
		return tabCase;
	}
	
	public abstract void jouer(Point noReplaceCase);
	
	public void resetTabCase() {
	    this.tabCase=new Case[49];
        this.nbCaseDispo = 0;
	}
	
	public void addCase(Case caseToAdd) {
	    this.tabCase[this.nbCaseDispo]=caseToAdd;
	    this.nbCaseDispo++;
	}
	
	public boolean verifSortieRoadExist(Point posPlayer) {
	    for(int i=0;i<this.nbCaseDispo;i++) {
            if(this.tabCase[i].getPosition().equals(posPlayer)) {
                return false;
            }
        }
        return !(posPlayer.getX()<0 || posPlayer.getY()<0 || posPlayer.getX()>6 || posPlayer.getY()>6);
	}
	
	public boolean verifRoadExistPosTrouver(Point posWanted, Point posPlayer) {
	    return posPlayer.getLocation().equals(posWanted.getLocation());
	}
	
	public boolean verifRoadExist(int i, Point posPlayer, Point posWanted) {
	    boolean ret = false;
	    if (i == 0 && posPlayer.getX()!=0 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()-1][(int)posPlayer.getY()].getOpen())[2]) {
            // Nord
            posPlayer.setLocation(posPlayer.getX()-1, posPlayer.getY());
            ret = roadExist(posPlayer, posWanted);
            posPlayer.setLocation(posPlayer.getX()+1, posPlayer.getY());
        }
        else if (i == 1 && posPlayer.getY()!=6 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()][(int)posPlayer.getY()+1].getOpen())[3]) {
            // Est
            posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()+1);
            ret = roadExist(posPlayer, posWanted);
            posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()-1);
        }
        else if (i == 2 && posPlayer.getX()!=6 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()+1][(int)posPlayer.getY()].getOpen())[0]) {
            // Sud
            posPlayer.setLocation(posPlayer.getX()+1, posPlayer.getY());
            ret = roadExist(posPlayer, posWanted);
            posPlayer.setLocation(posPlayer.getX()-1, posPlayer.getY());
        }
        else if (i == 3 && posPlayer.getY()!=0 && (Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()][(int)posPlayer.getY()-1].getOpen())[1]) {
            // Ouest
            posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()-1);
            ret = roadExist(posPlayer, posWanted);
            posPlayer.setLocation(posPlayer.getX(), posPlayer.getY()+1);
        }
	    return ret;
	}
	
	public boolean roadExist(Point posPlayer, Point posWanted) {
        if(verifRoadExistPosTrouver(posWanted, posPlayer)) {
            return true;
        }
        if(!verifSortieRoadExist(posPlayer)) {
            return false;
        }
        Case actualCase = Plateau.getInstance().getTabPlateau()[(int)posPlayer.getX()][(int)posPlayer.getY()];
        this.addCase(actualCase);
        boolean ret = false;
        for(int i=0; i<actualCase.getOpen().length && !ret; i++) {
            if(actualCase.getOpen()[i]) {
                ret = verifRoadExist(i, posPlayer, posWanted);
            }
        }
        return ret;
    }

	
	
	public int move(Point posWanted) {
	    resetTabCase(); 
		if(roadExist(this.position, posWanted)) {
			this.setPosition(posWanted);
			if(this.actualTresor<6 && Plateau.getInstance().getTabT()[(int)this.position.getX()][(int)this.position.getY()]!=null && this.actualTresor().equals(Plateau.getInstance().getTabT()[(int)this.position.getX()][(int)this.position.getY()].getNom())) {
			    this.actualTresor++;
		        resetTabCase();
		        return 1;
			}
			else if(this.actualTresor==6 && this.position.equals(this.positionDepart)) {
			    resetTabCase();
                return 2;
			}
		}
    	this.resetTabCase();
		return 0;
	}
}
