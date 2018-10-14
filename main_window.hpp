#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QtWidgets/QMainWindow>

class gl_widget;

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = 0);
	~main_window();

public slots:

private:
	gl_widget *glw;
};

#endif
