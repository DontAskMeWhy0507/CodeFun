import java.util.Vector;
import java.util.HashSet;

public class solution {
    class soDo {
        public static final String CIRCLE = "circle";
        public static final String RECTANGLE = "rectangle";
        public static final String TRIANGLE = "triangle";

        Vector<shape> shapes = new Vector<>();

        interface shape {
            void draw();
            void erase();
            void move(int x);
            String getType();
        }

        class circle implements shape {
            public void draw() {
                shapes.add(this);
                System.out.println("Drawing circle");
            }

            public void erase() {
                shapes.remove(this);
                System.out.println("Erasing circle");
            }

            public void move(int x) {
                System.out.println("Moving circle by " + x + " units");
            }

            public String getType() {
                return CIRCLE;
            }
        }

        class rectangle implements shape {
            public void draw() {
                shapes.add(this);
                System.out.println("Drawing rectangle");
            }

            public void erase() {
                shapes.remove(this);
                System.out.println("Erasing rectangle");
            }

            public void move(int x) {
                System.out.println("Moving rectangle by " + x + " units");
            }

            public String getType() {
                return RECTANGLE;
            }
        }

        class triangle implements shape {
            public void draw() {
                shapes.add(this);
                System.out.println("Drawing triangle");
            }

            public void erase() {
                shapes.remove(this);
                System.out.println("Erasing triangle");
            }

            public void move(int x) {
                System.out.println("Moving triangle by " + x + " units");
            }

            public String getType() {
                return TRIANGLE;
            }
        }

        public void removeDuplicates() {
            HashSet<String> seen = new HashSet<>();
            shapes.removeIf(shape -> !seen.add(shape.getType()));
            System.out.println("Removed duplicate shapes");
        }

        public void drawAllShapes() {
            for (shape s : shapes) {
                s.draw();
            }
        }

        public void eraseAllShapes() {
            for (shape s : shapes) {
                s.erase();
            }
        }

        public void moveAllShapes(int x) {
            for (shape s : shapes) {
                s.move(x);
            }
        }
    }

    public static void main(String[] args) {
        solution sol = new solution();
        soDo diagram = sol.new soDo();

        soDo.shape circle = diagram.new circle();
        soDo.shape rectangle = diagram.new rectangle();
        soDo.shape triangle = diagram.new triangle();

        circle.draw();
        rectangle.draw();
        triangle.draw();
        circle.draw(); // Drawing a duplicate circle

        diagram.removeDuplicates(); // Remove duplicate shapes

        diagram.moveAllShapes(5); // Move all shapes by 5 units
        diagram.eraseAllShapes(); // Erase all shapes
    }
}