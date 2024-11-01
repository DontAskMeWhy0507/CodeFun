import java.util.Iterator;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;


public class Layer {
    private List<Shape> shapes;

    public Layer() {
        shapes = new ArrayList<>();
    }
    public void addShape(Shape shape) {
        shapes.add(shape);
    }

    /**
     * Sai hoai vay.
     */
    public void removeCircles() {
        Iterator<Shape> iterator = shapes.iterator();
        while (iterator.hasNext()) {
            Shape shape = iterator.next();
            if (shape instanceof Circle) {
                iterator.remove();
            }
        }
    }

    /**
     * Ghet javadoc.
     * @return nguoi yeu
     */
    public String getInfo() {
        StringBuilder sb = new StringBuilder("Layer of crazy shapes:\n");
        for (Shape shape : shapes) {
            sb.append(shape.toString()).append("\n");
        }
        return sb.toString();
    }

    /**
     * Noen.
     */
    public void removeDuplicates() {
        LinkedHashSet<Shape> shapeSet = new LinkedHashSet<>(shapes);
        this.shapes = new ArrayList<>(shapeSet);
    }
    
}
