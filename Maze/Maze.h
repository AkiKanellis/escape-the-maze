#include "Cell.h"

#include <time.h>
#include <windows.h>

#include <iostream>
#include <algorithm>



/**
 *The number of steps the generator agent checks ahead every time to see if
 *there is a wall or an empty spot
 */
#define STEP 2


#pragma once
using namespace std;

/**
 *Maze is the class that will construct the maze vector, define each cell's
 *neighbors, define the costs of the links and the start and end of the maze
 *
 *@maze		- a 2D Cell vector which holds the cells
 *@height	- final height of the vector
 *@width	- final width of the vector
 *@start	- starting point of the maze (top left corner)
 *@exit		- ending point of the maze (bottom right corner)
 *@order	- used by DefineNeighbors() to know in which order to push() the
 *            cells in the neighbors vector, it will push them in reverse order
 *			  example: If you want a cell to check its children through the
 *					   order: right, down, left, up then you have to initialize
 *					   the vector in reverse like this
 *					   order({ { up, left, down, right } })
 */
class Maze
{
/*****************************************************************************/
/*                        User Defined Variables                             */
/*****************************************************************************/
public:
	/**
	 *enum Direction is used to define in which direction the maze generator
	 *will make its move and its also used to define the order in which the
	 *neighbors are going to be added (by using the order vector)
	 */
	enum Direction
	{
		right,
		down,
		left,
		up
	};
/*****************************************************************************/
/*                               Functions                                   */
/*****************************************************************************/
public:
	/**
	 *The Maze constructor initializes the width and height to the given ones,
	 *initializes the order of cell checking, feeds the srand with the clock
	 *of the computer, resizes the vector to the dimensions given,
	 *initializes the properties row, column and state of each cell and then
	 *generates the maze and defines its neighbors
	 *
	 *@givenWidth	-	the width given to the constructor
	 *@givenHeight	-	the height given to the constructor
	 */
	Maze(int givenWidth, int givenHeight);

	/**
	 *Used to print the maze array
	 */
	void Print();
private:
	/**
	 *Generates the maze by producing a random odd row, a random odd column,
	 *changing the state of the random cell chosen to empty and then feeding
	 *that cell to the recursive function
	 */
	void GenerateMaze();

	/**
	 *Accepts a cell (through the row and the column), checks in a random direction
	 *if number of STEP ahead is a wall and if it is, it tears that wall and the
	 *previous one down to create a path. Then it recursively calls the function
	 *to the new position.
	 */
	void Recursion(int row, int column);

	/**
	 *Generates four random directions for the generator agent to take consecutively
	 *
	 *@return vector<Direction> - returns a vector of the four directions
	 *
	 *example: {up, down, right, left}
	 */
	vector<Direction> GenerateRandomDirections();

	/**
	 *For every empty cell in the vector it defines its neighbors by checking
	 *every adjacent cell if it is empty, if it is then it adds a pointer of it
	 *to the internal neighbors vector of the cell
	 */
	void DefineNeighbors();

	/**
	*For every empty cell in the vector it defines it's link weight with each one
	*of it's neighbors by adding a random weight only to the neighbors that had
	*their weight initialised to zero and from the neighbors to the current cell.
	*With that way we manage to have the same weight both ways on the link
	*/
	void DefineCosts();
/*****************************************************************************/
/*                            Class Variables                                */
/*****************************************************************************/
public:	
	vector <vector<Cell> > maze;
	int height;
	int width;

	Cell* start;
	Cell* exit;
	vector <Direction> order;
};