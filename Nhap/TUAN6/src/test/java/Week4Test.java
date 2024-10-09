import org.junit.Assert;
import org.junit.Test;

public class Week4Test {
        @Test
        public void testMax2Int1(){
                int actualResult = Week4.max2Int(1, 2);
                int expectedResult = 2;
                Assert.assertEquals(actualResult, expectedResult);
        }

        @Test
        public void testMax2Int2(){}

        @Test
        public void testMax2Int3(){}

        @Test
        public void testMax2Int4(){}

        @Test
        public void testMax2Int5(){}

        @Test
        public void testMinArray1(){}

        @Test
        public void testMinArray2(){

        }

        @Test
        public void testMinArray3(){
                int [] array = {1, 3, 5, 7, 9};
                int actualResult = Week4.minArray(array);
                int expectedResult = 1;
                assert actualResult == expectedResult;
        }

        @Test
        public void testMinArray4(){}

        @Test
        public void testMinArray5(){}

        @Test
        public void testCalculateBMI1(){
                double weight = 70;
                double height = 1.75;
                double BMI = 25.0;

        }

        @Test
        public void testCalculateBMI2(){}

        @Test
        public void testCalculateBMI3(){}

        @Test
        public void testCalculateBMI4(){}

        @Test
        public void testCalculateBMI5(){}
}