/*
 * Labyrinth.cc
 *
 *  Created on: 6 нояб. 2019 г.
 *      Author: prepod
 */

#include "Labyrinth.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>

Labyrinth::Labyrinth(const char * filename)
{
	std::fstream f;
	f.open(filename, std::ios::in);
	if (!f.good())
		throw std::runtime_error(
				std::string("Labyrinth::Labyrinth(): "
						"Не могу открыть файл ") +
				std::string(filename));
	std::string line;
	std::getline(f, line);
	std::stringstream ss(line);
	ss >> _w >> _h >> _startx >> _starty;
	_map.resize(_w * _h);
	for (int i = 0; i < _h; i++) {
		std::getline(f, line);
		for (int j = 0; j < _w; j++) {
			_map[i*_w + j] = line[j];
		}
	}
}

bool Labyrinth::is_wall(int x, int y)
{
	if (x < 0 || y < 0 || x >= _w || y >= _h)
		return true;
	if (_map[y * _w + x] == '#') return true;
	return false;
}

bool Labyrinth::is_space(int x, int y)
{
	if (x < 0 || y < 0 || x >= _w || y >= _h)
		return true;
	if (_map[y * _w + x] == ' ') return true;
	return false;
}

bool Labyrinth::is_wall(double x, double y)
{
	return is_wall( int(floor(x)), int(floor(y)) );
}

bool Labyrinth::is_space(double x, double y)
{
	return is_space( int(floor(x)), int(floor(y)) );
}
