import edu.princeton.cs.introcs.StdDraw;

public class Heart {
    public static void main(String[] args) {
        StdDraw.setXScale(-2, 2);
        StdDraw.setYScale(-2, 2);
        StdDraw.setPenColor(StdDraw.RED);

        double[] xs = {-1, 0, 1, 0};
        double[] ys = {0, -1, 0, 1};
        StdDraw.filledPolygon(xs, ys);

        StdDraw.filledCircle(-0.5, 0.5, 0.5 / Math.sqrt(2));
        StdDraw.filledCircle(0.5, 0.5, 0.5 / Math.sqrt(2));
    }
}