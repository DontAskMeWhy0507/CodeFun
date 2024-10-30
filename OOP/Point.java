public class Point {
    private double pointX;
    private double pointY;
    
    public Point(double pointX, double pointY) {
        this.pointX = pointX;
        this.pointY = pointY;
    }

    public double getPointX() {
        return pointX;
    }  

    public void setPointX(double pointX) {
        this.pointX = pointX;
    }

    public double getPointY() {
        return pointY;
    }

    public void setPointY(double pointY) {
        this.pointY = pointY;
    }

    public double distance(Point newPoint) {
        return Math.sqrt((newPoint.getPointX() - this.pointX) * (newPoint.getPointX() - this.pointX) 
        + (newPoint.getPointY() - this.pointY) * (newPoint.getPointY() - this.pointY));
    }

    public boolean equal(Object o) {
        if (o instanceof Point) {   // 
            Point newPoint = (Point) o;
            return Math.abs(this.pointX - newPoint.getPointX()) <= 0.001
            && Math.abs(this.pointY - newPoint.getPointY()) <= 0.001;
        }
        return false;
    }

    @Override
    public String toString() {
        return "(" + pointX + "," + pointY + ")";
    }

    public int hashCode() {
        return (int) (pointX * 1000 + pointY * 1000);
    }


}
