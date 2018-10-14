#include "gl_widget.hpp"

#include <QOpenGLFunctions>
#include <QPainter>

gl_widget::gl_widget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void gl_widget::initializeGL()
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

	printf("GL_VENDOR: %s\n", f->glGetString(GL_VENDOR));
	printf("GL_RENDERER: %s\n", f->glGetString(GL_RENDERER));
	printf("GL_VERSION: %s\n", f->glGetString(GL_VERSION));
	printf("GL_SHADING_LANGUAGE_VERSION: %s\n",
		f->glGetString(GL_SHADING_LANGUAGE_VERSION));
	fflush(stdout);
}

void gl_widget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	//gfx->paint(&painter, event, elapsed);
	painter.end();
}
