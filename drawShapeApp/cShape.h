#pragma once
#include "framework.h"
#include "cPoint.h"

//lop co so truu tuong
class cShape
{
public:
	//thiet lap cac pthuc ao thuan tuy
	virtual void move(double dx, double dy) = NULL; //tinh tien hinh
	virtual void scale(double s) = NULL; //phong to/thu nho hinh theo ty le
	virtual void rotate(double alp) = NULL; //quay hinh voi tam hinh co dinh
	virtual bool isPointInside(cPoint P) const = NULL; //kiem tra diem nam trong hinh
	virtual bool isPointOnEdge(cPoint P) const = NULL; //ktra diem nam tren canh cua hinh
	virtual bool isIntersect(cShape* aS, HDC hdc, COLORREF cl = RGB(226, 238, 202)) const = NULL; //ktra co giao nhau voi hinh khac
	virtual void draw(HDC hdc, COLORREF cl = RGB(0, 100, 100)) const = NULL; //ve hinh
};

