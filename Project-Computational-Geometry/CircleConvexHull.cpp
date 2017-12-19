#include "CircleConvexHull.h"
#include <algorithm>

using namespace std;

double CircleConvexHull::distanceFromP0(const Point &a)
{
	return ((p0.getX() - a.getX())*(p0.getX() - a.getX()) + (p0.getY() - a.getY())*(p0.getY() - a.getY()));
}

int orientation(const Point &a, const Point &b, const Point &c)
{
	/*
		Return value: 2 -> If left turn
		1 -> If right turn
		0 -> Colinear
	*/

	Point vab(b.getX() - a.getX(), b.getY() - a.getY());
	Point vbc(c.getX() - b.getX(), c.getY() - b.getY());

	double val = vab.getX() * vbc.getY() - vbc.getY() * vab.getY();			// Cross product of the 2 vectors
	if (val == 0) return 0;

	return ((val > 0) ? 2 : 1);

	return 0;
}

int compare(const Point a, const Point b)
{
	int o = orientation(CircleConvexHull::p0, a, b);

	if (!o)
	{
		return ((CircleConvexHull::distanceFromP0(a) > CircleConvexHull::distanceFromP0(b)) ? 1 : 0);
	}

	return ((o == 2) ? 0 : 1);

}

vector<Point> CircleConvexHull::convexHull()
{
	vector<Point> result;
	vector<Point> vaux;
	// We find the bottom most point and assign it to p0
	Point pmin = vaux[0];
	size_t mpos = 0;
	for (size_t i = 1; i < vaux.size(); i++)
	{
		if (vaux[i].getY() < pmin.getY())
		{
			mpos = i;
			pmin = vaux[i];
		}
		else if ((vaux[i].getY() == pmin.getY()) && (vaux[i].getX() < pmin.getY()))
		{
			mpos = i;
			pmin = vaux[i];
		}
	}

	// Swap
	Point aux = vaux[0];
	vaux[0] = vaux[mpos];
	vaux[mpos] = aux;

	p0 = pmin;

	// Now we sort the array of points according to polar angle with respect to p0
	sort(vaux.begin() + 1, vaux.end(), compare);


	// Now we get rid of colinear points with p0 and chose the one that is at the largest distance from p0
	mpos = 1;
	for (size_t i = 1; i < vaux.size(); i++)
	{
		while (i < vaux.size() - 1 && orientation(p0, vaux[i], vaux[i + 1]) == 0)
			i++;

		vaux[mpos] = vaux[i];
		mpos++;							// Update the size
	}

	vaux.resize(mpos);

	result.push_back(vaux[0]);
	result.push_back(vaux[1]);

	// Begin iteration
	for (size_t i = 2; i < vaux.size(); i++)
	{
		while (orientation(result[result.size() - 2], result[result.size()], vaux[i]) != 2)
		{
			// Keep removing back while it forms right turn with v[i]
			result.pop_back();
		}
		result.push_back(vaux[i]);
	}
	return result;

}



