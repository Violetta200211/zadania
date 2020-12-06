/*
 * Labyrinth.h
 *
 *  Created on: 6 но€б. 2019 г.
 *      Author: prepod
 */

#ifndef LABYRINTH_H_
#define LABYRINTH_H_

#include <vector>
#include <cstdint>

class Labyrinth
{
protected:
	std::vector<char> _map;
	int _w { 0 }, _h { 0 };
	double _startx { 1.5 }, _starty { 1.5 };
public:
	Labyrinth(const char * filename);

	int w() const { return _w; }
	int h() const { return _h; }
	double startx() const { return _startx; }
	double starty() const { return _starty; }

	bool is_wall(int x, int y);
	bool is_space(int x, int y);

	bool is_wall(double x, double y);
	bool is_space(double x, double y);
};



#endif /* LABYRINTH_H_ */
