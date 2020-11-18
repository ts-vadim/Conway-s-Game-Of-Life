// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include "cgui/Graphics.h"
#include "GameOfLife.h"


int main()
{
	int longest = 0;
	int longest_cycle = 0;
	int cycle = 0;
	Graphics graphics;
	GameOfLife game(graphics.width, graphics.height);
	game.spawnChance = 0.5;
	game.Restart();

	while (true)
	{
		graphics.Clear();
		graphics.Draw(game);
		graphics.Text(0, 0, "Iteration: %d", game.iteration);
		graphics.Text(0, 1, "Longest: %d (%d)", longest, longest_cycle);
		graphics.Text(0, 2, "Cycle: %d", cycle);
		graphics.Display();

		if (longest < game.iteration)
		{
			longest = game.iteration;
			longest_cycle = cycle;
		}
		
		if (game.ended || GetAsyncKeyState(VK_RETURN) == -32767)
		{
			game.Restart();
			cycle++;
		}
	}

	graphics.Cursor(0, graphics.height - 4);
}
