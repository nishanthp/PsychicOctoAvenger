import java.util.ArrayList;


public abstract class Game {
	public int[] range = {-100,100};

	abstract ArrayList<Game> successors();
	abstract boolean cutoff();
	abstract float evaluation();
	abstract String display();
	abstract void makeMove(String p, int n);
	abstract String getWinner();
	abstract boolean maxTurn();
	

	public float minMax()
	{
		float alpha = range[0];
		float beta = range[1];
		
		if (this.maxTurn())
		{
			
			 return maxValue(this,alpha,beta);
			
		}
		else
		{
		
			return  minValue(this,alpha,beta);
		}
	}
	
public float minValue(Game game, float alpha, float beta) {
		if (game.cutoff())
		{
			return game.evaluation();
			
		}
		float value = range[0];
		for (Game next:game.successors())
		{
		
		float val = maxValue(next, alpha, beta);
		if(val>value)
		{
			value = val;
			
		}
		if (value>alpha)
		{
			
			alpha = value;
		}
		if (value>=beta)
		{
			
			return value;
		}
		
		
	}
		return value;
	}
	public float maxValue(Game game, float alpha, float beta) {
		if (game.cutoff())
		{
			 return game.evaluation();
			
		}
		
		float value = range[1];
		for(Game next:game.successors())
		{
		float val = minValue(next, alpha, beta);
		
		if(val<=value)
		{
			value = val;
			
		}
		if (value<=alpha)
		{
			
			return value;
		}
		if (value<beta)
		{
			beta = value;
			
		}
		
	}
		return value;
	}
	
}
