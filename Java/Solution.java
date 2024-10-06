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

    public int getDemoniator() {
        return denominator;
    }

    public void setDemoniator(int denominator) {
        if (denominator != 0) {
            this.denominator = denominator;
        }
    }

    /**
     * Constructor.
     */

     public Solution(int numerator, int denominator) {
         this.numerator = numerator;
         this.denominator = denominator;
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
     public void reduce() {
        int ucln = ucln(numerator, denominator);
        numerator /= ucln;
        denominator /= ucln;
     }

     /**
      * Trung dep trai.
      */
      
}