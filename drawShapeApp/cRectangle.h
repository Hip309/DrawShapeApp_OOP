#pragma once
#include"cPolygon.h"

class cRectangle : public cPolygon
{
public:
	//Phuong thuc thiet lap va pha huy
	cRectangle(double xUL = 100, double yUL = 100, double width = 200, double height = 100) : cPolygon(4) { setVertices(xUL, yUL, width, height); }
	~cRectangle() {}
	//Setter
	void setVertices(double xUL, double yUL, double width, double height);
};