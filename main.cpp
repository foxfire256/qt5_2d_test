#include <QApplication>

#include "main_window.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
	//QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	//QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

	QApplication a(argc, argv);
	main_window w;
	w.show();

	return a.exec();
}
