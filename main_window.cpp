#include "main_window.hpp"

#include <QHBoxLayout>
#include <QTimer>

#include "gl_widget.hpp"
#include "gfx.hpp"
#include "keyboard_handler.hpp"

//------------------------------------------------------------------------------
main_window::main_window(QWidget *parent) : QMainWindow(parent)
{
	printf("Qt compile time version: %s\n", QT_VERSION_STR);
	printf("Qt run time version: %s\n", qVersion());

	int w = 640;
	int h = 640;
	main_widget = new QWidget(this);

	g = new gfx(w, h);
	glw = new gl_widget(g, this);

	main_layout = new QHBoxLayout(main_widget);
	main_layout->addWidget(glw);
	this->setCentralWidget(main_widget);
	this->resize(w, h);

	gfx_timer = new QTimer(this);
	connect(gfx_timer, SIGNAL(timeout()), glw, SLOT(update()));
	// a value of 0 here makes this run all the time when the message queue
	// is clear
	gfx_timer->start(1 / 60.0 * 1000); // time in ms

	kh = new keyboard_handler(this);

	// just this seems to be sufficient to grab key presses
	this->installEventFilter(kh);
	//main_widget->installEventFilter(kh);
	//glw->installEventFilter(kh);
}

//------------------------------------------------------------------------------
main_window::~main_window()
{
	delete main_layout;
	delete glw;
	delete g;
	delete main_widget;
}

