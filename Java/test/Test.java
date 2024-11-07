package test;


public class Test extends father {

    int getAge() {
        return super(age);
    }

    String getName() {
        return super(name);
    }

    public static void main(String[] args) {
        Test t = new Test();
        System.out.println(t.getAge());
        System.out.println(t.getName());
    }
}
