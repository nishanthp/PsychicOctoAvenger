
import java.util.ArrayList;



public class TicTacToeBoard {

	String [] states = new String [9];

	public void initialize() {
		for (int i=0;i<9;i++)
			{
				states[i]=" ";
				
			}
			
			
		}
	
	public String getSquare (int n)
	{
		return states[n-1];
		
	}
	
	public void setSquare(int n, String player)
	{
			
		states[n]=player;
		
	}
	
	public TicTacToeBoard move(String player, int n)
	{
		
		if (n > 0 && n < 10 && states[n-1] == null)
		{ 
			TicTacToeBoard board = new TicTacToeBoard();
			for(int i=0;i<9;i++)
			{
				board.setSquare(i,states[i]);
				
			}
			
			board.setSquare(n-1, player);
			return board;
		}
		else
		{
			
			return null;
		}
		
	}
	
	public void makeBoard(String player, int n)
	{
		
		if (n > 0 && n < 10 && states[n-1] == null)
		{ 
			
			for(int i=0;i<9;i++)
			{
				setSquare(i,states[i]);
				
			}
			
			setSquare(n-1, player);
	
	}
		
	}
	
	public ArrayList<String[]> getLines()
	{
		ArrayList<String []> lines = new ArrayList<String []>();
		String [] diagnol1 = new String [3];
		String [] diagnol2 = new String [3];
		for(int i=0;i<3;i++)
		{
			String [] row = new String [3];
			row[0] = states[i*3];
			row[1] = states[i*3+1];
			row[2] = states[i*3+2];
			lines.add(row);
		}
		
		for(int i=0;i<3;i++)
		{
			String [] column = new String [3];
			column[0] = states[i];
			column[1] = states[i+3];
			column[2] = states[i+6];
			lines.add(column);
		}
		
		diagnol1[0]= states[0];
		diagnol1[1]= states[4];
		diagnol1[2]= states[8];
		lines.add(diagnol1);
		diagnol2[0]= states[2];
		diagnol2[1]= states[4];
		diagnol2[2]= states[6];
		lines.add(diagnol2);
	
//		for (String [] eline:lines)
//		{
//			for(int i=0;i<3;i++)
//			{
//				System.out.println(eline[i]);
//				
//			}
//			
//		}
		
		return lines;
	}
	
	public String checkWin()
	{
		for(String [] eline:getLines())
		{
			
			if (winnigLine(eline)!=null)
			{
				return winnigLine(eline);
				
			}
		}
		
		if (isFull())
		{
			return "draw";
			
		}
		return null;
		
	}

	public boolean isFull() {
		boolean isfull = true;
		
		for(int i=0;i<9;i++)
		{
			//System.out.println(states[i]);
			if (states[i]==null)
			{
				isfull=false;
				return isfull;
				
			}
		}
		return isfull;
	}

	public String winnigLine(String[] eline) 
	{
		if (eline[0]==eline[1] && eline[1]==eline[2])
		{
			return eline[0];
			
		}
		else
		{
	return null;
		}
	}
	
	
	   public String display(){
		    String board = "-------------\n";
		    for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++) {
			    board += "| " + states[i*3+j] + " ";
			}
			board += "|\n-------------\n";
		    }
		    return board;
		}
	   
	   
	public int evaluate()
	{
		if(checkWin()=="x")
		return 1;
		
	
		else if(checkWin()=="o")
			return -1;
		
		else if(checkWin()=="draw")
			return 0;
		else
			return 2;
		
		
	}
	
	
	public Boolean isEmpty(int n)
	{
		if(states[n-1]=="")
			return true;
		else
			return false;
	}
	
	
	
	
	
	

}
