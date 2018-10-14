#include "gl_widget.hpp"

#include <QOpenGLFunctions>
#include <QPainter>

#include "gfx.hpp"
#include "fox/counter.hpp"

gl_widget::gl_widget(gfx *g, QWidget *parent) : QOpenGLWidget(parent)
{
	this->g = g;
	c = new fox::counter();
}

gl_widget::~gl_widget()
{
	delete c;
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
	g->paint(&painter, event, c->update());
	painter.end();
}
