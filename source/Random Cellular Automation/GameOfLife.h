#pragma once

#include <time.h>
#include <random>
#include "cgui/Graphics.h"


class GameOfLife: public Drawable
{
public:
	int const& width = m_width;
	int const& height = m_height;
	int const& iteration = m_iteration;
	int const& aliveCount = m_aliveCount;
	bool const& ended = m_ended;
	float spawnChance = 0.4;
	float deathChance = 0.8;
	float deathChanceOld = 0.3;

	GameOfLife(int w, int h);
	~GameOfLife();

	void Restart();
	void Draw(Graphics& graphics);

private:
	int m_width = 40;
	int m_height = 20;
	int m_aliveCount = 0;
	int m_iteration = 0;
	bool m_ended = false;
	int restart_count = 0;
	FrameBuffer current_frame;
	FrameBuffer prev_frame;

	int nearCells(int x, int y);
};

