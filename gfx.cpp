#include "gfx.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QTransform>

gfx::gfx(int w, int h)
{
	img1 = new QImage(":/img/snowflake1.png");
	this->generator = std::mt19937_64(std::random_device{}());

	obj_count = 64;
	pos.resize(obj_count);
	vel.resize(obj_count);
	scale_max = 0.1f;
	scale_min = 0.02f;
	std::uniform_real_distribution<float> dv(16.0f, 32.0f);
	std::uniform_real_distribution<float> dr(4.0f, 16.0f);
	std::uniform_real_distribution<float> dx(0.0f, (float)w);
	std::uniform_real_distribution<float> dy(0.0f, (float)h);
	std::uniform_real_distribution<float> ds(scale_min, scale_max);
	for(auto &p : pos)
	{
		p[0] = dx(generator);
		p[1] = dy(generator);
		p[2] = 0.0f;
		p[3] = ds(generator);
	}
	for(auto &v : vel)
	{
		v[0] = dv(generator);
		v[1] = dv(generator);
		v[2] = dr(generator);
	}
}

gfx::~gfx()
{
	delete img1;
}

void gfx::paint(QPainter *painter, QPaintEvent *event, float delta_t)
{
	painter->fillRect(event->rect(), QBrush(QColor(0, 0, 0)));

	for(unsigned int i = 0; i < pos.size(); i++)
	{
		pos[i][0] += vel[i][0] * delta_t;
		pos[i][1] += vel[i][1] * delta_t;
		pos[i][2] += vel[i][2] * delta_t;

		// hacky but sorta works
		if(pos[i][0] > ((float)painter->window().width() + img1->width() * scale_max))
		{
			pos[i][0] -= ((float)painter->window().width() + img1->width() * scale_max);
		}
		if(pos[i][1] > ((float)painter->window().height() + img1->height() * scale_max))
		{
			pos[i][1] -= ((float)painter->window().height() + img1->height() * scale_max);
		}
	}

	for(auto &p : pos)
	{
		QTransform trans;

		trans.translate(p[0], p[1]);
		trans.rotate(p[2]);
		trans.scale(p[3], p[3]);

		painter->setTransform(trans);
		painter->drawImage(-img1->width() / 2.0f, -img1->height() / 2.0f, *img1);
		painter->resetTransform();
	}
}
