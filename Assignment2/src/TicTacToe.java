
import java.util.ArrayList;




public class TicTacToe extends Game {

	TicTacToeBoard board;
	String player;
	
	public TicTacToe() {
		player="x";
		board = new TicTacToeBoard();
	}
	
	public TicTacToe(TicTacToeBoard b)
	{	player = "o";
		this.board = b;
		
	}
	
	public TicTacToe(TicTacToeBoard cboard,String player)
	{
		this.board = cboard;
		this.player = player;
		
	}
	
	
	
	@Override
	float evaluation() {
		
		return board.evaluate();
		
	}

	@Override
	String display() {
		
		return board.display();
		
	}


	@Override
	boolean maxTurn() {
		if (player == "x")
		{
		return true;
		}
		else
		{
			return false;
		}
	}

	@Override
	 ArrayList<Game> successors() {
		ArrayList<Game> successors = new ArrayList<Game>();
		String newPlayer;
		if (player=="x")
		{
			
			newPlayer = "o";
			
		}
		else
			newPlayer = "x";
		for(int i=1;i<10;i++)
		 {
			  TicTacToeBoard b = board.move(player, i);
			  if (b != null)
			  {
			  successors.add(new TicTacToe(b,newPlayer));
			  }
			  
		 }
		return successors;
	}

	@Override
	String getWinner() {
		
		return board.checkWin(); 
		
	}

	@Override
	public boolean cutoff() {
		
		return (board.checkWin()!= null);
		
	}
	
	public void setBoard (TicTacToeBoard newboard)
	{
		this.board = newboard;
		
	}
	
	public TicTacToeBoard getBoard()
	{
		return board;
		
	}
	
	public boolean isValidMove(int n)
	{
		
		return board.isEmpty(n);
	}
	
	@Override
	public void makeMove(String s , int position)
	{
		TicTacToeBoard b = board.move(s, position);
		if (b != null)
		{
			setBoard(b);
			
		}
		if (s.equals("x"))
		{
			player="o";
			
		}
		else 
		{
			player="x";
			
		}
		
	}
	
	public int compMove()
	{
		int square = 0;
		float v = range[1];
		TicTacToe successor = null;
		for(Game next:this.successors())
		{
			 float val = next.minMax();
			 
			 if (val<v)
			 {
				 v = val;
				 successor = (TicTacToe)next;
			 }
			 
		}
		
		if (successor != null)
		{
			
			for (int i=1;i<10;i++)
			{
				if (board.getSquare(i)!= successor.getBoard().getSquare(i))
				{
					square = i;
					
				}
				
			}
			setBoard(successor.getBoard());
			if (player == "x")
			{
				player="o";
			}
				else
				{
				player = "x";
				}
				}
		
		return square;
	}

	

}
