public abstract class Shape {
    protected String color;
    protected boolean filled;

    /**
     * Trung dz.
     */
    public Shape() {

    }

    /**
     * Trung dz.
     * @param color a
     * @param filled bc
     */
    public Shape(String color, boolean filled) {
        this.color = color;
        this.filled = filled;
    }

    /**
     * Trung dz.
     * @return abc
     */
    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    /**
     * Trung dz.
     * @return abc
     */
    public boolean isFilled() {
        return filled;
    }

    public void setFilled(boolean filled) {
        this.filled = filled;
    }

    public abstract double getArea();

    public abstract double getPerimeter();

    /**
     * Trung dz.
     * @return String nao do
     */
    public String toString() {
        return "Shape[color=" + color
                + ",filled=" + filled + "]";
    }

}
