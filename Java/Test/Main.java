class A {
    public void methodA() {
        System.out.println("Method in class A");
    }
}

class B extends A {
    @Override
    public void methodA() {
        System.out.println("Method in class B");
    }

    public void methodB() {
        System.out.println("Method specific to class B");
    }
}

public class Main {
    public static void main(String[] args) {
        A a = new B();
        a.methodA(); // This will call the overridden method in class B
        // a.methodB(); // This will cause a compile-time error because methodB() is not defined in class A
    }
}