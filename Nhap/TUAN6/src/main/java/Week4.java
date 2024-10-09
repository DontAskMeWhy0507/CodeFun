public class Week4 {

        public static int max2Int(int a, int b) {
                return a > b ? a : b;
        }

        public static int minArray (int[] array) {
                int min = array[0];
                for (int i = 1; i < array.length; i++) {
                        if (min > array[i]) {
                                min = array[i];
                        }
                }
                return min;
        }

        public static String calculateBMI(double weight, double height) {
                double BMI = weight / (height * height);
                if(BMI < 18.5) {
                        return "Thiếu cân";
                } else if (BMI >= 18.5 && BMI <= 22.9) {
                        return "Bình thường";
                } else if (BMI >= 23 && BMI <= 24.9) {
                        return "Thừa cân";
                } else {
                        return "Béo phì";
                }
        }
}
