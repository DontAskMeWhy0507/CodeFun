import java.util.Objects;

public class Rectangle extends Shape {
    protected double width;
    protected double length;
    protected Point topLeft;

    /**
     * Trung dz.
     */
    public Rectangle() {
    }

    /**
     * Trung dz.
     * @param width b
     * @param length c
     */
    public Rectangle(double width, double length) {
        this.width = width;
        this.length = length;
    }

    /**
     * Abc.
     * @param width a
     * @param length b
     * @param color c
     * @param filled d
     */
    public Rectangle(double width, double length, String color, boolean filled) {
        super(color, filled);
        this.width = width;
        this.length = length;
    }
    
    /**
     * Khong co gi dau.
     * @param topLeft aab
     * @param width asdf
     * @param length asd fas
     * @param color asdf
     * @param filled asdf asd
     */
    public Rectangle(Point topLeft, double width, double length, String color, boolean filled) {
        super(color, filled);
        this.topLeft = topLeft;
        this.width = width;
        this.length = length;
    }

    public Point getTopLeft() {
        return topLeft;
    }

    public void setTopLeft(Point topLeft) {
        this.topLeft = topLeft;
    }

    /**
     * Trung dz.
     * @return abc
     */
    public double getWidth() {
        return width;
    }

    /**
     *  Trung dz.
     * @param width abc
     */
    public void setWidth(double width) {
        this.width = width;
    }

    public double getLength() {
        return length;
    }

    /**
     * Trung dz.
     * @param length abc
     */
    public void setLength(double length) {
        this.length = length;
    }

    /**
     * Trung dz.
     * @return abc
     */
    public double getArea() {
        return width * length;
    }

    /**
     * Trung dz.
     * @return abc
     */
    public double getPerimeter() {
        return 2 * (width + length);
    }

    /**
     * Trung dz.
     * @return abc
     */
    public String toString() {
        return "Rectangle["
                + "topLeft=" + topLeft.toString()
                + ",width=" + width
                + ",length=" + length
                + ",color=" + getColor()
                + ",filled=" + isFilled() + "]";
    }

    /**
     * Khong co gi dau.
     */
    public boolean equals(Object o) {
        if (o instanceof Rectangle) {
            Rectangle r = (Rectangle) o;
            return Math.abs(r.getLength() - length) < 0.001
                    && Math.abs(r.getWidth() - width) < 0.001
                    && r.getTopLeft().equals(topLeft);
        }
        return false;
     }

     public int hashCode() {
            return Objects.hash(topLeft, width, length);
     }
}
