#include "Maze.h"

/*****************************************************************************/
/*                              Constructor                                  */
/*****************************************************************************/
Maze::Maze(int givenWidth, int givenHeight)
:
width(givenWidth),
height(givenHeight),
order({ { up, left, down, right } })
{
	srand((unsigned int)time(NULL));	

	maze.resize(height);
	for (int i = 0; i < height; i++)
	{
		maze[i].resize(width);
		for (int j = 0; j < width; j++)
		{
			maze[i][j].row = i;
			maze[i][j].column = j;
			maze[i][j].state = State::wall;			
		}
	}

	GenerateMaze();
	DefineNeighbors();
	DefineCosts();

	start = &maze[1][1];
	exit = &maze[height - 2][width - 2];
}

/*****************************************************************************/
/*                          Generator Functions                              */
/*****************************************************************************/
void Maze::GenerateMaze()
{
	// Generate random odd row (1 ~ (height - 2))
	int row;
	do{
		row = (rand() % (height - 2)) + 1;
	} while (row % 2 == 0);

	// Generate random odd column (1 ~ (width - 2))
	int column;
	do{
		column = (rand() % (width - 2)) + 1;
	} while (column % 2 == 0);

	// Starting cell
	maze[row][column].state = State::empty;

	//　Allocate the maze with recursive method
	Recursion(row, column);
}

void Maze::Recursion(int row, int column) {

	vector<Direction> directions = Maze::GenerateRandomDirections();

	// Examine each direction
	for each (Direction var in directions)
	{
		switch (var)
		{
		case up:
			//　If 2 cells up is not out AND you found a wall
			if ((row - STEP > 0) && (maze[row - STEP][column].state == State::wall))
			{
				maze[row - STEP][column].state = State::empty;
				maze[row - STEP / 2][column].state = State::empty;
				Maze::Recursion(row - STEP, column);
			}
			break;
		case right:
			//　If 2 cells right is not out AND you found a wall
			if ((column + STEP < width - STEP / 2) && (maze[row][column + STEP].state == State::wall))
			{
				maze[row][column + STEP].state = State::empty;
				maze[row][column + STEP / 2].state = State::empty;
				Maze::Recursion(row, column + STEP);
			}
			break;
		case down:
			//　If 2 cells down is not out AND you found a wall
			if ((row + STEP < height - STEP / 2) && (maze[row + STEP][column].state == State::wall))
			{
				maze[row + STEP][column].state = State::empty;
				maze[row + STEP / 2][column].state = State::empty;
				Maze::Recursion(row + STEP, column);
			}
			break;
		case left:
			//　If 2 cells left is not out AND you found a wall
			if ((column - STEP > 0) && (maze[row][column - STEP].state == State::wall))
			{
				maze[row][column - STEP].state = State::empty;
				maze[row][column - STEP / 2].state = State::empty;
				Maze::Recursion(row, column - STEP);
			}
			break;
		}
	}
}

vector<Maze::Direction> Maze::GenerateRandomDirections()
{
	vector<Direction> directions{ { right, down, left, up } };
	 
	 random_shuffle(directions.begin(), directions.end());

	 return directions;
}

/*****************************************************************************/
/*                        Cell Defining Functions                            */
/*****************************************************************************/
void Maze::DefineNeighbors()
{
	// For every cell in the vector
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// If it is empty
			if (maze[i][j].state == State::empty)
			{
				// For every adjacent cell if empty then push it to the vector
				for each (Direction var in order)
				{
					Cell::CellLink temp;
					switch (var)
					{
					case up:
						if (maze[i - 1][j].state == State::empty)
						{
							temp = { &maze[i - 1][j], 0 };
							maze[i][j].neighbors.push_back(temp);
						}
						break;
					case right:
						if (maze[i][j + 1].state == State::empty)
						{
							temp = { &maze[i][j + 1], 0 };
							maze[i][j].neighbors.push_back(temp);
						}
						break;
					case down:
						if (maze[i + 1][j].state == State::empty)
						{
							temp = { &maze[i + 1][j], 0 };
							maze[i][j].neighbors.push_back(temp);
						}
						break;
					case left:
						if (maze[i][j - 1].state == State::empty)
						{
							temp = { &maze[i][j - 1], 0 };
							maze[i][j].neighbors.push_back(temp);
						}
						break;
					}
				}
			}
		}
	}	
}

void Maze::DefineCosts()
{
	// For every cell in the vector
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// If it is empty
			if (maze[i][j].state == State::empty)
			{
				/**
				 *For every adjacent cell if the weight between this cell and 
				 *it's neighbor is zero then add a random weight from the first
				 *cell to the second and vice versa
				 */
				for (int k = 0; k < maze[i][j].neighbors.size(); k++)
				{
					int neighborRow = maze[i][j].neighbors[k].cell->row;
					int neighborColumn = maze[i][j].neighbors[k].cell->column;
					int cost = (rand() % 100) + 1;

					if (maze[i][j].neighbors[k].weight == 0)
					{
						maze[i][j].neighbors[k].weight = cost;
						for (int l = 0; l < maze[neighborRow][neighborColumn].neighbors.size(); l++)
						{							
							if (maze[neighborRow][neighborColumn].neighbors[l].cell->row == maze[i][j].row &&
								maze[neighborRow][neighborColumn].neighbors[l].cell->column == maze[i][j].column)
							{
								maze[neighborRow][neighborColumn].neighbors[l].weight = cost;
								break;
							}
						}
					}
				}
			}
		}
	}
}

/*****************************************************************************/
/*                                 Misc                                      */
/*****************************************************************************/
void Maze::Print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; ++j)
		{
			cout << (char)maze[i][j].state;
		}
		cout << endl;
	}
	cout << endl;
}