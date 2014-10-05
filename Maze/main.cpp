#include "main.h"

int main()
{	
	Main::Answer repeat;

	do
	{
		Main::Answer mode;
		Main::Answer speed;
		Main::Answer size;
		AI::Algorithm algo;
	
		int mazeSize;
		int agentSpeed;		

		do
		{
			system("CLS");
			printf("Please choose the agent's speed:\n\n");
			printf("\t1. Instant (not recommended because the solution will not be visual)\n");
			printf("\t2. Fast\n");
			printf("\t3. Normal\n");
			printf("\t4. Slow\n\n");

			printf("Choice: ");

			scanf("%d", &speed);
		} while (	(speed != Main::instant)	&&
					(speed != Main::fast)		&&
					(speed != Main::normal)		&&
					(speed != Main::slow));

		switch (speed)
		{
		case Main::instant:
			agentSpeed = 0;
			break;
		case Main::fast:
			agentSpeed = 30;
			break;
		case Main::normal:
			agentSpeed = 100;
			break;
		case Main::slow:
			agentSpeed = 300;
			break;
		}

		do
		{
			system("CLS");
			printf("Please choose the maze size:\n\n");
			printf("\t1. Small\n");
			printf("\t2. Medium\n");
			printf("\t3. Big\n\n");

			printf("Choice: ");

			scanf("%d", &size);
		} while (	(size != Main::smallMaze)  &&
					(size != Main::mediumMaze) && 
					(size != Main::bigMaze));

		switch (size)
		{
		case Main::smallMaze:
			mazeSize = 11;
			break;
		case Main::mediumMaze:
			mazeSize = 23;
			break;
		case Main::bigMaze:
			mazeSize = 37;
			break;
		}

		do
		{
			system("CLS");
			printf("Please choose the algorithm to solve with:\n\n");
			printf("\t1. Depth First Search\n");
			printf("\t2. Breadth First Search\n");
			printf("\t3. Uniform Cost Search\n");
			printf("\t4. Iterative Deepening Search\n\n");

			printf("Choice: ");

			scanf("%d", &algo);
		} while (	(algo != AI::DFS)	&&
					(algo != AI::BFS)	&&
					(algo != AI::UCS)	&&
					(algo != AI::IDS));

		Maze thisMaze(mazeSize, mazeSize);
		AI solver(thisMaze, agentSpeed);

		auto start = high_resolution_clock::now();
		solver.Solve(algo);
		auto end = high_resolution_clock::now();
		auto elapsed = duration_cast<milliseconds>(end - start);

		printf("CPU time (in milliseconds): %d\n\n", elapsed.count());

		do
		{
			printf("Run again?\n\n");
			printf("\t1. Yes\n");
			printf("\t2. No\n\n");

			printf("Choice: "); 

			scanf("%d", &repeat);
		} while (	(repeat != Main::yes) &&
					(repeat != Main::no));

	} while (repeat == Main::yes);

	return 0;
}