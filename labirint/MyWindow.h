/*
 * MyWindow.h
 *
 *  Created on: 11 нояб. 2019 г.
 *      Author: Иван
 */

#ifndef MYWINDOW_H_
#define MYWINDOW_H_
#include "Window.h"
#include "Labyrinth.h"
#include "Player.h"

class MyWindow: public Window{
protected:
	Labyrinth _lab{"level.txt"};
	Player _player;
	void draw_col(int col, int h);
	void raycast(double& rx, double& ry, double dx, double dy);
public:
	MyWindow():Window(800,600){
		_player.set(_lab.startx(),_lab.starty());
		_player.set_check([&](double x, double y)-> bool{return _lab.is_space(x, y);});

	}
	virtual void render();
//	virtual void handle_event(const SDL_Event& e);
	virtual void handle_keys(const Uint8* keys);
};




#endif /* MYWINDOW_H_ */
