public class Square extends Rectangle {
    public Square() {
    }

    public Square(double side) {
        super(side, side);
    }

    public Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    /**
     * Trung dz.
     * @return abc
     */
    public double getSide() {
        return super.getWidth();
    }

    public void setSide(double side) {
        setWidth(side);
        setLength(side);
    }

    /**
     * Trung dz.
     * @param side abc
     */
    public void setWidth(double side) {
        super.setWidth(side);
        super.setLength(side);
    }

    /**
     * Trung dz.
     * @param side abc
     */
    public void setLength(double side) {
        super.setLength(side);
        super.setWidth(side);
    }

    /**
     * I dont Know.
     * @return String nao do
     */
    public String toString() {
        return "Square[side=" + getSide()
                + ",color=" + getColor()
                + ",filled=" + isFilled() + "]";
    }
}
