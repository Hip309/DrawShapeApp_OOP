#pragma once
#include "framework.h"
#include "cPoint.h"
#include "cShape.h"

const double Pi = atan(1) * 4;

class cEllipse : public cShape
{
protected:
	cPoint E; //tam
	double a, b; //do dai nua truc lon va do dai nua truc be
public:
	//Phuong thuc khoi tao va pha huy
	cEllipse(double xE = 500, double yE = 100, double da = 200, double db = 100) : E(xE, yE), a(da), b(db) {};
	~cEllipse() {}
	//Phuong thuc cap nhat thong tin
	void setCenter(double xE, double yE) { E = cPoint(xE, yE); a = 0; b = 0; }
	//Phuong thuc thuc cung cap thong tin
	cPoint getCenter() { return E; }
	//Phuong thuc kiem tra
	virtual bool isPointInside(cPoint P) const override; //kiem tra diem co nam trong elip
	virtual bool isPointOnEdge(cPoint P) const override; //kiem tra diem co thuoc duong elip
	bool isIntersect(cShape* aS, HDC hdc, COLORREF cl = RGB(226, 238, 202)) const override;
	//Operation
	void move(double dx, double dy) override { E.move(dx, dy); }
	void scale(double s) override { a *= s; b *= s; }
	virtual void rotate(double alp) override;
	virtual void draw(HDC hdc, COLORREF cl = RGB(0, 100, 100)) const override { Ellipse(hdc, (int)(E.getX() - a), (int)(E.getY() - b), (int)(E.getX() + a), (int)(E.getY() + b)); }
};
