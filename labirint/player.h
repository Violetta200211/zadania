#include "globals.h"
#include <functional>

class Player {

	protected:
		double _x{0}, _y{0}, _dir{0};
		std::function<bool(double,double)> _check{[](double,double) ->bool{return false;}};

	public:
		Player() {};
		Player(const Player&) = delete;
		double x() const{return _x;};
		double y() const{return _y;};
		double dir() const{return _dir;};
//		угол обзора 60 градусов
		static constexpr double fov() {return Pi/3;};
		void set(double x, double y) {_x=x; _y=y;};
		void turn_right(double a){ _dir+=a; while(_dir>Pi*2) _dir-=Pi*2;};
		void turn_left(double a){ _dir-=a; while(_dir<0) _dir+=Pi*2;};
		void walk_forward(double d){
			double n_x = _x + d*cos(_dir), n_y = _y + d*sin(_dir);
			if (_check(n_x, n_y)){ set(n_x, n_y);}
		}
		void strape_right(double d){
			double n_x = _x + d*cos(_dir + Pi/2), n_y = _y + d*sin(_dir + Pi/2);
			if (_check(n_x, n_y)){ set(n_x, n_y);}
		}
		void walk_backward(double d) {walk_forward(-d);}
		void strape_left(double d) {strape_right(-d);}
		void set_check(const std::function<bool(double,double)>& f){
			_check = f;
		}


};
