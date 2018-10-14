#include "gfx.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QImage>

gfx::gfx()
{
	img1 = new QImage(":/img/snowflake1.png");
}

gfx::~gfx()
{
	delete img1;
}

void gfx::paint(QPainter *painter, QPaintEvent *event, float delta_t)
{
	painter->fillRect(event->rect(), QBrush(QColor(0, 0, 0)));

	painter->drawImage(5, 5, *img1);
}
