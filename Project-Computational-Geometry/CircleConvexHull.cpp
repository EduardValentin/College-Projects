#include "CircleConvexHull.h"
#include <algorithm>
#include <stdlib.h>
#include <math.h>

using namespace std;

Point CircleConvexHull::p0 = Point(0, 0);

double vectorMagnitude(Point v)
{
    // returns the magnitude of the vector (x,y) determined by the point v.
    return sqrt(v.getX()*v.getX() + v.getY()*v.getY());
}
double disttancePointLine(double a,double b,double c,Point p)
{
    // returns the distance between point p and line ax + by + c=0
    return fabs((a*p.getX() + b*p.getY() + c) / vectorMagnitude(Point(a,b)));
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
		else if ((cpoints[i].getY() == pmin.getY()) && (cpoints[i].getX() < pmin.getX()))
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
	Point *vaux;
	size_t ssize = cpoints.size();

	vaux = new Point[ssize];

	for (size_t i = 0; i < ssize; i++)
	{
		vaux[i] = cpoints[i];
	}

	size_t mpos = computeBottomMostPoint();     // return position of bottom most point

	// Swap
	Point aux = vaux[0];
	vaux[0] = vaux[mpos];
	vaux[mpos] = aux;


	// Now we sort the array of points according to polar angle with respect to p0
	qsort(vaux+ 1,ssize-1,sizeof(Point),compare);


	// Now we get rid of colinear points with p0 and chose the one that is at the largest distance from p0
	mpos = 1;
	for (size_t i = 1; i < ssize; i++)
	{
		while (i < ssize - 1 && orientation(p0, vaux[i], vaux[i + 1]) == 0)
			i++;

		vaux[mpos] = vaux[i];
		mpos++;							// Update the size
	}

	ssize = mpos;

	chull.push_back(vaux[0]);
	chull.push_back(vaux[1]);

	// Begin iteration
	for (size_t i = 2; i < ssize; i++)
	{
		while (orientation(chull[chull.size() - 2], chull[chull.size()-1], vaux[i]) != 2)
		{
			// Keep removing back while it forms right turn with v[i]
			chull.pop_back();
		}
		chull.push_back(vaux[i]);
	}

	return chull;

}
Point CircleConvexHull::getCentroid()
{
    Point centroid = Point(0,0);
    double signedArea = 0.0;
    double x0 = 0.0; // Current vertex X
    double y0 = 0.0; // Current vertex Y
    double x1 = 0.0; // Next vertex X
    double y1 = 0.0; // Next vertex Y
    double a = 0.0;  // Partial signed area
    size_t i;
    for (i=0; i<chull.size()-1;i++)
    {
        x0 = chull[i].getX();
        y0 = chull[i].getY();
        x1 = chull[i+1].getX();
        y1 = chull[i+1].getY();
        a = x0*y1 - x1*y0;
        signedArea += a;
        centroid.setX(centroid.getX() + (x0 + x1)*a);
        centroid.setY(centroid.getY() + (y0 + y1)*a);
    }

    x0 = chull[i].getX();
    y0 = chull[i].getY();
    x1 = chull[0].getX();
    y1 = chull[0].getY();
    a = x0*y1 - x1*y0;
    signedArea += a;
    centroid.setX(centroid.getX() + (x0 + x1)*a);
    centroid.setY(centroid.getY() + (y0 + y1)*a);

    signedArea *= 0.5;
    centroid.setX(centroid.getX() /(6.0*signedArea));
    centroid.setY(centroid.getY() /(6.0*signedArea));

    return centroid;
}

int CircleConvexHull::checkPointPosition(const Point &p)
{
    if(!chull.empty())
    {
        /*
            Return values => 1, p is inside the convex hull of circles
                          => 2, p is outside the convex hull of circles
                          => 0, p is on the convex hull of circles
        */

        // mai intai se fixeaza un punct in centrul poligonului
        Point O = getCentroid();
        if(O == p)
        {
            return 1;
        }

        // binary search on points in convex hull
        // cautarea se face intre primele n-1 elemente pt ca v-m face testul intre punctul i si i+1

        int mij,left = 0,right = -2 + chull.size();

        while(left <= right)
        {
            mij = (left+right)/2;
            //cout << "mij:" <<chull[mij] << "/nmij+1:" << chull[mij+1];
            //cout << "orientation(O,chull[mij],p)" << orientation(O,chull[mij],p) << endl;
            //cout << "orientation(O,chull[mij+1],p)" << orientation(O,chull[mij+1],p) << endl;
            if(chull[mij] == p || chull[mij+1] == p)
            {
                return 1;
            }
            else if(orientation(O,chull[mij+1],p) == 0 || orientation(O,chull[mij],p) == 0)
            {
                // points O,p,chull[mij or mij+1] are colinear
                // we need to check now the position o p with respect to segment chull[mij],chull[mij+]
                if(orientation(chull[mij],chull[mij+1],p) == 2)
                {
                    // it is inside
                    return 1;
                }
                else
                {
                    // it is outside, we need to check distance from p to line determined by the 2 points on chull
                    double a,b,c; // a = coeficientul lui x, c= termenul liber, b = coeficientul lui y, este -1 (vezi formula)

                    double slope;
                    double dx = chull[mij+1].getX()-chull[mij].getX();
                    double dy = chull[mij+1].getY()-chull[mij].getY();

                    if(dx == 0)
                    {
                        // special case, the equation is x = chull[mij].x
                        a = chull[mij].getX();
                        b = 0;
                        c = -a;
                    }
                    else if(dy == 0)
                    {
                        // special case, the equation is x = chull[mij].y
                        a = chull[mij].getY();
                        b = 0;
                        c = -a;
                    }
                    else
                    {
                        slope = dy / dx;
                        // we calculate the equation of the line determined by chull[mij] and chull[mij+1] using the point slope form formul
                        a = slope;
                        b = -1;
                        c = slope * chull[mij].getX() + chull[mij].getY();
                    }
                    double dist = disttancePointLine(a,b,c,p);
                    if(dist < 1)
                        return 1;
                    else if(dist > 1)
                        return 2;
                    else
                        return 0;
                }
            }
            else if(orientation(O,chull[mij],p) == 2 && orientation(O,chull[mij+1],p) == 1)
            {
                int o = orientation(chull[mij],p,chull[mij+1]);
                // we found it
                if(o == 1 || o == 0)
                {
                    // it is inside the convex hull of centers, so it is inside the convex hull of circles
                    return 1;
                }
                else if(o == 2)
                {
                    // it is outside, we need to check distance from p to line determined by the 2 points on chull
                    double a,b,c; // a = coeficientul lui x, c= termenul liber, b = coeficientul lui y, este -1 (vezi formula)

                    double slope;
                    double dx = chull[mij+1].getX()-chull[mij].getX();
                    double dy = chull[mij+1].getY()-chull[mij].getY();

                    if(dx == 0)
                    {
                        // special case, the equation is x = chull[mij].x
                        a = chull[mij].getX();
                        b = 0;
                        c = -a;
                    }
                    else if(dy == 0)
                    {
                        // special case, the equation is x = chull[mij].y
                        b = chull[mij].getY();
                        a = 0;
                        c = -a;
                    }
                    else
                    {
                        slope = dy / dx;
                        // we calculate the equation of the line determined by chull[mij] and chull[mij+1] using the point slope form formul
                        a = slope;
                        b = -1;
                        c = slope * chull[mij].getX() + chull[mij].getY();
                    }
                    double dist = disttancePointLine(a,b,c,p);
                    if(dist < 1)
                        return 1;
                    else if(dist > 1)
                        return 2;
                    else
                        return 0;
                }
            }
            else if(orientation(O,chull[mij],p) == 1)
            {
                // punctul e mai la dreapta
                right = mij-1;
            } else if(orientation(O,chull[mij+1],p) == 2)
            {
                // punctul e mai la stanga
                left = mij+1;
            }
        }

    }
    else
    {
        cout << "Nothing in convex hull, run convexHull() method first";
        return -1;
    }
}
void CircleConvexHull::printChull()
{
    for(size_t i = 0;i<chull.size();i++)
        cout << chull[i] << endl;
}
void CircleConvexHull::readPointsFromFile(ifstream &f)
{
	while (!f.eof())
	{
		Point p;
		f >> p;
		cpoints.push_back(p);
	}
}



