#pragma once
#include <vector>
#include "Point.h"
#include <fstream>

using namespace std;

class CircleConvexHull
{
	vector<Point> cpoints;		// punctele de centru ale cercurilor in coordonate (X,y)
	vector<Point> chull;		// punctele de centru din acoperirea convexa a cercurilor
	static Point p0;
public:
	static Point getBottomMostPoint();
	size_t computeBottomMostPoint();
	vector<Point> convexHull();
	void readPointsFromFile(ifstream &f);
	Point getCentroid();
	int checkPointPosition(const Point &p);
	void printChull();
	CircleConvexHull() {};
	~CircleConvexHull() {};
	// friend functions
	friend int orientation(const Point &p1, const Point &p2, const Point &p3);

private:

};

