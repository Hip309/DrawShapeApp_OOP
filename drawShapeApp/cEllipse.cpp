#include "pch.h"
#include "cEllipse.h"

bool cEllipse::isPointInside(cPoint P) const
{
	double dx = P.getX() - E.getX();
	double dy = P.getY() - E.getY();
	return (pow(dx / a, 2) + pow(dy / b, 2) - 1) < 0.015;
}

bool cEllipse::isPointOnEdge(cPoint P) const
{
	double dx = P.getX() - E.getX();
	double dy = P.getY() - E.getY();
	double d = pow(dx / a, 2) + pow(dy / b, 2) - 1;
	return (fabs(d) <= 0.03);
}

bool cEllipse::isIntersect(cShape* aS, HDC hdc, COLORREF cl) const
{
	cPoint t1(0, 0);
	double Sx = 0, Sy = 0;
	int check = 0, count = 0;
	for (double i = E.getX() - a; i <= E.getX() + a; i++)
		for (double j = E.getY() - b; j <= E.getY() + b; j++)
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
			else
				if (this->isPointInside(p) && aS->isPointInside(p))
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

void cEllipse::rotate(double alp)
{
	if (alp == 90 || alp == -90)
	{
		double temp = a;
		a = b;
		b = temp;
	}
}

