#include "pch.h"
#include <iostream>
#include "cPolygon.h"
using namespace std;

const int MAX_VER = 50;
#define Xgreater(a, b) (a > b ? a : b)
#define Xless(a, b) (a < b ? a : b)

cPoint cPolygon::verDefault[] = { cPoint(100, 100), cPoint(100, 200), cPoint(250,200) };

void cPolygon::setVertices(int num, cPoint* P)
{
	if (P == NULL)
	{
		vertices = new cPoint[numVer = num];
		memcpy(vertices, verDefault, sizeof(cPoint) * num);
	}
	else
	{
		vertices = new cPoint[numVer = num];
		memcpy(vertices, P, sizeof(cPoint) * num);
	}
}

cPoint cPolygon::getCenter() const
{
	double x = 0, y = 0;
	for (int i = 0; i < numVer; i++)
	{
		x += vertices[i].getX();
		y += vertices[i].getY();
	}
	return cPoint(x / numVer, y / numVer);
}


bool cPolygon::isPointInside(cPoint P) const
{
	int flag = 0;
	double xIntersect;
	cPoint P1, P2;
	for (int i = 0; i < numVer; i++)
	{
		P1 = vertices[i];
		P2 = vertices[(i + 1) % numVer];
		if (P.getY() > Xless(P1.getY(), P2.getY()) && P.getY() <= Xgreater(P1.getY(), P2.getY()))
			if (P.getX() <= Xgreater(P1.getX(), P2.getX()))
				if (P1.getY() != P2.getY())
				{
					xIntersect = (P.getY() - P1.getY()) * (P2.getX() - P1.getX()) / (P2.getY() - P1.getY()) + P1.getX();
					if (P1.getX() == P2.getX() || P.getX() < xIntersect)
						flag++;
				}
	}
	return (flag % 2);
}

bool cPolygon::isPointOnEdge(cPoint P) const
{
	double d;
	double r = 0.04;
	for (int i = 0; i < numVer; i++)
	{
		d = P.distance(vertices[i]) + P.distance(vertices[(i + 1) % numVer]) - vertices[i].distance(vertices[(i + 1) % numVer]);
		if (fabs(d) <= r)
			return true;
	}
	return false;
}

bool cPolygon::isIntersect(cShape* aS, HDC hdc, COLORREF cl) const
{
	cPoint t1(0, 0);
	double Sx = 0, Sy = 0;
	int check = 0, count = 0;
	double xMin = vertices[0].getX(), yMin = vertices[0].getY();
	double xMax = vertices[0].getX(), yMax = vertices[0].getY();
	for (int i = 1; i < numVer; i++)
	{
		if (xMin > vertices[i].getX())
			xMin = vertices[i].getX();
		if (xMax < vertices[i].getX())
			xMax = vertices[i].getX();
		if (yMin > vertices[i].getY())
			yMin = vertices[i].getY();
		if (yMax < vertices[i].getY())
			yMax = vertices[i].getY();
	}
	for (double i = xMin; i <= xMax; i++)
		for (double j = yMin; j <= yMax; j++)
		{
			cPoint p(i, j);

			if ((this->isPointOnEdge(p) && aS->isPointOnEdge(p)) || (this->isPointOnEdge(p) && aS->isPointInside(p)) || (this->isPointInside(p) && aS->isPointOnEdge(p)))
			{
				Ellipse(hdc, i - 0.5, j - 0.5, i + 0.5, j + 0.5);
				check = 1;
				count++;
				Sx += i;
				Sy += j;
				t1 = p;
			}
			else if (this->isPointInside(p) && aS->isPointInside(p))
			{
				SetPixel(hdc, i, j, cl);
				check = 1;
				t1 = p;
			}
		}
	cPoint t((int)(Sx / count), (int)(Sy / count));
	if (this->isPointInside(t) && aS->isPointInside(t))
		t.mark(hdc, 5, RGB(0, 0, 0));
	else
		t1.mark(hdc, 5, RGB(0, 0, 0));
	return check;
}

void cPolygon::move(double dx, double dy)
{
	for (int i = 0; i < numVer; i++)
		vertices[i].move(dx, dy);
}

void cPolygon::scale(cPoint Center, double s)
{
	for (int i = 0; i < numVer; i++)
		vertices[i].scale(Center, s);
}

void cPolygon::rotate(cPoint Center, double alp)
{
	for (int i = 0; i < numVer; i++)
		vertices[i].rotate(Center, alp);
}

void cPolygon::draw(HDC hdc, COLORREF cl) const
{
	static POINT p[MAX_VER];
	for (int i = 0; i < numVer; i++)
	{
		p[i].x = vertices[i].getX();
		p[i].y = vertices[i].getY();
	}
	Polygon(hdc, p, numVer);
}
