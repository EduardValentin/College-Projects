#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

struct Point {
	double x, y;
	Point() : x(0),y(0){}
	Point(double xx, double yy) : x(xx), y(yy) {}
	bool operator==(const Point b)
	{
		return (this->x == b.x && this->y == b.y) ? true : false;
	}
};

int orientation(const Point a, const Point b, const Point c)
{
	/*
	Return value: 2 -> If left turn
	1 -> If right turn
	0 -> Colinear
	*/

	Point vab(b.x - a.x, b.y - a.y);
	Point vbc(c.x - b.x, c.y - b.y);

	double val = vab.x * vbc.y - vbc.x * vab.y;			// Cross product of the 2 vectors
	if (val == 0) return val;

	return ((val > 0) ? 2 : 1);

}


double getScalarProduct(Point a2, Point a1, Point a3) {
	double scalarProduct;
	double t1 = (a2.x - a1.x) * (a3.x - a1.x);
	double t2 = (a2.y - a1.y) * (a3.y - a1.y);
	scalarProduct = t1 + t2;
	return scalarProduct;
}

double getNorma(Point a2, Point a1, Point a3) {
	double norma;
	double t1x = (a2.x - a1.x);
	double t1y = (a2.y - a1.y);
	double t2x = (a3.x - a1.x);
	double t2y = (a3.y - a1.y), n1, n2;

	n1 = sqrt(pow(t1x, 2) + pow(t1y, 2));
	n2 = sqrt(pow(t2x, 2) + pow(t2y, 2));
	norma = n1 * n2;
	return norma;
}

double getCos(Point a2, Point a1, Point a3) {
	double product = getScalarProduct(a2, a1, a3), norma = getNorma(a2, a1, a3), cos;
	cos = product / norma;
	return cos;
}

double getDistance(Point a1, Point a2) {
	return sqrt(pow(a1.x - a2.x, 2) + pow(a1.y - a2.y, 2));
}

void checkA(Point a1, Point a2, Point a3, Point a4) {

	double cos_a1, cos_a4;

	cos_a1 = getCos(a2, a1, a3);
	cos_a4 = getCos(a2, a4, a3);

	double angle1 = acos(cos_a1) * 180.0 / PI, angle4 = acos(cos_a4) * 180.0 / PI;

	//cout << acos(getCos(Point(0,10),Point(0,0),Point(10,0))) * 180.0 / PI;

	cout << angle4 << " " << angle1;

	if (fabs(angle1 + angle4 - 180) < 0.01) {
		cout << "A4 este pe cercul circumscris triunghiului format de A1, A2, A3" << '\n';
	}
	else if (fabs(angle1 + angle4) > 180) {
		cout << "A4 apartine interiul cercului circumscris triunghiului format de A1, A2, A3" << '\n';
	}
	else {
		cout << "A4 nu apartine cercului circumscris triunghiului format de A1, A2, A3" << '\n';

	}
}

void checkB(Point a1, Point a2, Point a3, Point a4) {
	double d12 = getDistance(a1, a2), d34 = getDistance(a3, a4), d23 = getDistance(a2, a3), d14 = getDistance(a1, a4);
	if (d12 + d34 == d23 + d14) {
		cout << "Patrulaterul A1A2A3A4 este circumscriptibil" << '\n';
	}
	else {
		cout << "Patrulaterul A1A2A3A4 nu este circumscriptibil" << '\n';
	}
}

void readPoints(Point &a1, Point &a2, Point &a3, Point &a4) {
	cout << "a1.x = ";
	cin >> a1.x;
	cout << "a1.y = ";
	cin >> a1.y;
	cout << '\n';
	cout << "a2.x = ";
	cin >> a2.x;
	cout << "a2.y = ";
	cin >> a2.y;
	cout << '\n';
	cout << "a3.x = ";
	cin >> a3.x;
	cout << "a3.y = ";
	cin >> a3.y;
	cout << '\n';
	cout << "a4.x = ";
	cin >> a4.x;
	cout << "a4.y = ";
	cin >> a4.y;
	cout << '\n';
}

int main()
{
	Point a1, a2, a3, a4;

	readPoints(a1, a2, a3, a4);

	if (orientation(a1, a2, a3) != orientation(a1, a2, a4))
	{
		checkA(a3, a2, a1, a4);			// Verific daca a1,a2,a3 formeaza viraj diferit de a1,a2,a4 , in acest caz a1,a3,a2 este unghiul complementar lui a1,a4,a2
		checkB(a3, a2, a4, a1);

	}
	if (orientation(a1, a3, a2) != orientation(a1, a3, a4))
	{
		checkA(a2, a1, a3, a4);				// La fel 
		checkB(a2, a3, a4, a1);

	}
	if (orientation(a2, a3, a1) != orientation(a2, a3, a4))
	{
		checkA(a1, a2, a3, a4);				// La fel 
		checkB(a1, a2, a4, a3);
	}
	return 0;
}
