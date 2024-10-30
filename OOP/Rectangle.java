public class Rectangle extends Shape {
    protected double width;
    protected double length;

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
        return "Rectangle[width=" + width
                + ",length=" + length
                + ",color=" + getColor()
                + ",filled=" + isFilled() + "]";
    }
}
