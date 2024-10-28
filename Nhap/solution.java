public class solution {
    private int tuSo, mauSo;
    public double giaTri(int tuSo, int mauSo) {
        if (mauSo == 0) {
            throw new IllegalArgumentException("Mau so phai khac 0");
        } else {
            double ans = (double) tuSo / mauSo;
            return ans;
        }
    }
    public static void main(String[] args) {
        solution s = new solution();
        try {
            System.out.println(s.giaTri(5, 0));
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
}