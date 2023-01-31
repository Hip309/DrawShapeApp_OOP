#pragma once
#include"cEllipse.h"

class cCircle :public cEllipse
{
public:
	cCircle(double xC = 500, double yC = 500, double r = 200) : cEllipse(xC, yC, r, r) {};
	~cCircle() {}
};