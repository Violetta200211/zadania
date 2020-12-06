
#ifndef MYWINDOW_H_
#define MYWINDOW_H_
#include "Window.h"

class MyWindow: public Window{

protected:
	void setupGL();

public:
	MyWindow():Window(1000,800){
		 setupGL();
	}
	MyWindow(const MyWindow&) = delete;
	virtual ~MyWindow() = default;
	virtual void render();
};


#endif /* MYWINDOW_H_ */
