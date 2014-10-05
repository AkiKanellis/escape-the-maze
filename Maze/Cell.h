#include <vector>

#pragma once
using namespace std;

/**
 *enum char class for keeping the state of each cell as both a enum word and a char
 *
 *@wall		- cell is a wall and can't be traversed
 *@empty	- cell is empty and can be traversed
 *@visited	- cell has already been visited
 *@deadEnd	- cell has already been visited and leads to a dead end
 *@solution	- cell leads to the solution that was found found
 */
enum class State : char
{
	wall		= '#',
	empty		= ' ',
	visited		= '*',
	deadEnd		= '~',
	solution	= '.'
};

/**
 *Cell is the data structure used to represent each room in the maze
 *
 *@parent		- stores the cell visited prior to visiting the current cell
 *@row			- row of the maze vector that the cell corresponds to
 *@column		- column of the maze vector that the cell corresponds to
 *@neighbors	- a vector of cells that this cell is connected with
 *@state		- the state that the cell is at
 */
class Cell
{
/*****************************************************************************/
/*                        User Defined Variables                             */
/*****************************************************************************/
public:
	/**
	*CellLink is used to store the weight of the link between two cells
	*
	*@cell		- pointer to the second cell on the link
	*@weight	- weight of the link (randomly assigned)
	*/
	struct CellLink
	{
		Cell *cell;
		int weight;
	};
/*****************************************************************************/
/*                               Functions                                   */
/*****************************************************************************/
public:
	/**
	 *Returns the weight of the link between two cells
	 *
	 *@first	- first cell
	 *@second	- second cell
	 */
	static int GetLinkWeight(Cell* first, Cell* second);
/*****************************************************************************/
/*                            Class Variables                                */
/*****************************************************************************/
public:
	Cell* parent;
	int row;
	int	column;
	vector<CellLink> neighbors;
	State state;
};
