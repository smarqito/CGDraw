#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
	z = 0;

}

Point::Point(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

void Point::setPoint(Point p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

void Point::setPoint(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;

}
