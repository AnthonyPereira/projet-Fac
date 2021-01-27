module labyrinthe{
    exports graphics;
	
	opens graphics to javafx.fxml;
	
	requires javafx.controls;
	requires javafx.fxml;
	requires transitive javafx.graphics;
	requires java.desktop;

}