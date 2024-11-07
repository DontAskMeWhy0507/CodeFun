public class father {
    static int staticVariable = 10; // Thuộc tính tĩnh
    int instanceVariable = 5; // Thuộc tính thể hiện

    void display() {


         System.out.println("Static Variable: " + this.staticVariable); // Lỗi biên dịch
    }

    public static void main(String[] args) {
        father obj = new father();
        obj.display();
    }
}