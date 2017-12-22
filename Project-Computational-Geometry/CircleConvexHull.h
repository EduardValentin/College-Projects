#pragma once
#include "stdafx.h"
#include <vector>
#include <list>
#include "Point.h"
#include <fstream>

using namespace std;

class CircleConvexHull
{
	vector<Point> cpoints;		// punctele de centru ale cercurilor in coordonate (X,y)
	vector<Point> chull;		// punctele de centru din acoperirea convexa a cercurilor
	Point inputPoint;
	static Point p0;
public:
	static Point getBottomMostPoint();
	size_t computeBottomMostPoint();
	vector<Point> convexHull();
	void readPointsFromFile(ifstream &f);
	CircleConvexHull() {};
	~CircleConvexHull() {};
	// friend functions
	friend int orientation(const Point &p1, const Point &p2, const Point &p3);
	
private:

};

