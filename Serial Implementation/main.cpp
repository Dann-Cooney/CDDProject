/*

  -----------------------------------------------------------
 |	Authors:        | Daniel Cooney   || Jonathan Finlay     | 
 |	Start Date: 	| 2/12/17                                |
 |	Descritpion: 	| Implementation of the Wator Simulation |
 |	Last Updated: 	| Date - 5/1/18 || Time - 02:50am        |
  -----------------------------------------------------------


 */


#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Creating the symbols for each of the objects
char water = '.';
char fish = 'O';
char shark = 'X';


class Grid
{
	public:
    	char symbol;
    	int age;
    	int hunger;
    	bool processed;

	// Constructor for the Grid.
    Grid()
	{
    	symbol = water;
    	age = 0;
    	hunger = 0;
   	}

	// Contstructor for types: Fish and Sharks
    Grid(char type)
	{
   		if (type == fish)
   			{
			    symbol = fish;
			    age = 0;
			    processed = true;
  			}
	    else if(type == water)
	  		{
			   	symbol = water;
			    age = 0;
			    hunger = 0;
	   		}
	    else
	   		{
			    symbol = shark;
			    age = 0;
			    hunger = 0;
			    processed = true;
	   		}
	}

};


int nFish = 30;
int nShark = 2;
int const width = 15;
int const height = 15;
int randomXPos = 0;
int randomYPos = 0;
int fishBreed = 4;
int sharkBreed = 6;


//creating the sea grid
void draw(vector<vector<Grid>> &sea )
{
	system("clear");

		for(int i = 0; i < height; i++)
	    {
	  
	        for(int j= 0; j < width; j++)
	            {
					cout << sea[j][i].symbol;
					
		    	}

			cout << endl;
	    }
	 
}

//METHOD -- Used to populate grid with fish and sharks.
void populate(vector<vector<Grid>> &sea , int nFish, int nShark)
{
	//Checking for available space for fish
	while (nFish > 0)
	{
	    randomXPos = rand() % width;
	    randomYPos = rand() % height;
	    if (sea[randomXPos][randomYPos].symbol == water)
	    {
			sea[randomXPos][randomYPos] = Grid(fish);
			--nFish;
	    }
	    	
	}
	//Checking for available space for sharks
	while (nShark > 0)
	{
	    randomXPos = rand() % width;
	    randomYPos = rand() % height;
	    if (sea[randomXPos][randomYPos].symbol == water)
	    {
			sea[randomXPos][randomYPos] = Grid(shark);
			--nShark;
	    }
	}
}

bool check(vector<vector<Grid>> &sea , int x ,int y)
{

	if (x < 0 || x >= width)
	{
		if(x < 0)
		{
			x = width -1;
		}
		else
		{
			x = 0;
		}

	}

	if (y < 0 || y >= height)
	{
		if(y < 0)
		{
			y = height -1;
		}
		else
		{
			y = 0;
		}
	}

	if(sea[x][y].symbol == water)
	{
		return true;

	}
	// Stopping a shark from overlapping another shark. 
	if(sea[x][y].symbol == shark)
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool checkFish(vector<vector<Grid>> &sea , int x ,int y)
{
	if (x < 0 || x >= width)
	{
		if(x < 0)
		{
			x = width -1;
		}
		else
		{
			x = 0;
		}
	}

	if (y < 0 || y >= height)
	{
		if(y < 0)
		{
			y = height -1;
		}
		else
		{
			y = 0;
		}
	}
	//If there is a fish close the shark will go
	if(sea[x][y].symbol == fish)
	{
		return true;

	}
	else
	{
		return false;
	}


}
	
// Method for the next move of the fish
void moveFish(vector<vector<Grid>> &sea , int x ,int y)
{

	//creating variables for the next available position 
	bool up = check(sea, x , y -1 );
	bool down  = check(sea, x , y + 1 );
	bool left  = check(sea, x -1 , y);
	bool right  = check(sea, x +1, y);
	int move = 0;

	if(up || down || left || right)
	{
		move = 1;
	}

	if(move == 0)
	{
		sea[x][y].age++;
		sea[x][y].processed = true;
	}
	else	
	{   
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && up)
			{
				int newPos = y - 1;
				if(newPos < 0)
				{
					newPos = width - 1;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].processed = true;
				sea[x][newPos].age++;
				sea[x][y] = Grid();
				move = 0;
				if(sea[x][newPos].age >= fishBreed)
				{
					sea[x][y] = Grid(fish);
					sea[x][newPos].age = 0;
					nFish++;
				}
			}
			else if (direction == 1 && down)
			{
				int newPos = y + 1;
				if(newPos >= width)
				{
					newPos = 0;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].processed = true;
				sea[x][newPos].age++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].age >= fishBreed)
				{
					sea[x][y] = Grid(fish);
					sea[x][newPos].age = 0;
					nFish++;
				}
			}
			else if (direction == 2 && left)
			{
				int newPos = x - 1;
				if(newPos < 0)
				{
					newPos = height - 1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].processed = true;
				sea[newPos][y].age++;
				sea[x][y] = Grid();
				move = 0;
				if(sea[newPos][y].age >= fishBreed)
				{
					sea[x][y] = Grid(fish);
					sea[newPos][y].age = 0;
					nFish++;
				}		
			}
			else if (direction == 3 && right)
			{
				int newPos = x + 1 ;
				if(newPos >= height)
				{
					newPos = width - 1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].processed = true;
				sea[newPos][y].age++;
				sea[x][y] = Grid();
				move = 0;
				if(sea[newPos][y].age >= fishBreed)
				{
					sea[x][y] = Grid(fish);
					sea[newPos][y].age = 0;
					nFish++;
				}
			}
		}
	}
	
	
}
// Method for the next move of the shark
void moveShark(vector<vector<Grid>> &sea , int x ,int y)
{
	//creating variables for the next available position 
	bool up = checkFish(sea, x , y -1 );
	bool down  = checkFish(sea, x , y + 1 );
	bool left  = checkFish(sea, x -1 , y);
	bool right  = checkFish(sea, x +1, y);
	int move = 0;
   	
	
	// VALIDATION -- if a shark eats a fish
	if(up || down || left || right)
	{
		move = 1;
		
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && up)
			{
				int newPos = y - 1;
				if(newPos < 0)
				{
					newPos = width - 1;
				}
				sea[x][newPos] = sea[x][y]; //moves the shark or fish
				sea[x][newPos].processed = true;
				sea[x][newPos].age++;
				sea[x][newPos].hunger = 0;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hunger == 4)
				{
					sea[x][newPos] = Grid();
					nShark--;
				}
				
				if(sea[x][newPos].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[x][newPos].age = 0;
					sea[x][newPos].hunger = 0;
					nShark++;
				}
				
			}
			else if (direction == 1 && down)
			{
				int newPos = y + 1;
				if(newPos >= width)
				{
					newPos = 0;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].processed = true;
				sea[x][newPos].age++;
				sea[x][newPos].hunger = 0 ;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hunger == 4)
				{
					sea[x][newPos]= Grid();
					nShark--;
				}
			
				if(sea[x][newPos].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[x][newPos].age = 0;
					sea[x][newPos].hunger = 0;
					nShark++;
				}
				
			}
			else if (direction == 2 && left)
			{
			
				int newPos = x - 1;
				if(newPos < 0)
				{
					newPos = height -1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].processed = true;
				sea[newPos][y].age++;
				sea[newPos][y].hunger = 0 ;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hunger == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
					
				}
				
				if(sea[newPos][y].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[newPos][y].age = 0;
					sea[x][newPos].hunger = 0;
					nShark++;
				}		

			}
			else if (direction == 3 && right)
			{
				int newPos = x + 1 ;
				if(newPos >= height)
				{
					newPos = 0;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].processed = true;
				sea[newPos][y].age++;
				sea[newPos][y].hunger = 0;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hunger == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
				}

				if(sea[newPos][y].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[newPos][y].age = 0;
					sea[x][newPos].hunger = 0;
					nShark++;
				}
			}	
	}
}
	else
	{
		up = check(sea, x , y -1 );
		down  = check(sea, x , y + 1 );
		left  = check(sea, x -1 , y);
		right  = check(sea, x +1, y);

		if(up || down || left || right)
		{
			move = 1;
		}
	}
	
	if(move == 0)
	{
		sea[x][y].age++;
		sea[x][y].hunger++;

		if(sea[x][y].hunger == 4)
				{
					sea[x][y] = Grid();
					nShark--;
				}

		sea[x][y].processed = true;
	}
	else
   	{
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && up)
			{
				int newPos = y - 1;
				if(newPos < 0)
				{
					newPos = width - 1;
				}
				sea[x][newPos] = sea[x][y]; //moves the shark or fish
				sea[x][newPos].processed = true;
				sea[x][newPos].age++;
				sea[x][newPos].hunger++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hunger == 4)
				{
					sea[x][newPos] = Grid();
					nShark--;
				}
				
				if(sea[x][newPos].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[x][newPos].age = 0;
					nShark++;
				}
				
			}
			else if (direction == 1 && down)
			{
				int newPos = y + 1;
				if(newPos >= width)
				{
					newPos = 0;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].processed = true;
				sea[x][newPos].age++;
				sea[x][newPos].hunger++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hunger == 4)
				{
					sea[x][newPos]= Grid();
					nShark--;
				}
			
				if(sea[x][newPos].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[x][newPos].age = 0;
					nShark++;
				}
			
			}
			else if (direction == 2 && left)
			{
			
				int newPos = x - 1;
				if(newPos < 0)
				{
					newPos = height -1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].processed = true;
				sea[newPos][y].age++;
				sea[newPos][y].hunger++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hunger == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
					
				}
				

				
				if(sea[newPos][y].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[newPos][y].age = 0;
					nShark++;
				}		

			
			}
			else if (direction == 3 && right)
			{
				int newPos = x + 1 ;
				if(newPos >= height)
				{
					newPos = 0;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].processed = true;
				sea[newPos][y].age++;
				sea[newPos][y].hunger++;

				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hunger == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
				}

				
				if(sea[newPos][y].age >= sharkBreed)
				{
					sea[x][y] = Grid(shark);
					sea[newPos][y].age = 0;
					nShark++;
				}
				
			}
		}
	}
	
}
void sim(vector<vector<Grid>> &sea )
{
	for(int i = 0; i < height; i++)
    {
        for(int j= 0; j < width; j++)
            {
            	if(sea[j][i].processed == false)
            	{
            		if(sea[j][i].symbol == fish)
	            	{
	            		//move fish
	            		moveFish(sea, j, i);
	            	}
	            	else if (sea[j][i].symbol == shark)
	            	{
	            		moveShark(sea, j,i);
	            	}
	            	else
	            	{

	            	}
            	}
            }
    }
}
void resetFish(vector<vector<Grid>> &sea)
{
	for(int i = 0; i < width; i++)
    {
        for(int j= 0; j < height; j++)
            {
				sea[i][j].processed = false;
	    	}
    }
}

int main(void) 
{
	srand(time(NULL));
	vector<vector<Grid>> sea ;
	sea.resize(width);
	
	for( int i = 0; i < width; i++)
	{
		sea[i].resize(height);
	}
   	
	populate(sea, nFish, nShark);
	int i = 1;

	while(true)
	{
		

		resetFish(sea);
		draw(sea);
		sim(sea);
		cout << endl;
		cout << "_______WATOR Simulation______" << endl;

	 this_thread::sleep_for(chrono::milliseconds(400));

	}
}


