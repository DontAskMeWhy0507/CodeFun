import java.util.Objects;

public class Square extends Rectangle {
    public Square() {
    }

    public Square(double side) {
        super(side, side);
    }

    public Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    public Square(Point topLeft, double side, String color, boolean filled) {
        super(topLeft, side, side, color, filled);
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
        return "Square["
                + "topLeft=" + getTopLeft().toString()
                + ",side=" + getSide()
                + ",color=" + getColor()
                + ",filled=" + isFilled() + "]";
    }

    /**
     * Khong co gi.
     */
    public boolean equals(Object o) {
        if (o instanceof Square) {
            Square s = (Square) o;
            return Math.abs(getWidth() - s.getWidth()) < 0.001
                    && getTopLeft().equals(s.getTopLeft());
        }
        return false;
     }

     public int hashCode() {
         return Objects.hash(topLeft, width);
     }
}
