package abc;
public class Transaction {
    private String Operation;
    private double Amount;
    private double Balance;

    public static final String DEPOSIT = "deposit";
    public static final String WITHDRAW = "withdraw";
    
    public Transaction (String Operation, double Amount, double Balance) {
        this.Operation = Operation;
        this.Amount = Amount;
        this.Balance = Balance;
    }

    public String getOperation() {
        return Operation;
    }

    public double getAmount() {
        return Amount;
    }

    public double getBalance() {
        return Balance;
    }

    
}
