package graphics;

import java.awt.Point;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.GridPane;
import labyrinthe.Case;
import labyrinthe.Plateau;
import labyrinthe.Player;
import labyrinthe.Tresor;

public class ControllerGame implements Initializable {

    private static final String CONSTIMG = "/img/";
    
    @FXML
    private GridPane gridpane;

    @FXML
    private GridPane gridpaneT;

    @FXML
    private ImageView caseOut;

    private ImageView pos;

    @FXML
    private ImageView tresorOut;
    @FXML
    private ImageView currentCard;
    
    @FXML
    private GridPane gridpanePlayer;
    
    @FXML
    private ImageView jaune;
    @FXML
    private ImageView bleu;
    @FXML
    private ImageView rouge;
    @FXML
    private ImageView vert;
    @FXML
    private Label erreur;
    
    @FXML
    private AnchorPane endgame;
    @FXML
    private Label endgametxt;
    
    @FXML
    private AnchorPane tasCarte;
    @FXML
    private  ImageView currentPlayer;
    
    private int tour=0;
    private boolean cartePose=false;
    
    private String currPos;

    String[] nomPlayer = {"departJ","departB","departV","departR"};
    
    private Case[][] tab;
    
    private Player[] tabPlayer;

    private Tresor[][] tabT;

    @FXML
    private ImageView help;
    

    public void show() {
        
        showCase();
        showTresor();
        showLastcase();
        showLastTresor();
        showPlayer(0,jaune);
        showPlayer(1,bleu);
        if(Plateau.getInstance().getNbJoueur()+Plateau.getInstance().getNbIA()>2) {
            showPlayer(2,vert);
        }
        else {
            vert.setImage(null);
        }
        if(Plateau.getInstance().getNbJoueur()+Plateau.getInstance().getNbIA()>3) {
            showPlayer(3,rouge);
        }
        else {
            rouge.setImage(null);
        }
        if(tabPlayer[tour].getActualTresor()<6) {
            currentCard.setImage(new Image(getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/" + tabPlayer[tour].actualTresor()+ ".png")));
        }
        else {
            currentCard.setImage(null);
        }
        
        currentPlayer.setImage(new Image(getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/" + nomPlayer[tour]+ ".png")));

        int i =6;
        for(Node img:this.tasCarte.getChildren()) {
            ImageView image=(ImageView) img;
            if(i>tabPlayer[tour].getActualTresor()) {
                image.setImage(new Image(getClass().getResourceAsStream("/img/fond_carte.png")));
            }else {
                image.setImage(null);

            }
            i--;
        }

    }


    public void erreur(String arg) {
       this.erreur.setText(arg);
         
    }

    @FXML
    private void quit(ActionEvent e) {
        System.exit(0);
    }
    
    @FXML
    private void showHelp(ActionEvent e) throws IOException  {
        if(this.help.getImage()==null) {
        this.help.setImage(new Image(getClass().getResourceAsStream("/img/help.png")));
        }else {
            this.help.setImage(null);
        }
        
    }


    public void jouerIA() throws IOException {
        this.tabPlayer[this.tour].jouer(Plateau.getInstance().getPosInterdite());
        tourSuivant();
        
    }


    private void showPlayer(int i,ImageView p) {
        p.setY(this.tabPlayer[i].getPosition().getX()*60);
        p.setX(this.tabPlayer[i].getPosition().getY()*60);
    }

    public void rotateViewLine(boolean[] miniTab, ImageView current) {
        if (miniTab[1] && miniTab[3]) {
            current.setRotate(90);
        } else {
            current.setRotate(0);
        }
    }
    
    public void rotateViewCorner(boolean[] miniTab, ImageView current) {
        if (miniTab[0] && miniTab[1]) {
            current.setRotate(90);
        } else if (miniTab[1] && miniTab[2]) {
            current.setRotate(180);
        } else if (miniTab[2] && miniTab[3]) {
            current.setRotate(-90);
        } else {
            current.setRotate(0);
        }
    }
    
    public void rotateViewCross(boolean[] miniTab, ImageView current) {
        if (!miniTab[0]) {
            current.setRotate(-90);
        } else if (!miniTab[1]) {
            current.setRotate(0);
        } else if (!miniTab[2]) {
            current.setRotate(90);
        } else {
            current.setRotate(180);
        }
    }
    
    
    
    public void rotateCaseView(String type, boolean[] miniTab, ImageView current){
        if (type.equals("line")) {
            rotateViewLine(miniTab, current);
        } else if (type.equals("corner")) {
            rotateViewCorner(miniTab, current);
        } else if (type.equals("cross")) {
            rotateViewCross(miniTab, current);
        }
    }
    
    public void showCase() {
        int i = 0;
        int j = 0;
        for (Node node : gridpane.getChildren()) {
            boolean[] miniTab = tab[i][j].getOpen();
            ImageView current = (ImageView) node;
            String type = tab[i][j].getType();
            current.setImage(new Image(getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/"+ type + ".png")));
            rotateCaseView(type, miniTab, current);
            if (j == 6) {
                j = 0;
                i++;
            } else {
                j++;
            }
        }
    }

    
    @FXML
    private void selectDestination(MouseEvent event) throws IOException  {
        if(this.cartePose) {
            Node current=(Node) event.getSource();
            int x;
            int y;
            if(GridPane.getRowIndex(current) != null) {
                y=GridPane.getRowIndex(current);
            }else {
                y=0;
        }
        if(GridPane.getColumnIndex(current) != null) {
            x=GridPane.getColumnIndex(current);
        }else {
                x=0;
        }
        int i=this.tabPlayer[tour].move(new Point(y,x));
        if(i==1) {
            tourSuivant();
        }else if(i==2) {
            endgame.setDisable(false);
            endgame.setVisible(true);
            endgametxt.setText("Félicitation le joueur "+this.tabPlayer[tour].getName()+" a remporté la partie !!!");
        }
        show();
        }
   }
    

    @FXML
    private void switchtomenu(ActionEvent event) throws IOException {
        /* Lien Modifié */
        Parent root = FXMLLoader.load(getClass().getResource("/graphics/ViewMenu.fxml"));
        this.endgame.getScene().setRoot(root);
    }
    
    @FXML
    private void selectPos(MouseEvent event) throws IOException {
        if(!this.cartePose) {
            if (this.pos != null) {
                this.pos.setImage(null);
            }
            this.pos = (ImageView) event.getSource();
            this.pos.setImage(new Image(
                    getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/" + Plateau.getInstance().getLastCase().getType() + ".png")));
            this.currPos = event.getPickResult().getIntersectedNode().getId();
            this.pos.setRotate(this.caseOut.getRotate());
        }
    }

    @FXML
    private void rotateCase(MouseEvent event) {
        Plateau.getInstance().getLastCase().rightRotation();
        goodRotate();

    }

    @FXML
    private void moveWall(ActionEvent event) throws IOException {
        erreur("");
        if(!this.cartePose && this.currPos != null) {
            int x = Character.getNumericValue(this.currPos.charAt(0));
            int y = Character.getNumericValue(this.currPos.charAt(1));
            Case saveCase;
            saveCase = Plateau.getInstance().insertCase(new Point(x, y), Plateau.getInstance().getLastCase(),Plateau.getInstance().getLastTresor());
            if(saveCase != null) {
                this.cartePose=true;
                Plateau.getInstance().setLastCase(saveCase);
            }else {
                erreur("Placement impossible");
            }
            this.pos.setImage(null);
            this.pos = null;
            this.currPos = null;
        }
        show();
    }


    public void tourSuivant() throws IOException {
        if(this.cartePose) {
            if(Plateau.getInstance().isVariante()) {
                Plateau.getInstance().varianteVivants();
            }
            this.tour++;
            if(this.tour==Plateau.getInstance().getNbJoueur() + Plateau.getInstance().getNbIA()) {
                this.tour=0;
            }
            if (this.tour >= Plateau.getInstance().getNbJoueur()) {
                this.jouerIA();
            }
            this.cartePose=false;
            show();
        }
    }
    
    
    
    public void showTresor() {
        int i = 0;
        int j = 0;
        for (Node node : gridpaneT.getChildren()) {
            ImageView current = (ImageView) node;
            if (tabT[i][j] != null) {
                current.setVisible(true); 
                current.setImage(new Image(
                        getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/" + tabT[i][j].getNom() + ".png")));
            } else {
                current.setVisible(false);
            }
            if (j == 6) {
                j = 0;
                i++;
            } else {
                j++;
            }
        }
    }

    public void rotateLine(boolean[] miniTab) {
        if (miniTab[1] && miniTab[3]) {
            caseOut.setRotate(90);
        } else {
            caseOut.setRotate(0);
        }
    }
    
    public void rotateCorner(boolean[] miniTab) {
        if (miniTab[0] && miniTab[1]) {
            caseOut.setRotate(90);
        } else if (miniTab[1] && miniTab[2]) {
            caseOut.setRotate(180);
        } else if (miniTab[2] && miniTab[3]) {
            caseOut.setRotate(-90);
        } else {
            caseOut.setRotate(0);
        }
    }
    
    public void rotateCross(boolean[] miniTab) {
        if (!miniTab[0]) {
            caseOut.setRotate(-90);
        } else if (!miniTab[1]) {
            caseOut.setRotate(0);
        } else if (!miniTab[2]) {
            caseOut.setRotate(90);
        } else {
            caseOut.setRotate(180);
        }
    }
    
    public void goodRotate() {
        String type = Plateau.getInstance().getLastCase().getType();
        boolean[] miniTab = Plateau.getInstance().getLastCase().getOpen();
        if (type.equals("line")) {
            rotateLine(miniTab);
        } else if (type.equals("corner")) {
            rotateCorner(miniTab);
        } else if (type.equals("cross")) {
            rotateCross(miniTab);
        }
        if (this.pos != null) {
            this.pos.setRotate(this.caseOut.getRotate());
        }
    }

    public void showLastcase() {
        this.caseOut.setImage(new Image(
                getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/" + Plateau.getInstance().getLastCase().getType() + ".png")));
        goodRotate();

    }
    public void showLastTresor() {
        if(Plateau.getInstance().getLastTresor() != null) {
        this.tresorOut.setImage(new Image(
                getClass().getResourceAsStream(CONSTIMG+Plateau.getInstance().getTheme()+"/" + Plateau.getInstance().getLastTresor().getNom() + ".png")));
    }else {
        this.tresorOut.setImage(null);
    }
    }
    

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        endgame.setDisable(true);
        endgame.setVisible(false);
        endgametxt.setText(null);
        Plateau.getInstance().generatePlateau(Plateau.getInstance().getNbJoueur(), Plateau.getInstance().getNbIA(), Plateau.getInstance().getDiff());
        this.tabPlayer=Plateau.getInstance().getTabPlayer();
        this.tab = Plateau.getInstance().getTabPlateau();
        this.tabT = Plateau.getInstance().getTabT();
        show();

    }

}
