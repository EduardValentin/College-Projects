#include "Point.h"

double Point::getX() const
{
	return this->x;
}

double Point::getY() const
{
	return y;
}

void Point::setX(const double & x)
{
	this->x = x;
}

void Point::setY(const double & y)
{
	this->y = y;
}

bool Point::operator ==(const Point &a)
{
	return (a.x == this->x && a.y == this->y);

}
ostream& operator << (ostream& o, const Point &a)
{
	o << "(" << a.x << "," << a.y << ")  ";
	return o;
}
