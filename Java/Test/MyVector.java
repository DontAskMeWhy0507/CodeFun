public class MyVector {
    int x, y;
    public MyVector(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public MyVector add(MyVector v) {
        return new MyVector(this.x + v.x, this.y + v.y);
    }

    public String toString()
    {
        return "(" + x + "," + y + ")";
    }
}
