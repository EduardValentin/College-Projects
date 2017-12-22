#pragma once
#include <iostream>
#include "stdafx.h"


using namespace std;

class Point
{
	double x, y;
public:
	double getX() const;
	double getY() const;
	void setX(const double &x);
	void setY(const double &y);
	Point() :x(0), y(0) {};
	Point(const double &xx, const double &yy) :x(xx), y(yy) {}
	~Point() {};
	bool operator ==(const Point &a);
	double distanceFrom(const Point &a) const;
	friend ostream& operator << (ostream& o, const Point &a);
	friend istream& operator >> (istream& i, Point &a);


	
private:

};
