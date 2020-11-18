#include "GameOfLife.h"


GameOfLife::GameOfLife(int w, int h)
{
	m_width = w;
	m_height = h;
	frame.Create(m_width, m_height);
	current_frame.Create(m_width, m_height);
	prev_frame.Create(m_width, m_height);
}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::Restart()
{
	m_iteration = 0;
	m_ended = false;
	srand(restart_count);
	restart_count++;
	for (int y = 0; y < m_height; y++)
		for (int x = 0; x < m_width; x++)
			current_frame.SetChar(x, y, ((float)(rand() % 10) <= spawnChance * 10.0) ? '#' : ' ');
}

void GameOfLife::Draw(Graphics& graphics)
{
	m_aliveCount = 0;
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int cellsNear = nearCells(x, y);
			bool thisAlive = current_frame.GetChar(x, y) == '#';

			if (!thisAlive)
			{
				if (cellsNear == 3)
				{
					frame.SetChar(x, y, '#');
					m_aliveCount++;
				}
			}
			else
			{
				if (cellsNear < 2 || cellsNear > 3)
					frame.SetChar(x, y, ' ');
			}
		}
	}
	if (frame == current_frame || frame == prev_frame || m_aliveCount == 0)
		m_ended = true;
	current_frame.Copy(prev_frame);
	frame.Copy(current_frame);
	if (!m_ended)
		m_iteration++;
}

int GameOfLife::nearCells(int x, int y)
{
	int sum = 0;
	if (current_frame.GetChar(x - 1, y - 1) == '#')
		sum++;
	if (current_frame.GetChar(x, y - 1) == '#')
		sum++;
	if (current_frame.GetChar(x + 1, y - 1) == '#')
		sum++;
	if (current_frame.GetChar(x - 1, y) == '#')
		sum++;
	if (current_frame.GetChar(x + 1, y) == '#')
		sum++;
	if (current_frame.GetChar(x - 1, y + 1) == '#')
		sum++;
	if (current_frame.GetChar(x, y + 1) == '#')
		sum++;
	if (current_frame.GetChar(x + 1, y + 1) == '#')
		sum++;
	return sum;
}