#include "pch.h"
#include "cPoint.h"

const double Pi = atan(1) * 4;
const int MAX_VER = 1000;

cPoint& cPoint::operator=(const cPoint& P)
{
	X = P.X;
	Y = P.Y;
	return *this;
}

double cPoint::distance(cPoint P) const
{
	return  sqrt(pow((P.X - X), 2) + pow((P.Y - Y), 2));
}

void cPoint::scale(cPoint P, double s)
{
	X = (X - P.getX()) * s + P.getX();
	Y = (Y - P.getY()) * s + P.getY();
}

void cPoint::mark(HDC hdc, int size, COLORREF cl)
{
	for (int i = 0; i < size; i++)
	{
		SetPixel(hdc, X - i, Y, cl);
		SetPixel(hdc, X + i, Y, cl);
		SetPixel(hdc, X, Y - i, cl);
		SetPixel(hdc, X, Y + i, cl);
	}
}

cPoint cPoint::setVector(cPoint P) const
{
	cPoint temp;
	temp.X = P.getX() - getX();
	temp.Y = P.getY() - getY();
	return temp;
}

void cPoint::rotate(cPoint P, double alp)
{
	double cosa = cos(alp * Pi / 180);
	double sina = sin(alp * Pi / 180);
	double X1 = ((X - P.X) * cosa) - ((Y - P.Y) * sina) + P.X;
	Y = ((X - P.X) * sina) + ((Y - P.Y) * cosa) + P.Y;
	X = X1;
}
