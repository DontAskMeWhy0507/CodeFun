import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.ArrayList;
import java.util.List;

public class Week10 {
    public static void main(String[] args) {
        String s = "      public static <T> T[] randomArrayFrom(Iterable<T> elements, Range<Integer> size) {\r\n";

        Pattern p =   Pattern.compile(
            "^(?<!\\s{0,20}/\\*\\n)" // Negative lookbehind
            + "(?:\\s{2})+(?:(?:public|private|protected)\\s+)*"
            + "static\\s+(?:final\\s+)?[\\w<>,.?\\[\\]\\s]+\\s+(\\w+)"
            + "\\s*\\(([\\w<>,.?\\[\\]\\s]*)\\)\\s*\\{",
            Pattern.MULTILINE
    );
        Matcher m = p.matcher(s);

        while (m.find()) {
             System.out.println("Method Name: " + m.group(1));
            String parameters = m.group(2);
            if (parameters != null && !parameters.trim().isEmpty()) {
                String[] paramsArray = parameters.split(",");
                List<String> paramTypes = new ArrayList<>();
                for (String param : paramsArray) {
                     String trimmedParam = param.trim();
                    String[] parts = trimmedParam.split("\\s+");
                    if(parts.length > 0)
                    {
                        paramTypes.add(parts[0]);
                    }

                }
              System.out.println("Parameter Types: " + paramTypes);
             }
              else {
                      System.out.println("Parameter Types: []");
                }
        }
    }
}