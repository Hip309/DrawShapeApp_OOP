#pragma once
#include <wtypes.h>

class cPoint
{
private:
	double X, Y;
public:
	//Phuong thuc khoi tao
	cPoint(double x = 0, double y = 0) :X(x), Y(y) { }
	//Phuong thuc cap nhat thong tin
	void setX(double x) { X = x; }
	void setY(double y) { Y = y; }
	cPoint& operator = (const cPoint& P);
	//Phuong thuc cung cap thong tin
	double getX() const { return X; }
	double getY() const { return Y; }
	//Phuong thuc xu ly
	double distance(cPoint P) const; //tinh khoang cach toi 1 diem
	void move(double dx, double dy) { X += dx; Y += dy; } //tinh tien diem 
	void scale(cPoint P, double s); //dich chuyen diem goi thuc hien pthuc (tam goi la A) den vi tri moi(tam goi la B)
								    //sao cho vector PB = vector PA * s
	void mark(HDC hdc, int size, COLORREF cl = RGB(40, 41, 49)); //tu toa do diem ve hinh chu thap
	cPoint setVector(cPoint P) const; //tao voi diem P 1 vector(goc vector la diem goi thuc hien pthuc)
	void rotate(cPoint P, double alp); //dich chuyen diem goi thuc hien pthuc (tam goi la A) den vi tri moi(tam goi la B)
									   //sao cho vector PB lech 1 goc alp so voi vector PA
};