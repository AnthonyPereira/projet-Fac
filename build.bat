 @ECHO OFF
ant -Dlib="%JAVAFX_HOME%/lib" -Dview="src" -Djarname="labyrinthe" build && java --module-path "%JAVAFX_HOME%/lib;labyrinthe.jar" --module "labyrinthe/graphics.Main" &