/*
 * MyWindow.cc
 *
 *  Created on: 11 нояб. 2019 г.
 *      Author: Иван
 */

#include "MyWindow.h"




void MyWindow::render(){
	int h = 100;
	SDL_Rect Sky{0, 0, width(), height()/2};
	SDL_Rect Ground{0, height()/2, width(), height()/2};
	SDL_SetRenderDrawColor(_ren.get(), 6, 16, 128, 255);
	SDL_RenderFillRect(_ren.get(), &Sky);
	SDL_SetRenderDrawColor(_ren.get(), 32, 32, 32, 255);
	SDL_RenderFillRect(_ren.get(), &Ground);
	double d = width()/(2*tan(_player.fov()/2));
	double Dv = 0.;
	double Dh = 0.;
	for(int col=0 ;col < width(); col++){
		double rx = 0;
		double ry = 0;
		double dx = 0.;
		double dy = 0.;
		double beta = _player.fov()*(double(col)/double(width())-0.5);
		double gamma = _player.dir() + beta;
		if(cos(gamma) > 0) {

			dx = 1.;
			dy = tan(gamma);
			rx = floor(_player.x()) + 0.0001;
			ry = _player.y() - (_player.x() - rx)*dy;
			raycast(rx,ry,dx,dy);
			Dv = hypot(rx-_player.x(), ry - _player.y());
		} else if(cos(gamma) < 0) {
			dx = -1.;
			dy = tan(-gamma);
			rx = ceil(_player.x()) - 0.0001;
			ry = _player.y() - ( rx - _player.x())*dy;
			raycast(rx,ry,dx,dy);
			Dv = hypot(rx-_player.x(), ry - _player.y());
		} else {
			Dv = INFINITY;
		}
		if(sin(gamma) > 0) {
			dx = 1 /tan(gamma);
			dy = 1.;
			ry = floor(_player.y()) + 0.0001;
			rx = _player.x() - (_player.y()- ry)*dx;
			raycast(rx,ry,dx,dy);
			Dh = hypot(rx-_player.x(), ry - _player.y());

		} else if(sin(gamma) < 0) {
			dx = 1 /tan(-gamma);
			dy = -1.;
			ry = ceil(_player.y())-0.0001;
			rx = _player.x() - (ry - _player.y())*dx;
			raycast(rx,ry,dx,dy);
			Dh = hypot(rx-_player.x(), ry - _player.y());
		} else {
			Dh = INFINITY;
		}
			h = (d/cos(beta))/std::min(Dv,Dh);
		draw_col(col, h);

	}
}
//void MyWindow::handle_event(const SDL_Event& e){
//	if(e.type == SDL_KEYDOWN) {
//		if(e.key.keysym.scancode == SDL_SCANCODE_UP)
//			_player.walk_forward(0.05);
//		if(e.key.keysym.scancode == SDL_SCANCODE_DOWN)
//			_player.walk_backward(0.05);
//		if(e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
//			_player.strape_right(0.05);
//		if(e.key.keysym.scancode == SDL_SCANCODE_LEFT)
//			_player.strape_left(0.05);
//		if(e.key.keysym.scancode == SDL_SCANCODE_Z)
//			_player.turn_left(0.05);
//		if(e.key.keysym.scancode == SDL_SCANCODE_X)
//			_player.turn_right(0.05);
//
//	}
//
//}
void MyWindow::handle_keys(const Uint8* keys){
	if(keys[SDL_SCANCODE_RIGHT])
		_player.strape_right(0.05);
	if(keys[SDL_SCANCODE_LEFT])
		_player.strape_left(0.05);
	if(keys[SDL_SCANCODE_UP])
		_player.walk_forward(0.05);
	if(keys[SDL_SCANCODE_DOWN])
		_player.walk_backward(0.05);
	if(keys[SDL_SCANCODE_Z])
		_player.turn_left(0.05);
	if(keys[SDL_SCANCODE_X])
		_player.turn_right(0.05);
}
void MyWindow::raycast(double& rx, double& ry, double dx, double dy){
	do {
		rx += dx;
		ry += dy;
	} while (!_lab.is_wall(rx, ry));
}
void MyWindow::draw_col(int col, int h){
	SDL_SetRenderDrawColor(_ren.get(), 64, 16, 0, 255);
	int y1 = height()/2 - h/2, y2 = height()/2 + h/2;
	SDL_RenderDrawLine(_ren.get(), col, y1, col, y2);

}

