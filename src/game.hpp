#pragma once
#include <utility>
#include <vector>

using Position = std::pair<int, int>;
using Direction = Position;
class Game
{
	const static int WIDTH = 4;
	const static int HEIGHT = 4;
	const static int TILE_DISPLAY_SIZE = 3;
	const static int FOUR_RATIO = 10;
	const static int INITIAL_TILE_COUNT = WIDTH * HEIGHT / 8;

private:
	int board[HEIGHT][WIDTH];
	bool debug = false;

public:
	Game(bool debug)
	{
		this->debug = debug;
		for (int i = 0; i < INITIAL_TILE_COUNT; i++)
		{
			this->trySpawn();
		}
	}
	bool isGameOver();
	bool trySpawn();
	bool isInBounds(Position position);
	bool isInBounds(int x, int y);
	void move(Direction direction);
	bool compress(Direction direction);
	bool merge(Direction direction);
	std::vector<Position> getVacant();
	void set(Position position, int value);
	Direction read();
	void print();
	void print(bool debug);
};