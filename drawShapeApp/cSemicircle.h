#pragma once
#include"cCircle.h"

class cSemicircle :public cCircle {
private:
    int sequence;
public:
    cSemicircle(double xC = 500, double yC = 500, double r = 200) : cCircle(xC, yC, r) { sequence = 1; };
    ~cSemicircle() {}
    //Phuong thuc cung cap thong tin
    int getSequence()const { return sequence; }
    //Phuong thuc kiem tra
    bool isPointInside(cPoint P)const override;
    bool isPointOnEdge(cPoint P) const override;
    //Phuong thuc xu ly
    void rotate(double alp) override;
    void draw(HDC hdc, COLORREF cl = RGB(0, 100, 100))const override;

};