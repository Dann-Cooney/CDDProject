 /*

	Authors: Johnathan Finlay
			 Daniel Cooney

	Start Date: 2/12/17
	
	Descritpion: Implementation of the Wator Simulation 

	Last Updated: Time - 14:34
				  Date - 5/12/17 

----------------------------------------------------
 */


#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <time.h>

using namespace std;

char const water = '.';
char const fish = 'O';
char const shark = 'X';

class Grid
{
public:
    char symbol;
    int age;
    int hunger;
    bool processed;

// blank constructor
    Grid()
{
    symbol = water;
    age = 0;
    hunger = 0;
    
}
   Grid(char type)
{
   if (type == fish)
   {
    symbol = fish;
    age = 0;
    processed = true;
   }
   else
   {
     symbol = shark;
     age = 0;
     hunger =0;
   }
}
};


int nFish = 1;
int nShark = 0;
int const width = 15;
int const height = 15;
int randomXPos = 0;
int randomYPos = 0;


void draw(vector<vector<Grid>> &sea )
{
	system("clear");
for(int i = 0; i < width; i++)
    {
        for(int j= 0; j < height; j++)
            {
		cout << sea[i][j].symbol;
	    }
	cout << endl;
    }
}

void populate(vector<vector<Grid>> &sea , int nFish, int nShark)
{
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
	int x2;
	int y2;
}
void moveFish(vector<vector<Grid>> &sea , int x ,int y)
{
	bool up = check(sea, x , y -1 );
	bool down  = check(sea, x , y + 1 );
	bool left  = check(sea, x -1 , y);
	bool right  = check(sea, x +1, y);

	int direction = rand() % 4; 
	int i = 0;


		if (direction == 0 && left)
		{
			//left
			cout << "left";
			int newPos = (y - 1) % height;
			sea[x][newPos] = sea[x][y];
			sea[x][newPos].processed = true;
			sea[x][y] = Grid();
			i = 4;
		}
		else if (direction == 1 && right)
		{
			cout << "right";
			int newPos = (y + 1) % height;
			
			sea[x][newPos] = sea[x][y];
			sea[x][newPos].processed = true;
			sea[x][y] = Grid();
			i = 4;
		}
		else if (direction == 2 && up)
		{
			cout << "up";
			int newPos = (x - 1) % width;
			sea[newPos][y] = sea[x][y];
			sea[newPos][y].processed = true;
			sea[x][y] = Grid();
			i = 4;
		}
		else if (direction == 3 && down)
		{
			cout << "down";
			int newPos = (x + 1) % width;
			sea[newPos][y] = sea[x][y];
			sea[newPos][y].processed = true;
			sea[x][y] = Grid();
			i = 4;
		}
	
}
void sim(vector<vector<Grid>> &sea )
{
	for(int i = 0; i < width; i++)
    {
        for(int j= 0; j < height; j++)
            {
            	if(sea[i][j].processed == false)
            	{
            		if(sea[i][j].symbol == fish)
	            	{
	            		//move fish
	            		moveFish(sea, i, j);
	            	}
	            	else if (sea[i][j].symbol == shark)
	            	{
	            		/* code */
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
	//createSea(sea);
    draw(sea);
	populate(sea, nFish, nShark);
	while(true)
	{
		sim(sea);
		resetFish(sea);
		draw(sea);
		cin.get();
	}
}
