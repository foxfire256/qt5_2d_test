#include "gfx.hpp"

#include <QPainter>
#include <QPaintEvent>

gfx::gfx()
{

}

void gfx::paint(QPainter *painter, QPaintEvent *event, float delta_t)
{
	painter->fillRect(event->rect(), QBrush(QColor(64, 32, 64)));
}
