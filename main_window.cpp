#include "main_window.hpp"

#include "gl_widget.hpp"


//------------------------------------------------------------------------------
main_window::main_window(QWidget *parent) : QMainWindow(parent)
{
	glw = new gl_widget(this);
}

//------------------------------------------------------------------------------
main_window::~main_window()
{
	delete glw;
}
