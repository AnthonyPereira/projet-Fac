package graphics;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class Main extends Application {


    @Override
    public void start(Stage stage) throws Exception {
        Scene menu;
        Parent racine = FXMLLoader.load(getClass().getResource("/graphics/ViewMenu.fxml"));
        menu = new Scene(racine);
        
        menu.getStylesheets().add(getClass().getResource("/graphics/Menu.css").toExternalForm());
        stage.getIcons().add(new Image(
                getClass().getResourceAsStream("/img/icon.png")));
        stage.setResizable(false);
        stage.setScene(menu);
        stage.setTitle("Labyrinthe");
        stage.show();
        
    }
}
