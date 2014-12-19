package AIAssign.src;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class ReadFile {

	private String path;
	
	public ReadFile(String file_path){
		this.path = file_path;
		
	}
	
	public  String[] OpenFile() throws IOException
	{
		int numberofLines=readLines();
		//System.out.println(numberofLines);
		
		FileReader fr = new FileReader(path); 
		BufferedReader textReader = new BufferedReader(fr);
		
		String [] text = new String[numberofLines];
		
		for(int i=0;i<text.length;i++)
		{
			
			text[i]= textReader.readLine();
			
		}
		
		
		textReader.close();
		return text;
	}
	public int readLines() throws IOException
	{
		int numberofLines=0;
		
		FileReader fR = new FileReader(path); 
		BufferedReader tR = new BufferedReader(fR);
		
		while(tR.readLine()!=null)
		{
			
			numberofLines++;
		}
		
		tR.close();
		return numberofLines;
	}

}
