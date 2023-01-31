#pragma once
#include"cRectangle.h"
class cSquare : public cRectangle
{
public:
	//Phuong thuc thiet lap va pha huy
	cSquare(double xUL = 100, double yUL = 100, double edge = 150) : cRectangle(xUL, yUL, edge, edge) {}
	~cSquare() {}
};