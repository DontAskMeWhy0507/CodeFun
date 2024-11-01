import java.util.Objects;

public class Circle extends Shape {
    protected Point center;
    protected double radius;

    public Circle() {}

    public Circle(double radius) {
        this.radius = radius;
    }

    public Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }

    /**
     * Khong muon lam.
     * @param center asdf
     * @param radius asdf
     * @param color asdf
     * @param filled asdf as
     */
    public Circle(Point center, double radius, String color, boolean filled) {
        super(color, filled);
        this.center = center;
        this.radius = radius;
    }

    public Point getCenter() {
        return center;
    }

    public void setCenter(Point center) {
        this.center = center;
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
        return "Circle["
                + "center=" + center.toString()
                + ",radius=" + radius
                + ",color=" + getColor()
                + ",filled=" + isFilled() + "]";
    }

    /**
     * Javadoc.
     */
    public boolean equals(Object o) {
        if (o instanceof Circle) {
            Circle c = (Circle) o;
            return Math.abs(radius - c.getRadius()) < 0.001
                    && center.equals(c.getCenter());
        }
        return false;
    }

    public int hashCode() {
        return Objects.hash(center, radius);
    }


}
