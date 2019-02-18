import cs.min2phase.Search;
import java.io.*;

public class demo2 {
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String scrambledCube = in.readLine();
        String result = new Search().solution(scrambledCube, 25, 100000000, 0, 0);
        System.out.println(result);
    }
}
