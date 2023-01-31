#pragma once
#include "cPolygon.h"

class cTriangle : public cPolygon
{
public:
	//Phuong thuc thiet lap va pha huy
	static cPoint verTriDefault[3];
	cTriangle(cPoint* p = NULL) : cPolygon(3) { setVertices(p); }
	~cTriangle() {}
	//Phuong thuc cap nhap thong tin
	void setVertices(cPoint* P);
};