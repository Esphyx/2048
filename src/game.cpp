#include <iostream>
#include <math.h>
#include <random>
#include <algorithm>
#include <cctype>
#include "game.hpp"

std::mt19937 rng((std::random_device())());

bool Game::trySpawn()
{
	std::vector<Position> vacant = this->getVacant();
	if (vacant.size() <= 0)
	{
		return false;
	}
	int randomIndex = std::uniform_int_distribution(0, (int)vacant.size() - 1)(rng);
	Position pos = vacant.at(randomIndex);
	set(pos, std::uniform_int_distribution(0, this->FOUR_RATIO)(rng) == 0 ? 2 : 1);
	return true;
}

bool Game::isGameOver()
{
	if (Game::getVacant().size() > 0)
		return false;
	for (int y = 0; y < this->HEIGHT - 1; y++)
		for (int x = 0; x < this->WIDTH; x++)
			if (this->board[y][x] == this->board[y + 1][x])
				return false;
	for (int y = 0; y < this->HEIGHT; y++)
		for (int x = 0; x < this->WIDTH - 1; x++)
			if (this->board[y][x] == this->board[y][x + 1])
				return false;
	return true;
}

bool Game::isInBounds(Position position)
{
	return Game::isInBounds(position.second, position.first);
}
bool Game::isInBounds(int x, int y)
{
	return y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH;
}

void Game::move(Direction direction)
{
	if (this->compress(direction) | this->merge(direction) | this->compress(direction))
	{
		this->trySpawn();
	}
}
bool Game::compress(Direction direction)
{
	bool change = false;
	int dy = direction.first;
	int dx = direction.second;
	for (int i = 0; i < this->HEIGHT; i++)
	{
		for (int j = 0; j < this->WIDTH; j++)
		{
			int y = dy == 1 ? this->HEIGHT - i - 1 : i;
			int x = dx == 1 ? this->WIDTH - j - 1 : j;
			if (this->board[y][x] == 0)
				continue;

			while (this->isInBounds(x + dx, y + dy))
			{
				if (this->board[y + dy][x + dx] != 0)
					break;

				change = true;
				this->board[y + dy][x + dx] = this->board[y][x];
				this->board[y][x] = 0;
				x += dx;
				y += dy;
			}
		}
	}
	return change;
}
bool Game::merge(Direction direction)
{
	bool change = false;
	int dy = direction.first;
	int dx = direction.second;
	for (int i = 0; i < this->HEIGHT - std::abs(dy); i++)
	{
		for (int j = 0; j < this->WIDTH - std::abs(dx); j++)
		{
			int y = dy == 1 ? this->HEIGHT - i - 1 : i;
			int x = dx == 1 ? this->WIDTH - j - 1 : j;
			if (this->board[y][x] == 0)
				continue;
			if (this->board[y][x] == this->board[y - dy][x - dx])
			{
				change = true;
				this->board[y][x]++;
				this->board[y - dy][x - dx] = 0;
			}
		}
	}
	return change;
}

std::vector<Position> Game::getVacant()
{
	std::vector<Position> positions;
	for (int y = 0; y < this->HEIGHT; y++)
		for (int x = 0; x < this->WIDTH; x++)
			if (this->board[y][x] == 0)
				positions.push_back(std::make_pair(y, x));
	return positions;
}
void Game::set(Position position, int value)
{
	this->board[position.first][position.second] = value;
}

void clearTerminal()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

Direction Game::read()
{
	clearTerminal();
	this->print();
	std::string input;
	std::cin >> input;
	Direction direction = std::make_pair(0, 0);
	if (input == "w")
		direction = std::make_pair(-1, 0);
	else if (input == "a")
		direction = std::make_pair(0, -1);
	else if (input == "s")
		direction = std::make_pair(1, 0);
	else if (input == "d")
		direction = std::make_pair(0, 1);
	else
		direction = read();
	return direction;
}

void Game::print()
{

	std::string seperator = "+";
	for (int i = 0; i < this->WIDTH; i++)
	{
		for (int j = 0; j < 3 * this->TILE_DISPLAY_SIZE; j++)
			seperator += "-";
		seperator += "+";
	}
	if (this->debug)
	{
		std::cout << "+";
		for (int i = 0; i < this->WIDTH; i++)
		{
			for (int j = 0; j < 3 * this->TILE_DISPLAY_SIZE; j++)
				std::cout << (j == (3 * this->TILE_DISPLAY_SIZE) / 2 /*&& this->debug*/ ? std::to_string(i) : "-");
			std::cout << "+";
		}
	}
	else
		std::cout << seperator;
	std::cout << std::endl;
	for (int y = 0; y < this->HEIGHT; y++)
	{
		for (int i = 0; i < this->TILE_DISPLAY_SIZE; i++)
		{
			bool middle = i == (this->TILE_DISPLAY_SIZE - 1) / 2;
			std::string line = middle && this->debug ? std::string(1, std::to_string(y).back()) : "|";
			for (int x = 0; x < this->WIDTH; x++)
			{
				if (!middle || this->board[y][x] == 0)
				{
					line.insert(line.end(), 3 * this->TILE_DISPLAY_SIZE, ' ');
				}
				else
				{
					std::string tile = std::to_string(1 << this->board[y][x]);
					float padAmount = (3 * this->TILE_DISPLAY_SIZE - tile.size()) / 2.0;

					tile.insert(tile.begin(), floor(padAmount), ' ');
					tile.insert(tile.end(), ceil(padAmount), ' ');
					line += tile;
				}
				line += "|";
			}
			std::cout << line << std::endl;
		}
		std::cout << seperator << std::endl;
	}
}