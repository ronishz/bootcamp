// time complexity of TSP is O(n^(2)*2^(n))
import java.util.*;

public class TSP implements Runnable
{
    int size;
    int routes[][];		//edges
    String cities[];	//vertices
    
    Thread runners[];
    int threadCompleteCount;
    
    String solution;
    int totDistance;
    
    TSP()
    {
        try
        {
            int  i, j;
            String choice;

            Scanner scan = new Scanner(System.in); // It is the easiest way to read input in a Java program
            System.out.println("Enter the number of cities ");

            size = scan.nextInt();
            scan.skip("\n"); //That's because the Scanner.nextInt method does not consume the last newline character of your input, 
            				 //and thus that newline is consumed in the next call to Scanner.nextLine.

            cities = new String[size];
            routes = new int[size][size];

            System.out.println("Set city names : ");
            for(i=0; i< size; i++)
            {
                System.out.println("City " + (i+1) );
                cities[i] = scan.nextLine();
            }

            System.out.println("Set interconnecting routes ");
            for(i =0; i< size; i++)
            {
		
                for(j =i+1; j<size; j++ )
                {
                    System.out.println("Is there a route between " + cities[i] + " and " + cities[j] + "(y/n) : " );
                    choice = scan.nextLine();
                    if(choice.equalsIgnoreCase("y"))
                    {   
                        System.out.println("Enter distance : ");
                        routes[i][j] = routes[j][i] = scan.nextInt();
                        scan.skip("\n");
                    }
                    else
                    {//no route
                        routes[i][j] = routes[j][i] = 999;
                    }
                }//for(j
            }//for(i    
            
       
            threadCompleteCount = 0;
            solution = "Nearest Neighbour Algorithm couldnt form a tour to visit all cities";
            totDistance = 999;
            
            runners = new Thread[size];
            for(i =0 ; i< size; i++)
            {
                runners[i]= new Thread(this, String.valueOf(i)); // returns the index of ith word on string
                runners[i].start(); // to start the ith thread
            }
        }
        catch(Exception ex)
        {
            System.out.println("Err : "+ ex); //to print the exceptions.
        } 
    }//TSP()
    
    
    void display()
    {
        int i, j;
        for(i = 0; i< size; i++)
        {
            System.out.println();
            System.out.print(cities[i] + " :  ");
            for(j =0; j< size; j++)
            {
                System.out.print( cities[j] + "(" + routes[i][j] + ")   ");
            }
        }//for(i ...
        System.out.println();
    }
    
    public void run()					// this funtion will run automatically
    {
        int sPos = Integer.parseInt(Thread.currentThread().getName()); //this will give a thread id to sPos
        solveTSPUsingNearestNeighbour(sPos);
        threadCompleteCount++;
    }
    
    boolean solveTSPUsingNearestNeighbour(int startPos)
    {
        boolean isTourComplete = false;
        try
        {
            String solution = "";               // overwriting string variable
            int i, j, min,  currentPos, nextPos,  totDistance;
            int visitedCities[];
            int vi;
            
            //initializations and allocations
            
            visitedCities = new int[size];  
            vi =0 ;
            totDistance = 0;
            
            //mark startPos as visited
            visitedCities[vi] = startPos;
            vi++;

            solution = cities[startPos];

            currentPos = startPos; 
            //tour 
            
            while(! isTourComplete)
            {
                nextPos = -1; 
                min = 999;

                for(i =0; i < size; i++)
                {
                    if(routes[currentPos][i] != 999 && currentPos != i)
                    {
                        int flag = 0; 

                        //check for being unvisited
                        for(j =0; j < vi; j++)
                        {
                            if(visitedCities[j] == i)
                            {
                                flag = 1;
                                break;
                            }
                        }//for(j ...

                        if(flag == 0)
                        {//unvisited
                            if(routes[currentPos][i] < min)
                            {
                                min = routes[currentPos][i];
                                nextPos = i;
                            } 
                        }
                    }//if(routes...

                }//for(i ...

                if(nextPos != -1)
                {//move to next city
                    totDistance += min;
                    visitedCities[vi] = nextPos;
                    vi++;
                    solution = solution + "  " + cities[nextPos];
                    currentPos = nextPos;
                }
                else
                {
                    break;
                }

                if(vi == size)
                {
                    //tour back to start city
                    if(routes[currentPos][startPos] != 999)
                    {
                        solution = solution + "  " + cities[startPos];
                        totDistance += routes[currentPos][startPos];
                        isTourComplete = true;
                        if(totDistance < this.totDistance)
                        {
                            this.totDistance = totDistance;
                            this.solution = solution + "\nTotal Distance : " + totDistance;
                        }
                    }
                    else
                    {
                        isTourComplete = false;
                        break;
                    }
                }
            }//while
            
        }
        catch(Exception ex)
        {
            solution = "Err : " + ex.getMessage();
        } 
        return isTourComplete;
    }
    
    void displaySolution()
    {
        
        while(threadCompleteCount < size)
        {
            try
            {
                Thread.sleep(1000);
            }
            catch(Exception ex)
            {}
        }//while
        System.out.println("Solution : " + solution);
    }

    public static void main(String[] args) 
    {
        
        TSP tsp = new TSP();
        tsp.display();
		tsp.displaySolution();
                
    }

}

/* OUTPUT:-
[root@localhost ~]# javac TSP.java
[root@localhost ~]# java TSP
Enter the number of cities 
3
Set city names : 
City 1
NASHIK
City 2
SANGAMNER
City 3
PUNE
Set interconnecting routes 
Is there a route between NASHIK and SANGAMNER(y/n) : 
Y
Enter distance : 
65
Is there a route between NASHIK and PUNE(y/n) : 
Y
Enter distance : 
200
Is there a route between SANGAMNER and PUNE(y/n) : 
Y
Enter distance : 
135

NASHIK :  NASHIK(0)   SANGAMNER(65)   PUNE(200)   
SANGAMNER :  NASHIK(65)   SANGAMNER(0)   PUNE(135)   
PUNE :  NASHIK(200)   SANGAMNER(135)   PUNE(0)   
Solution : NASHIK  SANGAMNER  PUNE  NASHIK
Total Distance : 400
*/
