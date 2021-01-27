
package graphics;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.CheckBox;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.stage.Stage;
import labyrinthe.Plateau;

public class Controller implements Initializable {

    @FXML
    private CheckBox check;
    
    @FXML
    private MenuButton theme;

    @FXML
    private void switchtogame(ActionEvent event) throws IOException {
        /* Lien Modifié */
        Parent root = FXMLLoader.load(getClass().getResource("/graphics/View.fxml"));
        Scene scene = new Scene(root);
        /* Lien Modifié */
        scene.getStylesheets().add(getClass().getResource("/graphics/Menu.css").toExternalForm());
        Node node = (Node) event.getSource();
        Stage stage = (Stage) node.getScene().getWindow();
        stage.setScene(scene);
    }

    @FXML
    private void quit(ActionEvent e) {
        System.exit(0);
    }
    
    @FXML
    private void setVariante(ActionEvent e) {
        Plateau.getInstance().setVariante(check.isSelected());
    }
    
    
    @FXML
    private void setdiff(ActionEvent e) throws IOException  {
        MenuItem source = (MenuItem) e.getSource();
        Plateau.getInstance().setDiff(Character.getNumericValue(source.getText().charAt(0)));
    }
    
    @FXML
    private void setNbPlayer(ActionEvent e) throws IOException  {
        MenuItem source = (MenuItem) e.getSource();
        Plateau.getInstance().setNbJoueur(Character.getNumericValue(source.getText().charAt(0)));
    }
    
    @FXML
    private void setNbIA(ActionEvent e) throws IOException {
        MenuItem source = (MenuItem) e.getSource();
        Plateau.getInstance().setNbIA(Character.getNumericValue(source.getText().charAt(0)));
    }
    
    @FXML
    private void setTheme(ActionEvent e) throws IOException {
        MenuItem source = (MenuItem) e.getSource();
        Plateau.getInstance().setTheme(source.getText());
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        if(Plateau.getInstance().isVariante()) {
            check.setSelected(true);
        }
        showThemeList(new File("./img"));
    }

    public void showThemeList(File dir) {
        File[] files = dir.listFiles();
        for (File file : files) {
            if (file.isDirectory()) {
                MenuItem menuItem = new MenuItem(file.getName());
                menuItem.setOnAction(arg0 -> {
                    try {
                        setTheme(arg0);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                });
                this.theme.getItems().add(menuItem);
            }
        }
    }
}
