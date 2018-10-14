#include "main_window.hpp"

#include <QHBoxLayout>

#include "gl_widget.hpp"
#include "gfx.hpp"

//------------------------------------------------------------------------------
main_window::main_window(QWidget *parent) : QMainWindow(parent)
{
	printf("Qt compile time version: %s\n", QT_VERSION_STR);
	printf("Qt run time version: %s\n", qVersion());

	main_widget = new QWidget(this);

	g = new gfx();
	glw = new gl_widget(g, this);

	main_layout = new QHBoxLayout(main_widget);
	main_layout->addWidget(glw);
	this->setCentralWidget(main_widget);
}

//------------------------------------------------------------------------------
main_window::~main_window()
{
	delete main_layout;
	delete glw;
	delete g;
	delete main_widget;
}
