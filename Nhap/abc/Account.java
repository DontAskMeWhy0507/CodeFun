package abc;
import java.util.ArrayList;
public class Account {
    private double Balance;
    ArrayList<Transaction> transactions;
    private void deposit (double amount) {
        if (amount <= 0) {
            System.out.println("So tien ban nap vao khong hop le!");
            return;
        }
        Balance += amount;
        transactions.add(new Transaction(Transaction.DEPOSIT, amount, Balance));
    }

    private void withdraw (double amount) {
        if (amount <= 0) {
            System.out.println("So tien ban rut ra khong hop le!");
        } else if (amount > Balance) {
            System.out.println("So tien ban rut vuot qua so du!");
        } else {
            Balance -= amount;
            transactions.add(new Transaction(Transaction.WITHDRAW, amount, Balance));
        }
    }

    public void addTransaction (double amount, String operation) {
        if (operation.equals(Transaction.DEPOSIT)) {
            deposit(amount);
        } else if (operation.equals(Transaction.WITHDRAW)) {
            withdraw(amount);
        } else {
            System.out.println("Yeu cau khong hop le!");
        }
    }

    public void printTransaction () {
        for (int i = 0; i < transactions.size(); i++) {
            if (transactions.get(i).getOperation().equals(Transaction.DEPOSIT)) {
                System.out.printf("Giao dich %d: Nap tien $%.2f. So du luc nay: $%.2f.\n", i + 1,
                transactions.get(i).getAmount(), transactions.get(i).getBalance());
            } else {
                System.out.printf("Giao dich %d: Rut tien $%.2f. So du luc nay: $%.2f.\n", i + 1,
                transactions.get(i).getAmount(), transactions.get(i).getBalance());
            }
        }
    }
}