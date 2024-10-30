
public class Circle extends Shape {
    protected double radius;

    public Circle() {}

    public Circle(double radius) {
        this.radius = radius;
    }

    public Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }
    
    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    /**
     * Trung dz.
     * @return abc.
     */
    public double getArea() {
        return Math.PI * radius * radius;
    }

    /**
     * Trung dz.
     * @return abc
     */
    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }

    /**
     * I dont Know.
     * @return abc
     */
    public String toString() {
        return "Circle[radius=" + radius
                + ",color=" + getColor()
                + ",filled=" + isFilled() + "]";
    }
}
