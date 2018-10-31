#include "main_window.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
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

	QSizePolicy right_size_policy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	int right_width = 96;

	main_widget = new QWidget(this);

	g = new gfx(w, h);
	glw = new gl_widget(g, this);

	quit_pb = new QPushButton("Quit", this);
	quit_pb->setSizePolicy(right_size_policy);
	quit_pb->setMaximumWidth(right_width);
	connect(quit_pb, SIGNAL(pressed()), this, SLOT(do_quit()));

	main_layout = new QHBoxLayout(main_widget);
	left_layout = new QVBoxLayout();
	right_layout = new QVBoxLayout();
	main_layout->addLayout(left_layout);
	main_layout->addLayout(right_layout);
	left_layout->addWidget(glw);
	right_layout->addStretch();
	right_layout->addWidget(quit_pb);

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
	// order matters with these layouts
	delete left_layout;
	delete right_layout;
	delete main_layout;

	delete quit_pb;
	delete glw;
	delete g;
	delete main_widget;
}

//------------------------------------------------------------------------------
void main_window::do_quit()
{
	this->close();
}

