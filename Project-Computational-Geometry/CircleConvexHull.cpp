#include "stdafx.h"
#include "CircleConvexHull.h"
#include <algorithm>
#include <stdlib.h>

using namespace std;

Point CircleConvexHull::p0 = Point(0, 0);

int orientation(const Point &a, const Point &b, const Point &c)
{
	/*
		Return value: 2 -> If left turn
		1 -> If right turn
		0 -> Colinear
	*/

	Point vab(b.getX() - a.getX(), b.getY() - a.getY());
	Point vbc(c.getX() - b.getX(), c.getY() - b.getY());

	double val = (vab.getX() * vbc.getY()) - (vbc.getX() * vab.getY());			// Cross product of the 2 vectors
	if (val == 0) 
		return 0;

	return ((val > 0) ? 2 : 1);
}

int compare(const void *a, const void *b)
{
	Point pa = *((Point *)a);
	Point pb = *((Point *)b);

	int o = orientation(CircleConvexHull::getBottomMostPoint(), pa, pb);

	if (!o)
	{
		return ((pa.distanceFrom(CircleConvexHull::getBottomMostPoint()) <= pb.distanceFrom(CircleConvexHull::getBottomMostPoint())) ? -1 : 1);
	}

	return ((o == 2) ? -1 : 1);

}

Point CircleConvexHull::getBottomMostPoint()
{
	return p0;
}

size_t CircleConvexHull::computeBottomMostPoint()
{
	// We find the bottom most point and assign it to p0
	Point pmin = cpoints[0];
	size_t mpos = 0;
	for (size_t i = 1; i < cpoints.size(); i++)
	{
		if (cpoints[i].getY() < pmin.getY())
		{
			mpos = i;
			pmin = cpoints[i];
		}
		else if ((cpoints[i].getY() == pmin.getY()) && (cpoints[i].getX() < pmin.getY()))
		{
			mpos = i;
			pmin = cpoints[i];
		}
	}
	p0 = pmin;
	return mpos;
}

vector<Point> CircleConvexHull::convexHull()
{
	vector<Point> result;
	Point *vaux;
	size_t size = cpoints.size();

	vaux = new Point[cpoints.size()];

	for (size_t i = 0; i < cpoints.size(); i++)
	{
		vaux[i] = cpoints[i];
	}

	size_t mpos = computeBottomMostPoint();

	// Swap
	Point aux = vaux[0];
	vaux[0] = vaux[mpos];
	vaux[mpos] = aux;


	// Now we sort the array of points according to polar angle with respect to p0
	qsort(vaux+ 1,size-1,sizeof(Point),compare);


	// Now we get rid of colinear points with p0 and chose the one that is at the largest distance from p0
	mpos = 1;
	for (size_t i = 1; i < size; i++)
	{
		while (i < size - 1 && orientation(p0, vaux[i], vaux[i + 1]) == 0)
			i++;

		vaux[mpos] = vaux[i];
		mpos++;							// Update the size
	}

	size = mpos;

	result.push_back(vaux[0]);
	result.push_back(vaux[1]);

	// Begin iteration
	for (size_t i = 2; i < size; i++)
	{
		while (orientation(result[result.size() - 2], result[result.size()-1], vaux[i]) != 2)
		{
			// Keep removing back while it forms right turn with v[i]
			result.pop_back();
		}
		result.push_back(vaux[i]);
	}
	return result;

}

void CircleConvexHull::readPointsFromFile(ifstream &f)
{
	f >> inputPoint;

	while (!f.eof())
	{
		Point p;
		f >> p;
		cpoints.push_back(p);
	}
}



