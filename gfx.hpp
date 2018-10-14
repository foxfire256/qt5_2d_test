#ifndef GFX_HPP
#define GFX_HPP

class QPainter;
class QPaintEvent;
class QImage;

class gfx
{
public:
	gfx();
	virtual ~gfx();
	void paint(QPainter *painter, QPaintEvent *event, float delta_t);

private:
	QImage *img1;
};

#endif // GFX_HPP
