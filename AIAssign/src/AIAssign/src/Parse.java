package AIAssign.src;
import java.io.IOException;
import java.util.Scanner;


public class Parse {

	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		String file_Name=in.nextLine();
		ReadFile rf = new ReadFile(file_Name);
		
		try {
			String [] lines = rf.OpenFile();
			
			for(int i=0;i<lines.length;i++)
			{
				System.out.println(lines[i]);
				
			}
			ManipulteString ms = new ManipulteString(lines);
			ms.manipulate();
			
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}

	}
	
	

}
