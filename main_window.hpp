#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QtWidgets/QMainWindow>

class gl_widget;
class gfx;
class keyboard_handler;

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QWidget;
class QTimer;
class QPushButton;

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = 0);
	~main_window();

public slots:
	void do_quit();

private:
	gl_widget *glw;
	gfx *g;
	keyboard_handler *kh;

	QTimer *gfx_timer;
	QWidget *main_widget;
	QHBoxLayout *main_layout;
	QVBoxLayout *left_layout, *right_layout;
	QPushButton *quit_pb;
};

#endif
