import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Scanner;


public class GameLauncher {

	static int nodesVisited=0;
	public static void main(String[] args) {
		TicTacToeBoard b= new TicTacToeBoard();
		
		Scanner  sc = new Scanner(System.in);
		System.out.println("Enter the number of entries");
		int input = sc.nextInt();
		for(int i=0;i<input;i++)
		{
			b.makeBoard(getPlayer(), getMove());
			System.out.println(b.display());
		}
		Game game = new TicTacToe(b);
		
		while(!game.cutoff())
		{
			
			System.out.println(game.display());
			//game.makeMove("x",getMove());
			float v = game.range[1];
			Game successor=null;
			for(Game next : game.successors())
			{
				nodesVisited++;
				 float value = next.minMax();
				 if(value<v)
				 {
					 v = value;
					 successor = next;
				 }
				 
			}
			
			//Number of nodes visited.
			 game = successor;
		}
		
		System.out.println(game.display());
		System.out.println("The number of nodes visited in the tree are"+" "+nodesVisited);
		
		if(game.getWinner()=="draw")
		{
			System.out.println("The game is drawn!");
			
		}
		else
		{
			System.out.println("The winner is"+" "+game.getWinner());
			
		}
		
		
	}

	public static int getMove() {
		int move = 0;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			System.out.println("Enter the Position");
			move = Integer.parseInt(br.readLine());
		} catch (NumberFormatException | IOException e) {
			System.out.println("Error occured while trying to accees the input move");
			System.exit(1);
		}
		if (1>move||move>10)
		{
			System.out.println("The value for move should be between 1 and 9");
			return getMove();
		}
		return move;
	}
	
	public static String getPlayer() {
		String player = null;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			System.out.println("Enter the player");
			player = br.readLine();
		} catch (IOException e) {
			System.out.println("Error occured while trying to accees the input move");
			System.exit(1);
		}
		if(player.equals("x")||player.equals("o"))
		{
		
		return player;
		}
		return null;
	}

}
