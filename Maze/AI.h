#include "Maze.h"

#include <stdio.h>

#include <iostream>
#include <deque>
#include <queue>


#pragma once

/**
 *AI is the class that will solver the maze vector through the search algorithm
 *that was given
 *
 *@mazeCopy		- a copy of the Maze object that was given to the constructor
 *@helperPath	- helper path for DFS and IDS
 *@finalPath	- final path that will be printed on the maze
 *@speed		- speed of the agent (in milliseconds, higher is slower)
 */
class AI
{
/*****************************************************************************/
/*                        User Defined Variables                             */
/*****************************************************************************/
public:
	/**
	 *enum for storing the choise given in the main function. It's also used for
	 *the Solve function to choose which algorithm to implement
	 */
	enum Algorithm
	{
		DFS = 1,
		BFS = 2,
		UCS = 3,
		IDS = 4
	};
private:
	/**
	 *Used by the Uniform Cost Search algorithm in order to keep a data structure
	 *in the queue capable of storing both the cell and the total cost to get to
	 *the cell from the specific path taken
	 *
	 *@cell		- the cell that was stored
	 *@cost		- total cost of the specific path that was taken 
	 */
	struct CellWithCost
	{
		Cell* cell;
		int cost;
	};

	/**
	 *Comparator is used to overload the "()" operator. That is done with the
	 *goal of having our priority queue in UCS sorting the items by checking
	 *the cost of each CellWithCost element
	 */
	struct Comparator
	{
		bool operator()(CellWithCost const lfs, CellWithCost const rhs)
		{
			return lfs.cost > rhs.cost;
		}
	};	
/*****************************************************************************/
/*                               Functions                                   */
/*****************************************************************************/
public:
	/**
	 *The AI constructor copies the Maze object to a new Maze object and also
	 *defines the speed of the agent
	 *
	 *@mazeObj		- the Maze object given
	 *@givenSpeed	- the agent's given speed (in milliseconds, higher is slower)
	 */
	AI(Maze mazeObj, int givenSpeed);

	/**
	 *Solve runs the search algorithm chosen and then calls the CopyPath function
	 *in order to copy the path found to the finalPath deque
	 *
	 *@algo - the algorithm that was chosen
	 */
	void Solve(Algorithm algo);
private:
	/**
	 *The Depth First Search algorithm will go as deep as it can in our graph before
	 *trying to expand the other neighbors for every cell. DFS doesn't find the 
	 *shortest path!
	 *
	 *@cell - the root cell
	 */
	void DepthFirstSearch(Cell* cell);

	/**
	 *The Breadth First Search algorithm will first expand the neighbors and then
	 *move on deeper to the graph. BFS finds the shortest path but not if we take
	 *into account the cost of the links!
	 *
	 *@cell - the root cell
	 */
	void BreadthFirstSearch(Cell* cell);

	/**
	 *The Uniform Cost Search algorithm is basically the same as the Breadth First
	 *Search but it takes into account the cost of each link in the graph.
	 *UFS will find both the shortest and cheaper path in the maze!
	 *
	 *@cell - the root cell
	 */
	void UniformCostSearch(Cell* cell);

	/**
	 *Iterative Deepening Search combines depth-first search's space-efficiency
	 *and breadth-first search's completeness in order to find the the path to
	 *the exit.
	 *
	 *@cell - the root cell
	 */
	void IterativeDeepeningSearch(Cell* cell);

	/**
	 *Used by IterativeDeepeningSearch in order to recursively check the cells
	 *based on the bound given
	 *
	 *@cell		- the input cell
	 *@bound	- the bound given
	 *@return	- cell returned to be checked if it is the exit cell
	 */
	Cell* IDShelper(Cell* cell, int bound);


	/**
	*Takes a cell as input and outputs if that cell is the start cell
	*
	*@cell		- the input cell
	*@return	- true if cell is start cell, false if otherwise
	*/
	bool IsStart(Cell* cell);

	/**
	*Takes a cell as input and outputs if that cell is the exit cell
	*
	*@cell		- the input cell
	*@return	- true if cell is exit cell, false if otherwise
	*/
	bool IsExit(Cell* cell);

	/**
	 *Returns the total cost from start to cell
	 *
	 *@cell		- the input cell
	 *@return	- total path cost
	 */
	int GetTotalCost(Cell* cell);

	/**
	 *Sets the environment to the desired state
	 *
	 *@cell		- the input cell
	 *@state	- the desired state
	 */
	void SetEnvironment(Cell* cell, State state);

	/**
	 *Prints the environment in a speed based on the speed given
	 */
	void PrintEnvironment();

	/**
	 *Depending on the algorithm, copies the path to the finalPath deque and
	 *then it prints that path by calling PrintPath
	 *
	 *@algo - the algorithm that was chosen
	 */
	void CopyPath(Algorithm algo);
	
	/**
	 *Prints the solution path on the maze by setting the path found to solution
	 *and then printing that envirnment based on the speed given
	 */
	void PrintPath();
/*****************************************************************************/
/*                            Class Variables                                */
/*****************************************************************************/
private:
	Maze mazeCopy;

	deque<Cell*> helperPath;
	deque<Cell*> finalPath;

	int speed;
};