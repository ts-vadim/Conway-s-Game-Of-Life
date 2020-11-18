// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include "cgui/Graphics.h"
#include "cinput/Input.h"
#include "GameOfLife.h"


int main()
{
	std::cout << "Press alt+enter, then enter";
	getchar();
	int longest = 0;
	int longest_cycle = 0;
	int cycle = 0;
	Graphics graphics;
	GameOfLife game(graphics.width, graphics.height);

	game.spawnChance = 0.7;
	
	game.deathChanceOld = 0.07;
	game.Restart();

	int i = 0;

	while (true)
	{

		i++;
		if (i > 5)
		{
			game.deathChance = rand() % 4 / 10.0;
			i = 0;
		}

		graphics.Clear();
		graphics.Draw(game);
		graphics.Text(0, 0, "Iteration: %d", game.iteration);
		graphics.Text(0, 1, "Longest: %d (%d)", longest, longest_cycle);
		graphics.Text(0, 2, "Cycle: %d", cycle);
		graphics.Text(0, 3, "deathChance: %f", game.deathChance);
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

		//Sleep(10);
	}

	graphics.Cursor(0, graphics.height - 4);
}
