#include "AI.h"

/*****************************************************************************/
/*                              Constructor                                  */
/*****************************************************************************/
AI::AI(Maze mazeObj, int givenSpeed)
: 
mazeCopy(mazeObj),
speed(givenSpeed)
{}
/*****************************************************************************/
/*                            Solve Function                                 */
/*****************************************************************************/
void AI::Solve(Algorithm algo)
{
	switch (algo)
	{
	case AI::DFS:
		DepthFirstSearch(mazeCopy.start);
		break;
	case AI::BFS:
		BreadthFirstSearch(mazeCopy.start);
		break;
	case AI::UCS:
		UniformCostSearch(mazeCopy.start);
		break;
	case AI::IDS:
		IterativeDeepeningSearch(mazeCopy.start);
		break;
	}
	CopyPath(algo);
}
/*****************************************************************************/
/*                      Search Algorithm Functions                           */
/*****************************************************************************/
void AI::DepthFirstSearch(Cell* cell)
{
	deque<Cell*> stack;
	bool isDeadEnd;

	stack.push_back(cell);

	while (!stack.empty())
	{
		isDeadEnd = true;
		cell = stack.back();
		helperPath.push_back(cell);

		SetEnvironment(cell, State::visited);
		PrintEnvironment();

		if (IsExit(cell))
		{
			break;
		}

		for (int i = 0; i < cell->neighbors.size(); i++)
		{
			if (cell->neighbors[i].cell->state == State::empty)
			{
				stack.push_back(cell->neighbors[i].cell);
				isDeadEnd = false;
			}
		}
		
		if (isDeadEnd)
		{
			stack.pop_back();
			helperPath.pop_back();

			SetEnvironment(cell, State::deadEnd);
			PrintEnvironment();
		}
	}
}

void AI::BreadthFirstSearch(Cell* cell)
{
	deque<Cell*> queue;

	queue.push_front(cell);

	while (!queue.empty())
	{
		cell = queue.back();
		queue.pop_back();

		SetEnvironment(cell, State::visited);
		PrintEnvironment();

		if (IsExit(cell))
		{
			break;
		}

		for (int i = cell->neighbors.size() - 1; i >= 0; i--)
		{
			if (cell->neighbors[i].cell->state == State::empty)
			{
				cell->neighbors[i].cell->parent = cell;
				queue.push_front(cell->neighbors[i].cell);
			}
		}
	}
}

void AI::UniformCostSearch(Cell* cell)
{
	priority_queue<CellWithCost, vector<CellWithCost>, Comparator> priorityQueue;

	CellWithCost temp = { cell, 0 };
	CellWithCost tempNeighbor;
	int tempCost = 0;

	priorityQueue.push(temp);

	SetEnvironment(temp.cell, State::visited);

	while (!priorityQueue.empty())
	{
		temp = priorityQueue.top();
		priorityQueue.pop();

		SetEnvironment(temp.cell, State::visited);
		PrintEnvironment();

		if (IsExit(temp.cell))
		{
			break;
		}

		for (int i = temp.cell->neighbors.size() - 1; i >= 0; i--)
		{
			if (temp.cell->neighbors[i].cell->state == State::empty)
			{
				temp.cell->neighbors[i].cell->parent = temp.cell;
				tempCost = GetTotalCost(temp.cell->neighbors[i].cell);
				
				tempNeighbor = { temp.cell->neighbors[i].cell, tempCost };

				priorityQueue.push(tempNeighbor);
			}
		}
	}
}

void AI::IterativeDeepeningSearch(Cell* cell)
{
	Cell* temp;
	int bound = 0;

	while (true)
	{
		temp = IDShelper(cell, bound);

		if (IsExit(temp))
		{
			break;
		}
		bound++;
	} 	
}
/*****************************************************************************/
/*                           Helper Functions                                */
/*****************************************************************************/
Cell* AI::IDShelper(Cell* cell, int bound)
{
	Cell* temp = cell;

	SetEnvironment(cell, State::visited);
	PrintEnvironment();

	helperPath.push_back(cell);

	if (bound > 0)
	{
		for (int i = 0; i < cell->neighbors.size(); i++)
		{
			if (cell->neighbors[i].cell->state == State::empty)
			{
				temp = IDShelper(cell->neighbors[i].cell, bound - 1);

				if (IsExit(temp))
				{
					return temp;
				}
			}			
		}		
	}
	else if (IsExit(cell))
	{
		return cell;
	}

	SetEnvironment(cell, State::empty);
	PrintEnvironment();

	helperPath.pop_back();

	return temp;
}

bool AI::IsExit(Cell* cell)
{
	return (cell->row == mazeCopy.exit->row) && (cell->column == mazeCopy.exit->column);
}

bool AI::IsStart(Cell* cell)
{
	return (cell->row == mazeCopy.start->row) && (cell->column == mazeCopy.start->column);
}

int AI::GetTotalCost(Cell* cell)
{
	int cost = 0;

	for (Cell* var = cell; !IsStart(var); var = var->parent)
	{
		cost += Cell::GetLinkWeight(var, var->parent);
	}
	return cost;
}

/*****************************************************************************/
/*                                 Misc                                      */
/*****************************************************************************/
void AI::SetEnvironment(Cell* cell, State state)
{
	cell->state = state;
	mazeCopy.maze[cell->row][cell->column].state = state;
}

void AI::PrintEnvironment()
{	
	if (speed > 0)
	{
		system("CLS");
		mazeCopy.Print();
		Sleep(speed);
	}
}

void AI::CopyPath(Algorithm algo)
{	
	switch (algo)
	{
	case AI::DFS:
	case AI::IDS:
		for each (Cell* cell in helperPath)
		{			
			if (cell->state != State::deadEnd)
			{
				finalPath.push_front(cell);
			}
		}
		break;
	case AI::BFS:
	case AI::UCS:
		for (Cell* cell = mazeCopy.exit; !IsStart(cell); cell = cell->parent)
		{
			finalPath.push_back(cell);			
		}
		finalPath.push_back(mazeCopy.start);
		break;
	}
	PrintPath();
}

void AI::PrintPath()
{
	for each (Cell* cell in finalPath)
	{
		SetEnvironment(cell, State::solution);
		PrintEnvironment();
	}
}