#include "Maze.h"
#include "AI.h"

#include <chrono>

#pragma once

using namespace std::chrono;

class Main
{
public:
	enum Answer
	{
		instant = 1,
		fast	= 2,
		normal	= 3,
		slow	= 4,

		smallMaze	= 1,
		mediumMaze	= 2,
		bigMaze		= 3,

		yes = 1,
		no	= 2
	};
};