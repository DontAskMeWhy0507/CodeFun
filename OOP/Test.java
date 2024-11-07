class SuperClass {
    public static void main(String[] args) {
        System.out.println("Main method in SuperClass");
    }
}

class A extends SuperClass {
    // Không định nghĩa main()
}

public class Test {
    public static void main(String[] args) {
        A.main(args); // Gọi main từ lớp SuperClass
    }
}
