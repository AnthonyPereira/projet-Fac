
package labyrinthe;

import java.awt.Point;
import java.security.SecureRandom;

public class Plateau {
    
    private static final String LINE = "line";
    private static final String CROSS = "cross";
    private static final String CORNER = "corner";
    private static Plateau instance;
    
    private Case[][] tabPlateau = new Case[7][7];

    private Tresor[][] tabT = new Tresor[7][7];

    private Player[] tabPlayer = new Player[4];

    private FactoryCase f = new FactoryCase();

    private FactoryTresor t = new FactoryTresor();
    
    private FactoryPlayer p = new FactoryPlayer();

    private String[] nomMonstre = { "ARAIGNEE", "CHAUVE_SOURIS", "CHOUETTE", "DINOSAURE", "FANTOME", "FEE",
            "GENIE", "RAT", "SALAMANDRE", "SCARABEE", "SPHYNX", "TROLL" };

    private Tresor[] tabMonster = new Tresor[12];

    private Case[] tabOtherCase = new Case[34];

    private Case lastCase;
    
    private Tresor lastTresor;
    
    private Point posInterdite;
    
    String[][] tabCard = new String[4][6];

    int nbTresors = 0;
    
    private SecureRandom rand = new SecureRandom();

    private int nbJoueur=4;
    private int nbIA=0;
    private boolean variante=false;
    private String theme="Defaut";
    private int diff=1; 
    
    public int getNbJoueur() {
        return nbJoueur;
    }

    
    public boolean isVariante() {
        return variante;
    }

    public void setVariante(boolean variante) {
        this.variante = variante;
    }

    public String getTheme() {
        return theme;
    }

    public void setTheme(String theme) {
        this.theme = theme;
    }

    public void setNbJoueur(int nbJoueur) {
        this.nbJoueur = nbJoueur;
    }
    
    public int getNbIA() {
        return nbIA;
    }
    
    public void setNbIA(int nbIA) {
        this.nbIA = nbIA;
    }

    public int getDiff() {
        return diff;
    }

    public void setDiff(int diff) {
        this.diff = diff;
    }
    
    public void setLastCase(Case lastCase) {
        this.lastCase = lastCase;
    }

    public Point getPosInterdite() {
        return posInterdite;
    }

    public Case[] shuffleCase() {
        for (int i = 0; i < 34; i++) {
            int x = rand.nextInt(34);

            Case tmp = tabOtherCase[x];
            tabOtherCase[x] = tabOtherCase[i];
            tabOtherCase[i] = tmp;
        }
        return tabOtherCase;
    }

    public Tresor[] shuffleTresor() {
        for (int i = 0; i < 12; i++) {
            int x = rand.nextInt(12);

            Tresor tmp = tabMonster[x];
            tabMonster[x] = tabMonster[i];
            tabMonster[i] = tmp;
        }
        return tabMonster;
    }
    
    public Case[][] getTabPlateau() {
        return tabPlateau;
    }


    
    public void setTabPlateau(Case[][] tabPlateau) {
        this.tabPlateau = tabPlateau;
    }


    
    public Tresor[][] getTabT() {
        return tabT;
    }


    
    public void setTabT(Tresor[][] tabT) {
        this.tabT = tabT;
    }


    
    public String[] getNomMonstre() {
        return nomMonstre;
    }


    
    public void setNomMonstre(String[] nomMonstre) {
        this.nomMonstre = nomMonstre;
    }


    
    public Tresor[] getTabMonster() {
        return tabMonster;
    }


    
    public void setTabMonster(Tresor[] tabMonster) {
        this.tabMonster = tabMonster;
    }


    
    public Case[] getTabOtherCase() {
        return tabOtherCase;
    }


    
    public void setTabOtherCase(Case[] tabOtherCase) {
        this.tabOtherCase = tabOtherCase;
    }


    
    public String[][] getTabCard() {
        return tabCard;
    }


    
    public void setTabCard(String[][] tabCard) {
        this.tabCard = tabCard;
    }


    
    public int getNbTresors() {
        return nbTresors;
    }


    
    public void setNbTresors(int nbTresors) {
        this.nbTresors = nbTresors;
    }


    
    public Case getLastCase() {
        return lastCase;
    }


    
    public void setTabPlayer(Player[] tabPlayer) {
        this.tabPlayer = tabPlayer;
    }


    
    public void setPosInterdite(Point posInterdite) {
        this.posInterdite = posInterdite;
    }

    public void generateOtherCase() {
        // generation des autres cases que l'on stock dans un tableau
        int nbOCase = 0;
        for (int i = 0; i < 12; i++) {
            tabOtherCase[nbOCase] = f.createLine(null, new boolean[] { true, false, true, false },
                    LINE);
            nbOCase++;
        }
        for (int i = 0; i < 16; i++) {
            tabOtherCase[nbOCase] = f.createCorner(null, new boolean[] { false, true, true, false },
                    CORNER);
            nbOCase++;
        }
        for (int i = 0; i < 6; i++) {
            tabOtherCase[nbOCase] = f.createCross(null, new boolean[] { false, true, true, true },
                    CROSS);
            nbOCase++;
        }
        do {
            tabOtherCase = shuffleCase();
        }while(tabOtherCase[33].getType().equals(CROSS));
    }

    public void generateMonster() {
        // generation des autres tresors que l'on stock dans un tableau
        for (int j = 0; j < 12; j++) {
            tabMonster[j] = t.createMonstre(nbTresors, nomMonstre[j], null);
        }
    }

    public void addToField() {

        // On remplie la matrice de cases
        int nbCasePlace = 0;
        for (int j = 0; j <= 6; j += 2) {
            for (int h = 1; h <= 5; h += 2) {
                tabOtherCase[nbCasePlace].setPosition(new Point(j, h));
                int x = rand.nextInt(5);
                for (int swap = 0; swap < x; swap++) {
                    tabOtherCase[nbCasePlace].rightRotation();
                }
                tabPlateau[j][h] = tabOtherCase[nbCasePlace];
                nbCasePlace++;
            }
        }
        for (int j = 1; j <= 5; j += 2) {
            for (int h = 0; h <= 6; h += 1) {
                tabOtherCase[nbCasePlace].setPosition(new Point(j, h));
                int x = rand.nextInt(5);
                for (int swap = 0; swap < x; swap++) {
                    tabOtherCase[nbCasePlace].rightRotation();
                }
                tabPlateau[j][h] = tabOtherCase[nbCasePlace];
                nbCasePlace++;
            }
        }
        lastCase = tabOtherCase[33];
        posInterdite=new Point();
        
        
    }
    
    public Point verifAndAddMonster(Point nbTresorPlace, int k, int h, int cpt){
        if (nbTresorPlace.getX() < 6 && tabPlateau[k][h].getType().equals(CROSS) && tabT[k][h] == null) {
            tabMonster[(int)nbTresorPlace.getX() ].setPosition(new Point(k, h));
            tabT[k][h] = tabMonster[(int)nbTresorPlace.getX() ];
            nbTresorPlace.setLocation(nbTresorPlace.getX()+1, nbTresorPlace.getY());
        } 
        if (((int)nbTresorPlace.getY()  < 6 && tabPlateau[k][h].getType().equals(CORNER) && tabT[k][h] == null) && (rand.nextDouble() > 0.5 || cpt>3)) {
            tabMonster[(int)nbTresorPlace.getY()  + 6].setPosition(new Point(k, h));
            tabT[k][h] = tabMonster[(int)nbTresorPlace.getY()  + 6];
            nbTresorPlace.setLocation(nbTresorPlace.getX(), nbTresorPlace.getY()+1);
        }
        if (nbTresorPlace.getX()  < 6 && tabPlateau[h][k].getType().equals(CROSS) && tabT[h][k] == null) {
            tabMonster[(int)nbTresorPlace.getX() ].setPosition(new Point(h, k));
            tabT[h][k] = tabMonster[(int)nbTresorPlace.getX() ];
            nbTresorPlace.setLocation(nbTresorPlace.getX()+1, nbTresorPlace.getY());
        }
        if (((int)nbTresorPlace.getY()  < 6 && tabPlateau[h][k].getType().equals(CORNER) && tabT[h][k] == null) && (rand.nextDouble() > 0.5 || cpt>3)) {
            tabMonster[(int)nbTresorPlace.getY()  + 6].setPosition(new Point(h, k));
            tabT[h][k] = tabMonster[(int)nbTresorPlace.getY()  + 6];
            nbTresorPlace.setLocation(nbTresorPlace.getX(), nbTresorPlace.getY()+1);
        }
        return nbTresorPlace;
    }

    public void addMonster() {
        // On ajoute les tresors aléatoirement sur le plateau
        Point nbTresorPlace = new Point(0,0); // T, L
        int cpt = 1;
        while (nbTresorPlace.getX() < 6 || nbTresorPlace.getY() < 6) {
            for (int k = 1; k <= 5; k += 2) {
                for (int h = 0; h <= 6; h += 1) {
                    nbTresorPlace = verifAndAddMonster(nbTresorPlace, k, h, cpt);
                }
            }
            cpt++;
        }
    }

    public void addStaticCase() {
        // angle des points de départ
        tabPlateau[0][0] = f.createCorner(new Point(0, 0),
                new boolean[] { false, true, true, false }, CORNER);
        tabPlateau[0][6] = f.createCorner(new Point(0, 6),
                new boolean[] { false, false, true, true }, CORNER);
        tabPlateau[6][0] = f.createCorner(new Point(6, 0),
                new boolean[] { true, true, false, false }, CORNER);
        tabPlateau[6][6] = f.createCorner(new Point(6, 6),
                new boolean[] { true, false, false, true }, CORNER);

        // case static du jeu
        tabPlateau[0][2] = f.createCross(new Point(0, 2), new boolean[] { false, true, true, true },
                CROSS);
        tabPlateau[0][4] = f.createCross(new Point(0, 4), new boolean[] { false, true, true, true },
                CROSS);
        tabPlateau[2][0] = f.createCross(new Point(2, 0), new boolean[] { true, true, true, false },
                CROSS);
        tabPlateau[2][2] = f.createCross(new Point(2, 2), new boolean[] { true, true, true, false },
                CROSS);
        tabPlateau[2][4] = f.createCross(new Point(2, 4), new boolean[] { false, true, true, true },
                CROSS);
        tabPlateau[2][6] = f.createCross(new Point(2, 6), new boolean[] { true, false, true, true },
                CROSS);
        tabPlateau[4][0] = f.createCross(new Point(4, 0), new boolean[] { true, true, true, false },
                CROSS);
        tabPlateau[4][2] = f.createCross(new Point(4, 2), new boolean[] { true, true, false, true },
                CROSS);
        tabPlateau[4][4] = f.createCross(new Point(4, 4), new boolean[] { true, false, true, true },
                CROSS);
        tabPlateau[4][6] = f.createCross(new Point(4, 6), new boolean[] { true, false, true, true },
                CROSS);
        tabPlateau[6][2] = f.createCross(new Point(6, 2), new boolean[] { true, true, false, true },
                CROSS);
        tabPlateau[6][4] = f.createCross(new Point(6, 4), new boolean[] { true, true, false, true },
                CROSS);
    }

    public void addTresor() {
        int nbTresorsPlaces = 0;
        // tresor objet static
        String[] tresorPlateau = {"CRANE","EPEE","SAC_DE_PIECES","CLEFS","EMERAUDE","ARMURE","GRIMOIRE","COURONNE","COFFRE_AU_TRESORS","CHANDELIER","CARTE_AU_TRESORS","ANNEAU_D_OR"};
        Point[] pointTresor = {new Point(0, 2), new Point(0, 4), new Point(2, 0), new Point(2, 2), new Point(2, 4), new Point(2, 6), new Point(4, 0), new Point(4, 2),new Point(4, 4), new Point(4, 6),  new Point(6, 2), new Point(6, 4)};
        for(int i=0; i<tresorPlateau.length;i++) {
            tabT[(int)pointTresor[i].getX()][(int)pointTresor[i].getY()] = t.createTresor(nbTresorsPlaces, tresorPlateau[i], pointTresor[i]);
        }
    }

    public void addStart() {
        // ajout des points de départ des joueurs
        tabT[0][0] = t.createStart(0, "departJ", new Point(0, 0));
        tabT[0][6] = t.createStart(1, "departB", new Point(0, 6));
        tabT[6][0] = t.createStart(2, "departV", new Point(6, 0));
        tabT[6][6] = t.createStart(3, "departR", new Point(6, 6));
    }
    // creation des listes des Tresors à recuperer par les jouers via un tableau.

    public String[][] generateListeTresors(int nbJoueurs) {
        String[][] tabRet = new String[nbJoueurs][];
        String[] tabTresors = new String[24];

        for (int i = 0; i < nbJoueurs; i++) {
            tabRet[i] = new String[24 / nbJoueurs];
        }

        int i = 0;
        for (TresorEnum monTresor : TresorEnum.values()) {
            tabTresors[i++] = monTresor.toString();
        }

        int x;
        for (i = 0; i < 24; i++) {
            x = rand.nextInt(24);
            String tmp = tabTresors[x];
            tabTresors[x] = tabTresors[i];
            tabTresors[i] = tmp;
        }

        int k = 0;
        for (i = 0; i < nbJoueurs; i++) {
            for (int j = 0; j < (24 / nbJoueurs); j++) {
                tabRet[i][j] = tabTresors[k++];
            }
        }

        return tabRet;
    }
    
    public void generatePlayer(int nbJoueurs, int nbIA, int difficulte) {
        String[] couleur = {"Jaune","Bleu","Vert","Rouge"};
        Point[] point = {new Point(0,0),new Point(0,6),new Point(6,0),new Point(6,6)}; 
        
        for(int i=0; i<nbJoueurs; i++) {
            getTabPlayer()[i] = p.createHuman(couleur[i], couleur[i],point[i], tabCard[i]);
        }
        for(int i=nbJoueurs; i<nbJoueurs+nbIA; i++) {
            if(difficulte==1) { 
                getTabPlayer()[i] = p.createrIA1(couleur[i], couleur[i],point[i], tabCard[i]);   
            }
            else if(difficulte==2) {
                getTabPlayer()[i] = p.createrIA2(couleur[i], couleur[i],point[i], tabCard[i]);   
            }
            else if(difficulte==3) {
                getTabPlayer()[i] = p.createrIA3(couleur[i], couleur[i],point[i], tabCard[i]);   
            }
        }
    }

    public Player[] getTabPlayer() {
        return tabPlayer;
    }

    public void generatePlateau(int nbJoueur, int nbIA, int difficulte) {
        tabPlateau = new Case[7][7];
        tabT = new Tresor[7][7];
        tabPlayer = new Player[4];
        addStaticCase();
        addTresor();
        addStart();
        generateOtherCase();
        generateMonster();
        tabCard= generateListeTresors(4);
        generatePlayer(nbJoueur, nbIA, difficulte);
        // on melange nos tab pour remplir le plateau aléatoirement
        tabMonster = shuffleTresor();
        addToField();
        addMonster();
    }

    public static Plateau getInstance() {
        if(instance == null) {
            instance = new Plateau();
        }
        return instance;
    }

    public int[] shuffleT(int[] idT) {
        for (int i = 0; i < 24; i++) {
            int x = rand.nextInt(24);
            int tmp = idT[x];
            idT[x] = idT[i];
            idT[i] = tmp;
        }
        return idT;
    }

    
    public Tresor getLastTresor() {
        return lastTresor;
    }

    
    public void setLastTresor(Tresor lastTresor) {
        this.lastTresor = lastTresor;
    }
    
    public void moveColonne(int ligne, int colonne) {
        int direct = (3-ligne)/3;
        this.lastTresor = this.tabT[6-ligne][colonne];
        for (int i=(6-ligne); i!=ligne; i-=direct) {
            this.tabPlateau[i][colonne] = this.tabPlateau[i-direct][colonne];
            this.tabPlateau[i][colonne].setPosition(new Point(i,colonne));
            this.tabT[i][colonne]= this.tabT[i-direct][colonne];
        }
        for(int i=0; i<this.nbJoueur+this.nbIA; i++) {
            if(this.tabPlayer[i].getPosition().getY()==colonne) {
                this.tabPlayer[i].getPosition().setLocation(this.tabPlayer[i].getPosition().getX()+direct, this.tabPlayer[i].getPosition().getY());
                if(this.tabPlayer[i].getPosition().getX()==(6-ligne)+direct) {
                    this.tabPlayer[i].getPosition().setLocation(ligne, this.tabPlayer[i].getPosition().getY());
                }
            }
        }
    }
    
    public void moveLigne(int ligne, int colonne) {
        int direct = (3-colonne)/3;
        this.lastTresor = this.tabT[ligne][6-colonne];
        for (int i=(6-colonne); i!=colonne; i-=direct) {
            this.tabPlateau[ligne][i] = this.tabPlateau[ligne][i-direct];
            this.tabPlateau[ligne][i].setPosition(new Point(ligne,i));
            this.tabT[ligne][i]= this.tabT[ligne][i-direct];
        }
        for(int i=0; i<this.nbJoueur+this.nbIA; i++) {
            if(this.tabPlayer[i].getPosition().getX()==ligne) {
                this.tabPlayer[i].getPosition().setLocation(this.tabPlayer[i].getPosition().getX(), this.tabPlayer[i].getPosition().getY()+direct);
                if(this.tabPlayer[i].getPosition().getY()==(6-colonne)+direct) {
                    this.tabPlayer[i].getPosition().setLocation(this.tabPlayer[i].getPosition().getX(), colonne);
                }
            }
        }
    }
    
    /*
     * Fonction qui insère une case au Point point
     * Ayant :
     * x -> la ligne
     * y -> la colonne
     */
    public Case insertCase(Point point, Case insertCase, Tresor insertTresor) {
        int ligne = (int) point.getX();
        int colonne = (int) point.getY();

        if (posInterdite.equals(point)) {
            /* Lorsque qu'on choisit une case qui n'est pas sur un bord */
            return null;
        } 
        else {
            Case oldCase = null;

            if (ligne == 0 || ligne == 6) {
                oldCase = this.tabPlateau[6-ligne][colonne];
                moveColonne(ligne, colonne);
            }
            else if (colonne == 0 || colonne == 6) {
                oldCase = this.tabPlateau[ligne][6-colonne];
                moveLigne(ligne, colonne);
            }
            
            this.tabPlateau[ligne][colonne] = insertCase;
            this.tabPlateau[ligne][colonne].setPosition(new Point(ligne,colonne));
            this.tabT[ligne][colonne]=insertTresor;
            
            if(ligne == 0 || ligne == 6) {
                posInterdite=new Point((6-ligne),colonne);
            }
            else if(colonne == 0 || colonne == 6) {
                posInterdite=new Point(ligne,(6-colonne));
            }
            return oldCase;
        }
    }
    
    public Point posTresor(String tresorRechercher) {
        for(int i=0;i < tabT.length;i++) {
            for(int j=0; j < tabT[i].length;j++) {
                if(tabT[i][j] != null && tabT[i][j].getNom().equals(tresorRechercher)) {
                    return new Point(i,j);
                }
            }
        }
        return new Point(0,0);
    }
    
    public boolean isNomMonstre(String nom) {
        for(int i=0; i<12; i++) {
            if(this.nomMonstre[i].equals(nom)) {
                return true;
            }
        }
        return false;
    }
    
    public boolean containPlayer(Case caseP) {
        int nbJ = this.nbJoueur+this.nbIA;
        for(int i=0; i<nbJ; i++) {
            if(tabPlayer[i].getPosition().equals(caseP.getPosition())) {
                return true;
            }
        }
        return false;
    }
    
    public void moveVarianteVivants(boolean[] tabOpen, int i, int j){
        if (tabOpen[0] && i!=0 && (getTabPlateau()[i-1][j].getOpen())[2] && tabT[i-1][j]==null && !containPlayer(getTabPlateau()[i-1][j]) && rand.nextDouble()>0.25) {
            tabT[i-1][j]=tabT[i][j];
            tabT[i][j]=null;
        }
        else if (tabOpen[1] && j!=6 && (getTabPlateau()[i][j+1].getOpen())[3] && tabT[i][j+1]==null && !containPlayer(getTabPlateau()[i][j+1]) && rand.nextDouble()>0.25) {
            tabT[i][j+1]=tabT[i][j];
            tabT[i][j]=null;
        }
        else if (tabOpen[2] && i!=6 && (getTabPlateau()[i+1][j].getOpen())[0] && tabT[i+1][j]==null && !containPlayer(getTabPlateau()[i+1][j]) && rand.nextDouble()>0.25) {
            tabT[i+1][j]=tabT[i][j];
            tabT[i][j]=null;
        }
        else if (tabOpen[3] && j!=0 && (getTabPlateau()[i][j-1].getOpen())[1] && tabT[i][j-1]==null && !containPlayer(getTabPlateau()[i][j-1]) && rand.nextDouble()>0.25) {
            tabT[i][j-1]=tabT[i][j];
            tabT[i][j]=null;
        }
    }
    
    public void varianteVivants() {
        boolean[] tabOpen;
        for(int i=0; i<7; i++) {
            for(int j=0; j<7; j++) {
                if(tabT[i][j]!=null && isNomMonstre(tabT[i][j].getNom())) {
                    tabOpen = getTabPlateau()[i][j].getOpen();
                    moveVarianteVivants(tabOpen, i, j);
                }
            }
        }
    }
}
