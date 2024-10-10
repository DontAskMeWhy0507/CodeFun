public class solution {
    class Animal {
        String name;

        // Constructor
        public Animal(String name) {
            this.name = name;
        }
        public String getName() {
            return name;
        }
        
        //static method
        public static void staticMethod() {
            System.out.println("This is a static method");
        }

        // Method to test upcasting
        public void sound() {
            System.out.println("Animal makes sound");
        }
    }

    class Dog extends Animal {
        // Constructor 
        public Dog () {
            super("Dog");   // super() is used to call the constructor of the father class
        }

        public Dog(String name) {
            super(name);    // super() is used to call the constructor of the father class
        }

        // Method to test upcasting and downcasting
        public void sound() {
            System.out.println("Dog barks");
        }

        public void dogRun() {
            System.out.println("Dog is running");
        }

        // Method to test static method
        
    }

    
    String nameInfor (Animal a) {
        return a.getName();
    }

    public static void main(String[] args) {
        solution s = new solution();

        // Upcasting
        Animal a = s.new Dog();
        a.sound();      // prints "Dog barks" because sound method is overridden in Dog class
     //  a.dogRun();     // error: cannot find symbol because dogRun method is not in Animal class
        // Conclusion: We can only call methods that are in father class if we upcast the object.

        // Downcasting
        if (a instanceof Dog) { // check if a is an instance (object) of Dog class
            Dog d = (Dog) a;
            d.sound();      // prints "Dog barks"
            d.dogRun();     // prints "Dog is running"
        }   else {
            System.out.println("a is not an instance of Dog class");
        }
 

        // method that have parameter of type father class can accept objec that is instance of child class
        Dog dogg = s.new Dog("Bobby");
        System.out.println(s.nameInfor(dogg)); // prints the name of the dog
        
        //Lien ket dong va lien ket tinh

    }
}