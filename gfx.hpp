#ifndef GFX_HPP
#define GFX_HPP

#include <vector>
#include <array>
#include <random>

class QPainter;
class QPaintEvent;
class QImage;

class gfx
{
public:
	gfx(int w, int h);
	virtual ~gfx();
	void paint(QPainter *painter, QPaintEvent *event, float delta_t);

private:
	QImage *img1;

	int obj_count;
	/**
	 * @brief position {x, y, rot, scale}
	 */
	std::vector<std::array<float, 4>> pos;
	/**
	 * @brief velocity {x_vel, y_vel, rot_vel(degrees)}
	 */
	std::vector<std::array<float, 3>> vel;

	std::mt19937_64 generator;

	float scale_max;
	float scale_min;
};

#endif // GFX_HPP
