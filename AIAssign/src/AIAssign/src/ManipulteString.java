package AIAssign.src;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.Set;
import java.util.Stack;

import javax.sql.rowset.serial.SerialBlob;


public class ManipulteString {

	public String [] arryLines;
	public String [] temp1;
	static int moves;
	static Block I_A,I_B,I_C,I_D,I_E,I_N,I_G,I_H,I_I,I_S;
	static Block TableA,TableB,TableC,TableD,TableE,TableN,TableG,TableS,TableI;
	static Block F_A,F_B,F_C,F_D,F_E,F_N,F_G,F_H,F_I,F_S;
	
	ArrayList<String> temporary = new ArrayList<String>();
	ArrayList<String> objects = new ArrayList<String>();
	ArrayList<Block> exsisted_objects = new ArrayList<Block>();
	ArrayList<Block> exsisted_finalobjects = new ArrayList<Block>();
	ArrayList<Block> exsisted_tableobjects = new ArrayList<Block>();
	ArrayList<String> actual_objects = new ArrayList<String>();
	ArrayList<Block> table_objects = new ArrayList<Block>();
	
	
	ArrayList<Block> low_priority = new ArrayList<Block>();
	ArrayList<Block> dlow_priority = new ArrayList<Block>();
	ArrayList<Block> high_priority = new ArrayList<Block>();
	ArrayList<Block> superHigh_priority = new ArrayList<Block>();
	ArrayList<Block> superRemove = new ArrayList<Block>();
	ArrayList<String> intial_state = new ArrayList<String>();
	ArrayList<String> final_state = new ArrayList<String>();
	
	static ArrayList<String> block_print = new ArrayList<String>();
	 ArrayList<String> block_printSU;
	 ArrayList<String> block_printSD;
	 ArrayList<String> block_printPU;
	 ArrayList<String> block_printPD;
	
	public ManipulteString(String[] lines) {
		this.arryLines = lines;
	}
	
	public void manipulate()
	{
		// To get the objects
	for(int i=0;i<arryLines.length;i++)
	{
		if(arryLines[i].equals("INITIAL STATE:"))	
			break;
		if (arryLines[i].equals("BLOCKS:"))
		{
			continue;
		}
		
		objects.add(arryLines[i]);
		
	 
	}
	
	
	
	
	//To get Initial States
	for(int i=0;i<arryLines.length;i++)
	{
		if (arryLines[i].equals("BLOCKS:"))
			continue; 
		if(objects.contains(arryLines[i]))
		{
			continue;
		}
		if (arryLines[i].equals("INITIAL STATE:")) 
				{
					continue;
				}
		
		if (arryLines[i].equals("GOAL STATE:"))
		{
			break;
			
		}
		//System.out.println(arryLines[i]);
		intial_state.add(arryLines[i]);
	}
	
	for(int i=0;i<intial_state.size();i++)
	{
		block_print.add(intial_state.get(i)); 
		
	}
	
	
	
	int flag=0;
	//To get Goal States
	
	for(int i=0;i<arryLines.length;i++)
	{
		if(arryLines[i].equals("GOAL STATE:"))
		{
			flag=i;
			
		}
	}
	
	for(int i=0;i<arryLines.length;i++)
	{
		
		if(i>flag)
		{
			final_state.add(arryLines[i]);
			
			
		}
		
	}

	populate();
	}
	

	public void populate()
	{
		String str=null;
		for(int i=0;i<objects.size();i++)
		{
		  str = objects.get(0);
		
		}

		
		
			temp1  = str.split(","+" ");

		for(int i=0;i<temp1.length;i++)
			{
				actual_objects.add(temp1[i]);			//obtaining the number of blocks
				
			}
			
		
			for(int i=0;i<temp1.length;i++)
			{
				//System.out.println(temp1[i]);
				
				
				String InitialBlock = "I_"+temp1[i];
				
				String FinalBlock = "F_"+temp1[i];
				
				String TableName = "Table"+temp1[i];
				
				 exsisted_objects.add(new Block(InitialBlock,temp1[i],TableName));	 
				 exsisted_finalobjects.add(new Block(FinalBlock,temp1[i],TableName));
				 exsisted_tableobjects.add(new Block(TableName,temp1[i]));
			}	
		
		//Populate the classes
		String ontemporary="";
		for(String temp:intial_state)			//traversing the initial state for ON_TABLE
		{
			
			for(int j=0;j<temp1.length;j++)
			{
			if(temp.equals("ON_TABLE("+temp1[j]+")"))
			{
			ontemporary = temp1[j];
			
			for(int i=0;i<exsisted_tableobjects.size();i++)
			{
			
				
				if(exsisted_tableobjects.get(i).Name.equals("Table"+temporary))
				{
					
					exsisted_tableobjects.get(i).above_ptr = ontemporary;
					
				}
			}
			for(int i=0;i<exsisted_objects.size();i++)
			{
				
				if(exsisted_objects.get(i).Name.equals("I_"+ontemporary))
				{
					exsisted_objects.get(i).below_ptr = "Table"+ontemporary;
					
				}
			}
			}
			}
		}
		
		
		String HDtemporary="";
		for(String temp:intial_state)			//traversing the initial state for HOLDING
			
		{
			for(int j=0;j<temp1.length;j++)
			{
			if(temp.equals("HOLDING("+temp1[j]+")"))
			{	
				HDtemporary= temp1[j];
			for(int i=0;i<temp1.length;i++)
			{
			
			
				if(exsisted_objects.get(i).Name.equals("I_"+HDtemporary))
				{
					exsisted_objects.get(i).below_ptr = "HAND";
					exsisted_objects.get(i).above_ptr = "HAND";
				}
				
			}
			}
			}
			
		}
			
		for(String temp:intial_state)			//traversing the initial state for the ON(x,y)
		{
			for(int i=0;i<temp1.length;i++)
			{
				for(int j=0;j<temp1.length;j++)
				{
					if(temp.equals("ON("+temp1[i]+","+temp1[j]+")"))
					{
						
						
						for(int k=0;k<temp1.length;k++)
						{	
						if(exsisted_objects.get(k).Name.equals("I_"+temp1[j]))
						{
							exsisted_objects.get(k).above_ptr = temp1[i];
							
						}
						if(exsisted_objects.get(k).Name.equals("I_"+temp1[i]))
						{
							exsisted_objects.get(k).below_ptr = temp1[j];
						}
						
					    }
						
						
						
					}
					
				}
			
			}
		}
		/*for(int i=0 ;i<exsisted_objects.size();i++)
		{
			System.out.println(exsisted_objects.get(i).above_ptr);
			System.out.println(exsisted_objects.get(i).Name);
			System.out.println(exsisted_objects.get(i).below_ptr);
		}*/
			
///////////////////////////////////////////////////////////////////////////////////////////////////////
		
		String ftemporary = "";
		for(String temp:final_state)			//traversing the initial state for ON_TABLE
		{
			
			for(int j=0;j<temp1.length;j++)
			{
				if(temp.equals("ON_TABLE("+temp1[j]+")"))
				{
					 ftemporary = temp1[j];
			
			for(int i=0;i<exsisted_tableobjects.size();i++)
					 {
				if(exsisted_tableobjects.get(i).Name.equals("Table"+ftemporary))
				{
					exsisted_tableobjects.get(i).above_ptr = ftemporary;
					
				}
				}
			for(int i=0;i<exsisted_finalobjects.size();i++)
			 {
			
				if(exsisted_finalobjects.get(i).Name.equals("F_"+ftemporary))
				{
					exsisted_finalobjects.get(i).below_ptr = "Table"+ftemporary;
					
				}
			 }
				
			}
			}
			}
		
		
		
		
	for(String temp:final_state)			//traversing the initial state for HOLDING
			
		{
			for(int j=0;j<temp1.length;j++)
			{
				if(temp.equals("HOLDING("+temp1[j]+")"))
			for(int i=0;i<temp1.length;i++)
			{

				if(exsisted_finalobjects.get(i).Name.equals("F_"+temp1[j]))
				{
					exsisted_finalobjects.get(i).below_ptr = "HAND";
					//Block.above_ptr = "HAND";
				}
				
			
			}
			
		}
		}
	for(String temp:final_state)			//traversing the initial state for the ON(x,y)
	{
		for(int i=0;i<temp1.length;i++)
		{
			for(int j=0;j<temp1.length;j++)
			{
				if(temp.equals("ON("+temp1[i]+","+temp1[j]+")"))
				{
				
					for(int k=0;k<temp1.length;k++)
					{
					if(exsisted_finalobjects.get(k).Name.equals("F_"+temp1[j]))
					{
						exsisted_finalobjects.get(k).above_ptr = temp1[i];
						
					}
					if(exsisted_finalobjects.get(k).Name.equals("F_"+temp1[i]))
					{
						exsisted_finalobjects.get(k).below_ptr = temp1[j];
						//System.out.println(temp1[j]);
					}
					}
				
				
					
				}
				
			}
		
		}
	}
	
	traverseGraph();
	}

	/**
	 * Check which one of the position_different are free to move for first pass
	 */
	ArrayList<Block> free_move = new ArrayList<Block>();

	public void traverseGraph() {

		for(int i=0;i<exsisted_objects.size();i++)
		{
			
			if(exsisted_objects.get(i).above_ptr==null && exsisted_objects.get(i).below_ptr!="HAND")
			{
				
				free_move.add(exsisted_objects.get(i));				// access which are free to move
				//System.out.println(exsisted_objects.get(i).Name);
			}
			if(exsisted_objects.get(i).below_ptr=="HAND")				
			{
				String req = "PUTDOWN("+exsisted_objects.get(i).printName+"):";
				checkforPrintingPD(exsisted_objects.get(i).printName, block_print);
				System.out.println(req+block_print);
				moves++;
				exsisted_objects.get(i).above_ptr=null;
				
				exsisted_objects.get(i).below_ptr="Table"+exsisted_objects.get(i).printName;
				free_move.add(exsisted_objects.get(i));
				
			}
			
		}
		for(int i=0;i<exsisted_objects.size();i++)			//for those objects which are not being mentioned in the goal state (I_A)
		{
			for(int j=0;j<temp1.length;j++)
			{
			if(exsisted_objects.get(j).printName.equals(temp1[j]))
			{
				if(exsisted_objects.get(j).below_ptr == null)
				{
					exsisted_objects.get(j).below_ptr = "Table"+temp1[j];
					
				}
			}
			}
		}
		
		for(int i=0;i<exsisted_finalobjects.size();i++)			//for those objects which are not being mentioned in the goal state (F_A)
		{
			for(int j=0;j<temp1.length;j++)
			{
			if(exsisted_finalobjects.get(j).printName.equals(temp1[j]))
			{
				if(exsisted_finalobjects.get(j).below_ptr == null)
				{
					exsisted_finalobjects.get(j).below_ptr = "Table"+temp1[j];
					
				}
			}
			}
		}
		
		freeMove();
	}
	

		public void freeMove()
		{
		for(int i=0;i<free_move.size();i++)
		{
					
					 String tableName = free_move.get(i).tableName;
					 if(!(free_move.get(i).below_ptr.equals(tableName)))
					 {
						 //System.out.println(free_move.get(i).above_ptr);
						 updatePtrTable(free_move.get(i));
						 
					 }

		}
			 
		
		check();
		}
	
	private void updatePtrTable(Block free_move2) {
		String unstackPrint=" ";
  		
  			
  				String tableName = free_move2.tableName;
  				if(!(free_move2.below_ptr.equals(tableName)))
  				{
  					
  					
  					for(int j=0;j<temp1.length;j++)			//check whether it is on any other block
  					{
  						
  					if(free_move2.below_ptr.equals(temp1[j]))
  					{
  						//System.out.println(free_move2.below_ptr);
  						unstackPrint=temp1[j];
  						
  						
  						for(int k=0;k<temp1.length;k++)
  						{
  						if(exsisted_objects.get(k).printName.equals(unstackPrint))	//find the block in the exsisted_objects
  						{
  							
  							exsisted_objects.get(k).above_ptr = null;
  							//System.out.println(exsisted_objects.get(k).above_ptr);
  							free_move.add(exsisted_objects.get(k));
  						}
  						}
  					}
  					
  					
  					
  					
  					}
  					checkforPrintingSD(free_move2.printName,unstackPrint, block_print);
  					System.out.println("UNSTACK("+free_move2.printName+","+unstackPrint+"):"+block_print); //AFTER THIS CHECK CONDITION
  					moves++;
  					
  					free_move2.below_ptr = "Table"+free_move2.printName;
  					//System.out.println(free_move2.below_ptr);
  					checkforPrintingPD(free_move2.printName, block_print);
  					System.out.println("PUTDOWN("+free_move2.printName+"):"+block_print);
  					moves++;
  					
  					
  				}
  			}
	
	
	
	public void check()
	{
		
		if(free_move.size()==actual_objects.size())
		{
			
    			actualTraverse();
    			
    			if(!(low_priority.isEmpty()&&high_priority.isEmpty()&&superHigh_priority.isEmpty()))
    			{
    				arrayTraverse();
    				
    			}
    			else
    			{
    				System.out.println("The total number of moves are"+moves);
    				System.out.println("The initial and Goal State are same!");
    			}
			
		}
		else
		{  
			freeMove();
			
		}
		
	}

	String pointerBlock = "";
	String lowPriorityptr = "";
	private void actualTraverse() {
		
	
		table_objects.addAll(exsisted_objects); // this is to get the latest copy of all the objects
	
		/**
		 * for loop to fill the low priority and the high priority 
		 */
	
		for(int i=0;i<table_objects.size();i++)
		{
			pointerBlock = table_objects.get(i).printName;
			
			for(int j=0;j<exsisted_finalobjects.size();j++)
			{
				
				if(exsisted_finalobjects.get(j).printName.equals(pointerBlock))
				{
					
					
					if(table_objects.get(i).above_ptr!=exsisted_finalobjects.get(j).above_ptr && !(table_objects.get(i).below_ptr.equals(exsisted_finalobjects.get(j).below_ptr)))
					{
						
						high_priority.add(table_objects.get(i));
					}
					else
					{
						
						
						low_priority.add(table_objects.get(i));
					}
				}
				
			}

		}
		
		
		/**
		 * Remove the objects which are in final state
		 */
		Iterator<Block> iter = low_priority.iterator();
		Boolean flag = false;
		while(iter.hasNext())
		{ 
			Block tempBlock = iter.next();

			for(int i=0;i<exsisted_finalobjects.size();i++)
			{
				
				
				if(exsisted_finalobjects.get(i).printName.equals(tempBlock.printName))
				{
					//System.out.println(tempBlock.below_ptr);
					
					if(tempBlock.below_ptr.equals(exsisted_finalobjects.get(i).below_ptr))
					{
						for(int j=0;j<exsisted_objects.size();j++)
						{
							if(exsisted_objects.get(i).printName.equals(tempBlock.printName))
							{
								exsisted_objects.get(i).finalPosition = true;
							}
							
						}
						
						iter.remove();
						
					}
					
				}
				
			}
			
			
		}
		
		/**
		 * This loop will be used to fill the super high priority blocks
		 */
		
		 for(int i=0;i<high_priority.size();i++)
		 {
			for(int j=0;j<temp1.length;j++)
			{
				if(high_priority.get(i).printName.equals(temp1[j]))
				{
					for(int k=0;k<exsisted_finalobjects.size();k++)
					{
						
						if(exsisted_finalobjects.get(k).printName.equals(high_priority.get(i).printName))
							
						{
							//System.out.println(exsisted_finalobjects.get(k).printName);
							
							for(int m=0;m<high_priority.size();m++)
							{
								if(exsisted_finalobjects.get(k).above_ptr.equals(high_priority.get(m).printName))
								{
									
									superHigh_priority.add(high_priority.get(i));
									
								}
							}
							
						}
					}
					
				}
			}
			 
			 }
		 Iterator<Block> itr= high_priority.iterator();
		 while(itr.hasNext())
		 {
			 if(superHigh_priority.contains(itr.next()))
			 {
				 itr.remove();
			 }
			 
		 }
		 
		 /**
		  * Dependency among the super high_priority
		  * 
		  */
		/*for(int i=0;i<exsisted_finalobjects.size();i++)
		{
			System.out.println(exsisted_finalobjects.get(i).above_ptr);
			System.out.println(exsisted_finalobjects.get(i).Name);
			//System.out.println(exsisted_finalobjects.get(i).below_ptr);
			
			
		}*/
		 
here:		 for(int i=0;i<superHigh_priority.size();i++)
		 {
			 for(int j=0;j<temp1.length;j++)
			 {
				 if(superHigh_priority.get(i).printName.equals(temp1[j]))
				 {
					 for(int k=0;k<exsisted_finalobjects.size();k++)
					 {
						 if(superHigh_priority.get(i).printName.equals(exsisted_finalobjects.get(k).printName))
						 {
							 for(int m=0;m<exsisted_objects.size();m++)
							 {
								 if(exsisted_finalobjects.get(k).below_ptr.equals(exsisted_objects.get(m).printName))
								 {
									
									 if(exsisted_objects.get(m).finalPosition.equals(true))
									 {
										 //System.out.println(superHigh_priority.get(i).Name);
										 superRemove.add(superHigh_priority.get(i));
										 firstMove(superHigh_priority.get(i));
										 
									 }
									 
								 }
							 }
							 
						 }
						 
					 }
					 
				 }
				 
			 }
			 if(!(superHigh_priority.size()==superRemove.size()-1))
			 {
				 continue here;
			 }
			 
		 }
		 // to remove redundancy in super_High priority  
		 Iterator<Block> superPriority = superHigh_priority.iterator();
		 while(superPriority.hasNext())
		 {
			 if(superRemove.contains(superPriority.next()))
				 
			 {
				 superPriority.remove();
			 }
		 }
		 	/*for(int i=0;i<superHigh_priority.size();i++)
		 	{
		 		System.out.println(superHigh_priority.get(i).printName);
		 		
		 	}*/
		 
		 }
		 
	
	

		private void firstMove(Block first_move) {

					String temp = first_move.printName;
					 checkforPrintingPU(temp,block_print);
					 System.out.println("PICKUP("+temp+"):"+block_print);
					 moves++;
					 for(int j=0;j<exsisted_finalobjects.size();j++)
					 {
						 if(exsisted_finalobjects.get(j).printName.equals(temp))
						 {
							 
							 for(int k=0;k<exsisted_objects.size();k++)
							 {
								 if(exsisted_objects.get(k).printName.equals(exsisted_finalobjects.get(j).printName))
								 {
									 exsisted_objects.get(k).above_ptr = exsisted_finalobjects.get(j).above_ptr;
									 exsisted_objects.get(k).below_ptr = exsisted_finalobjects.get(j).below_ptr;
									 exsisted_objects.get(k).finalPosition = true;
									 checkforPrintingSU(first_move.printName, exsisted_finalobjects.get(j).below_ptr, block_print);
									 System.out.println("STACK("+first_move.printName+","+exsisted_objects.get(k).below_ptr+"):"+block_print);
									 moves++;
								 }
								 
							 }
							 
						 }
					 }
					
				}
			
		
	

		/**
		 * Now you are traversing the graph using the 3 arraylist
		 */
		 public void arrayTraverse()
		 {
		 for(int i=0;i<superHigh_priority.size();i++)
		 {
			 for(int j=0;j<temp1.length;j++)
			 {
				 if(superHigh_priority.get(i).printName.equals(temp1[j]))
				 {
					 String temp = temp1[j];
					 checkforPrintingPU(temp,block_print);
					 System.out.println("PICKUP("+temp1[j]+"):"+block_print);
					 moves++;
					 for(int k=0;k<exsisted_finalobjects.size();k++)
					 {
						 if(exsisted_finalobjects.get(k).printName.equals(temp1[j]))
						 {
							 if(exsisted_finalobjects.get(k).below_ptr!= "HAND")
							 {
								 superHigh_priority.get(i).above_ptr = exsisted_finalobjects.get(k).above_ptr;
								 superHigh_priority.get(i).below_ptr = exsisted_finalobjects.get(k).below_ptr;
								 checkforPrintingSU(temp1[j],exsisted_finalobjects.get(k).below_ptr , block_print);
								 System.out.println("STACK("+temp1[j]+","+superHigh_priority.get(i).below_ptr +"):"+block_print);
								 moves++;
							 }
						 }
						 
					 }
				 }
			 }
			 
			 
			 }
		 
		 
		 for(int i=0;i<high_priority.size();i++)
		 {
			 for(int j=0;j<temp1.length;j++)
			 {
				 if(high_priority.get(i).printName.equals(temp1[j]))
				 { 
					 String temp = temp1[j];
					 checkforPrintingPU(temp,block_print);
					 System.out.println("PICKUP("+temp1[j]+"):"+block_print);
					 moves++;
					 for(int k=0;k<exsisted_finalobjects.size();k++)
					 {
						 if(exsisted_finalobjects.get(k).printName.equals(temp1[j]))
						 {
							 if(exsisted_finalobjects.get(k).below_ptr!="HAND")
							 {
								 high_priority.get(i).above_ptr = exsisted_finalobjects.get(k).above_ptr;
								 high_priority.get(i).below_ptr = exsisted_finalobjects.get(k).below_ptr;
								 checkforPrintingSU(temp1[j], exsisted_finalobjects.get(k).below_ptr, block_print);
								 System.out.println("STACK("+temp1[j]+","+high_priority.get(i).below_ptr+"):"+block_print);
								 moves++;
							 }
							 
						 }
					 }
				 }
			 }
			 
			 
		 }
		 
	Boolean flag= false;
	Boolean pickUp = false;
		for(int i=0;i<low_priority.size();i++)
		 {
			 
	innerLoop:		 
		for(int j=0;j<temp1.length;j++)
			 {
				 if(low_priority.get(i).printName.equals(temp1[j]))
				 {
					 
					 String temp = low_priority.get(i).printName;
					
					
					 
					 for(int k=0;k<exsisted_finalobjects.size();k++)
					 {
						 
						 if(exsisted_finalobjects.get(k).printName.equals(temp))
						 {
							 if(exsisted_finalobjects.get(k).below_ptr.equals("HAND"))
							 {
								 Integer low = low_priority.size();
								 Integer dlow = dlow_priority.size()-1;
								 if(low.equals(dlow))
								 {
									 flag= true;
									 checkforPrintingPU(temp,block_print);
									 System.out.println("PICKUP("+temp+"):"+block_print);
									 moves++;
									 
								 }
								 else
								 {
									 pickUp = true;
									 break innerLoop;
								 }
							 }
							 
							 if(!(flag))
							 { 
							 checkforPrintingPU(temp,block_print);
							 System.out.println("PICKUP("+temp+"):"+block_print);
							 moves++;
							 
							 if(exsisted_finalobjects.get(k).below_ptr!="HAND")
							 {
								 dlow_priority.add(low_priority.get(i));
								 low_priority.get(i).above_ptr = exsisted_finalobjects.get(k).above_ptr;
								 low_priority.get(i).below_ptr = exsisted_finalobjects.get(k).below_ptr;
								 
								 checkforPrintingSU(temp1[j], exsisted_finalobjects.get(k).below_ptr, block_print);
								 System.out.println("STACK("+temp1[j]+","+low_priority.get(i).below_ptr+"):"+block_print);
								 moves++;
							 }
							 }
							 
						 }
						 
					 }
				 
					 
				 }
				 
			 }
			 
			 
			 }	//low Priority loop ends here
		
		
		
		/**
		 * Dependency among the low_priority
		 * 		 */
		
		if(pickUp)
		{
			Iterator<Block> iter= low_priority.iterator();
			while(iter.hasNext())
			{
				if(dlow_priority.contains(iter.next()))
				{
					iter.remove();
					
				}
				
			}
			
			
			for(int i=0;i<low_priority.size();i++)
			{
				
				for(int j=0;j<temp1.length;j++)
				{
					if(low_priority.get(i).printName.equals(temp1[j]))
					{
						String temp = low_priority.get(i).printName;
						//System.out.println(temp);
						for(int k=0;k<temp1.length;k++)
						{
							if(exsisted_finalobjects.get(k).printName.equals(low_priority.get(i).printName))
							{
								
								if(exsisted_finalobjects.get(k).below_ptr.equals("HAND"))
								{
									 checkforPrintingPU(temp,block_print);
									 System.out.println("PICKUP("+temp+"):"+block_print);
									 moves++;
									
								}
								
							}
						}
					}
					
				}
				
			}
		}
		
		
		 		System.out.println("The total number of moves are"+moves);
			 }  // arrayTraverse method ends here 
		 	
		 
		
	
		 	

		private void checkforPrintingPU(String temp,
				ArrayList<String> block_print2) {
			String unrequired1 = "ON_TABLE("+temp+")";
			String unrequired2 = "CLEAR("+temp+")";
			block_printPU = new ArrayList<String>();
			for(int i=0;i<block_print.size();i++)
			{
			if(block_print.contains(unrequired1))
			{
				block_printPU.add(unrequired1);
				//block_print.remove(unrequired1);
				
			}
			if(block_print.contains(unrequired2))
			{
				block_printPU.add(unrequired2);
				//block_print.remove(unrequired2);
			}
			if(block_print.contains("HE"))
			{
				block_printPU.add("HE");
				//block_print.remove("HE");
			}
			}
			
			Iterator<String> iterPU = block_print.iterator();
			while(iterPU.hasNext())
			{
				if(block_printPU.contains(iterPU.next()))
				{
					iterPU.remove();
				}
			}
			block_print.add("HOLDING("+temp+")");
			Set<String>hashing3 = new LinkedHashSet<String>();
			hashing3.addAll(block_print);
			block_print.clear();
			block_print.addAll(hashing3);
			
		}
		private void checkforPrintingPD(String temp,
				ArrayList<String> block_print2) {
			
			String required1 = "ON_TABLE("+temp+")";
			String required2 = "CLEAR("+temp+")";
			block_printPD = new ArrayList<String>();
				block_print.add(required1);			
				block_print.add (required2);
				
				for(int i=0;i<block_print.size();i++)
				{
					String temp1= block_print.get(i);
					if(temp1.startsWith("HOLDING"))
					{
						block_printPD.add(temp1);
						//block_print.remove(i);
					}
					
					
				}
				Iterator<String> iterPD = block_print.iterator();
				while(iterPD.hasNext())
				{
					if(block_printPD.contains(iterPD.next()))
					{
						iterPD.remove();
					}
					
				}
				block_print.add("HE");
				Set<String> hashing2 = new LinkedHashSet<String>();
				hashing2.addAll(block_print);
				block_print.clear();
				block_print.addAll(hashing2);
				
			
		}
		private void checkforPrintingSU(String temp1, String temp2,
				ArrayList<String> block_print2) {
			String required1 = "ON("+temp1+","+temp2+")";
			String required2 = "CLEAR("+temp1+")";
			String unrequired= "CLEAR("+temp2+")";
			block_print.add(required1);
			block_print.add(required2);
			block_printSU = new ArrayList<String>();
			for(int i=0;i<block_print.size();i++)
			{
				String temp = block_print.get(i);
				if(temp.startsWith("HOLDING("))
				{
					block_printSU.add(temp);
					
				}
				if(temp.equals(unrequired))
				{
					block_printSU.add(temp);
					//block_print.remove(unrequired);
					
				}
				
			}
			Iterator<String> iterSU = block_print.iterator();
			while(iterSU.hasNext())
			{
				if(block_printSU.contains(iterSU.next()))
				{
					iterSU.remove();
				}
				
				
			}
			block_print.add("HE");
			Set<String> hashing1 = new LinkedHashSet<String>();
			hashing1.addAll(block_print);
			block_print.clear();
			block_print.addAll(hashing1);
			
		}
		private void checkforPrintingSD(String itName,String temp,
				ArrayList<String> block_print2) {
			
			String required1 = "CLEAR("+temp+")";
			String unrequired1 = "ON("+itName+","+temp+")";
			String unrequired2 = "CLEAR("+itName+")";
			block_printSD = new ArrayList<String>();
				for(int i=0;i<block_print.size();i++)
				{
				if(block_print.contains("HE"))
				{
					block_printSD.add("HE");
					//block_print.remove("HE");
				}
				if(block_print.contains(unrequired1))
				{
					block_printSD.add(unrequired1);
					//block_print.remove(unrequired1);
				}
				if(block_print.contains(unrequired2))
				{
					block_printSD.add(unrequired2);
					//block_print.remove(unrequired2);
				}
				}
				Iterator<String> iterSD = block_print.iterator();
				while(iterSD.hasNext())
				{
					if(block_printSD.contains(iterSD.next()))
					{
						iterSD.remove();
						
					}
					
					
				}
				
				block_print.add(required1);
				block_print.add("HOLDING("+itName+")");
				
			Set <String> hashing = new LinkedHashSet<String>();
			hashing.addAll(block_print);
			block_print.clear();
			block_print.addAll(hashing);
		}
		
	
	
}	// manipulateString class ends here
