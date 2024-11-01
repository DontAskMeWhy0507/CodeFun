import java.util.ArrayList;
public class Layer {
    private ArrayList<Shape> shapes;

    public Layer() {
        shapes = new ArrayList<>();
    }
    
    public void addShape(Shape shape) {
        shapes.add(shape);
    }

    public void removeCircles() {
        for (int i = 0; i < shapes.size(); i++) {
            if (shapes.get(i) instanceof Circle) {
                shapes.remove(i);
                i--;
            }
        }
    }

    public String getInfo() {
        StringBuilder info = "Layer of crazy shapes: \n";
        for (Shape shape : shapes) {
            info.append(shape.toString() + "\n");
        }
    }

    public void removeDuplicates() {
        
    }
 
}
