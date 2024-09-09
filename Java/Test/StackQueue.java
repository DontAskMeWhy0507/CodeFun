
public class StackQueue {
    public static void main(String[] args) {
       MyVector v1 = new MyVector(2,3);
        MyVector v2 = new MyVector(4,5);
        MyVector v3 = v1.add(v2);
        System.out.println(v3.x + " " + v3.y); ;
        System.out.println(v3);
    }

}
