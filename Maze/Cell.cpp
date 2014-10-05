#include "Cell.h"

/*****************************************************************************/
/*                                  Misc                                     */
/*****************************************************************************/
int Cell::GetLinkWeight(Cell* first, Cell* second)
{
	for (int k = 0; k < first->neighbors.size(); k++)
	{
		if (first->neighbors[k].cell->row == second->row &&
			first->neighbors[k].cell->column == second->column)
		{
			return first->neighbors[k].weight;
		}
	}
}