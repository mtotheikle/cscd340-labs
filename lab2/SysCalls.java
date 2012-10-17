import java.io.*; // Need this to compile for the try-catch block
import java.util.*;

public class SysCalls
{
	public static void main(String[] args) throws FileNotFoundException
	{
		Scanner fin = null;
		File fileHandler = new File("test.txt");
		fin = new Scanner(fileHandler);
		
		while (fin.hasNext()) {
			System.out.println(fin.nextLine());
		}
	}
}