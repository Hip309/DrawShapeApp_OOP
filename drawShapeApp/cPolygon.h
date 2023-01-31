#pragma once
#include "framework.h"
#include <vector>
#include "cPoint.h"
#include "cShape.h"

class cPolygon : public cShape
{
protected:
	int numVer;
	cPoint* vertices;
public:
	//Phuong thuc thiet lap va pha huy
	static cPoint verDefault[];
	cPolygon(int num = 4, cPoint* P = NULL) : numVer(num) { setVertices(num, P); }
	~cPolygon() { delete[] vertices; }
	//Phuong thuc cap nhat thong tin
	virtual void setVertices(int num, cPoint* P); //cap nhat thong tin cac dinh
	//Phuong thuc cung cap thong tin
	cPoint getCenter() const; //thong tin trong tam cua da giac
	//Phuong thuc kiem tra
	bool isPointInside(cPoint P) const override; //kiem tra 1 diem co nam trong da giac(dua theo thuat toan Ray casting)
	bool isPointOnEdge(cPoint P) const override; //kiem tra 1 diem co nam tren canh cua da giac
	bool isIntersect(cShape* aS, HDC hdc, COLORREF cl = RGB(226, 238, 202)) const override; //kiem tra 1 hinh bat ky co giao voi da giac
	//Operation
	void move(double dx, double dy) override;
	void scale(cPoint Center, double s);
	void scale(double s) override { scale(getCenter(), s); }
	void rotate(cPoint Center, double alp);
	void rotate(double alp) override { rotate(getCenter(), alp); }
	void draw(HDC hdc, COLORREF cl = RGB(0, 100, 100)) const override;
};