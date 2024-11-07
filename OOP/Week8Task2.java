import java.io.FileNotFoundException;
import java.io.IOException;

public class Week8Task2 {
    /**
     * Abc.
     * @throws NullPointerException abc
     */
    public void nullPointerEX() throws NullPointerException {
        throw new NullPointerException();
    }

    /**
     * Khong co gi.
     * @return abc
     */
    public String nullPointerExTest() {
        try {
            nullPointerEX();
        } catch (NullPointerException e) {
            return "Lỗi Null Pointer";
        }
        return "Không có lỗi";
    }

    /**
     * Abc.
     * @throws ArrayIndexOutOfBoundsException abc
     */
    public void arrayIndexOutOfBoundsEx() throws ArrayIndexOutOfBoundsException {
        throw new ArrayIndexOutOfBoundsException();
    }

    /**
     * Khong co gi abc.
     * @return 123
     */
    public String arrayIndexOutOfBoundsExTest() {
        try {
            arrayIndexOutOfBoundsEx();
        } catch (ArrayIndexOutOfBoundsException e) {
            return "Lỗi Array Index Out of Bounds";
        }
        return "Không có lỗi";
    }

    /**
     * Abc.
     * @throws ArithmeticException abc
     */
    public void arithmeticEX() throws ArithmeticException {
        throw new ArithmeticException();
    }

    /**
     * Khong co gi.
     * @return abc
     */
    public String arithmeticExTest() {
        try {
            arithmeticEX();
        } catch (ArithmeticException e) {
            return "Lỗi Arithmetic";
        }
        return "Không có lỗi";
    }

    /**
     * Khong co gi.
     * @throws FileNotFoundException abcd
     */
    public void fileNotFoundEX() throws FileNotFoundException {
        throw new FileNotFoundException();
    }

    /**
     * Khong co gi.
     * @return abc
     */
    public String fileNotFoundExTest() {
        try {
            fileNotFoundEX();
        } catch (FileNotFoundException e) {
            return "Lỗi File Not Found";
        }
        return "Không có lỗi";
    }

    /**
     * Khong co gi.
     * @throws IOException abc
     */
    public void ioEx() throws IOException {
        throw new IOException();
    }

    /**
     * KHong co gi.
     * @return abc
     */
    public String ioExTest() {
        try {
            ioEx();
        } catch (IOException e) {
            return "Lỗi IO";
        }
        return "Không có lỗi";
    }

}
