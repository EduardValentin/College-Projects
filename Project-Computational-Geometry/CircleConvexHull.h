#pragma once
#include <vector>
#include <list>
#include "Point.h"

using namespace std;

class CircleConvexHull
{
	vector<Point> cpoints;		// punctele de centru ale cercurilor in coordonate (X,y)
	vector<Point> chull;		// punctele de centru din acoperirea convexa a cercurilor
public:
	static Point p0;
	vector<Point> convexHull();
	CircleConvexHull() {};
	~CircleConvexHull() {};
	static double distanceFromP0(const Point &a);
	// friend functions
	friend int orientation(const Point &p1, const Point &p2, const Point &p3);

	// de adaugat functie de citire a punctelor, din stream initial
private:

};

Point CircleConvexHull::p0(0, 0);