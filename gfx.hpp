#ifndef GFX_HPP
#define GFX_HPP

class QPainter;
class QPaintEvent;

class gfx
{
public:
	gfx();
	void paint(QPainter *painter, QPaintEvent *event, float delta_t);
};

#endif // GFX_HPP
