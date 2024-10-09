// Import your library
// Do not change the name of the Solution class
public class Solution {
    private int numerator;
    private int denominator;

    /**
     * Get the numerator.
     * @return the numerator
     */
    public int getNumerator() {
        return numerator;
    }

    public void setNumerator(int numerator) {
        this.numerator = numerator;
    }

    public int getDenominator() {
        return denominator;
    }

    /**
     * Set the denominator.
     */
    public void setDenominator(int denominator) {
        if (denominator != 0) {
            this.denominator = denominator;
        }
    }

    /**
     * Constructor.
     */
    public Solution(int numerator, int denominator) {
        if (denominator != 0) {
            this.numerator = numerator;
            this.denominator = denominator;
        } else {
            this.numerator = numerator;
            this.denominator = 1;
        }
    }

    int ucln(int a, int b) {
        a = Math.abs(a);
        b = Math.abs(b);
        if (a == 0 || b == 0) {
            return Math.abs(a + b);
        }
        while (a != b) {
            if (a > b) {
                a -= b;
            } else {
                b -= a;
            }
        }
        return Math.abs(a);
    }

    /**
     * Trung dep trai.  
     */
    public Solution reduce() {
        int ucln = ucln(numerator, denominator);
        if (ucln == 0) {
            return this;
        }
        this.numerator /= ucln;
        this.denominator /= ucln;
        return this;
    }

    /**
     * Trung dep trai.
     * @return deptrai
     */

    public Solution multiply(Solution other) {
        if (other.denominator == 0) {
            return this;
        }
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        this.numerator = num;
        this.denominator = den;
        return this.reduce();
    }

    /**
     * Trung dep trai.
     * @return deptrai
     */
    public Solution add(Solution other) {
        if (other.denominator == 0) {
            return this;
        }
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        this.numerator = num;
        this.denominator = den;
        return this.reduce();
        
    }

    /**
     * Trung dep trai.
     * @return deptrai
     */
    public Solution subtract(Solution other) {
        if (other.denominator == 0) {
            return this;
        }
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        this.numerator = num;
        this.denominator = den;
        return this.reduce();
    }

    /**
     * Trung dep trai.
     * @return deptrai
     */
    public Solution divide(Solution other) {
        if (other.denominator == 0) {
            return this;
        }
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        this.numerator = num;
        this.denominator = den;
        return this.reduce();
    }

    /**
     * Trung dep trai.
     * @return deptrai
     */
    public boolean equals(Object obj) {
        if (obj instanceof Solution) {
            Solution other = (Solution) obj;
            return (numerator * other.denominator) == (other.numerator * denominator);
        }
        return false;
    }
}