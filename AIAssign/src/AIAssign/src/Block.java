package AIAssign.src;

public class Block {
	 String Name="";
	 String printName="";
	 String tableName="";
	 String above_ptr=null;
	 String below_ptr=null;
	 Boolean finalPosition = false;
		Block()
		{
		
		
		}
		Block(String Name)
		{
		
		this.Name = Name;
		}
		Block(String Name, String printName)
		{
			this.Name = Name;
			this.printName = printName;
				
			
		}
		Block(String Name, String printName, String tableName)
		{
			this.Name = Name;
			this.printName = printName;
			this.tableName = tableName;
		}
	
}
