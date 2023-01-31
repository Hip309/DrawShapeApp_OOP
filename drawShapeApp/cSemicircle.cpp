#include "pch.h"
#include "cSemicircle.h"

bool cSemicircle::isPointInside(cPoint P) const
{
    if (sequence == 1 && (P.getY() < E.getY()))
    {
        if (P.distance(E) < a)
            return true;
    }
    else if (sequence == 2 && (P.getX() > E.getX()))
    {
        if (P.distance(E) < a)
            return true;
    }
    else if (sequence == 3 && (P.getY() > E.getY()))
    {
        if (P.distance(E) < a)
            return true;
    }
    else if (sequence == 4 && (P.getX() < E.getX()))
    {
        if (P.distance(E) < a)
            return true;
    }
    return false;
}

bool cSemicircle::isPointOnEdge(cPoint P) const
{
    double d = P.distance(E) - a;
    if (sequence == 1 && (P.getY() == E.getY() || P.getY() < E.getY()))
    {
        if ((P.getX() <= (E.getX() + a)) && (P.getX() >= (E.getX() - a)) && fabs(d) <= 1)
            return true;
    }
    else if (sequence == 2 && (P.getX() == E.getX() || P.getX() > E.getX()))
    {
        if ((P.getY() <= (E.getY() + a)) && (P.getY() >= (E.getY() - a)) && fabs(d) <= 1)
            return true;
    }
    else if (sequence == 3 && (P.getY() == E.getY() || P.getY() > E.getY()))
    {
        if ((P.getX() <= (E.getX() + a)) && (P.getX() >= (E.getX() - a)) && fabs(d) <= 1)
            return true;
    }
    else if (sequence == 4 && (P.getX() == E.getX() || P.getX() < E.getX()))
    {
        if ((P.getY() <= (E.getY() + a)) && (P.getY() >= (E.getY() - a)) && fabs(d) <= 1)
            return true;
    }
    return false;
}

void cSemicircle::rotate(double alp)
{
    int temp = sequence;
    if (alp == -90)
    {
        if (temp == 1)
        {
            sequence += 3;
            temp += 3;
        }
        else {
            sequence = (temp + 3) % 4;
            temp += 3;
        }
    }
    else if (alp == 90)
    {
        if (sequence <= 3)
        {
            sequence += 1;
            temp += 1;
        }
        else {
            sequence = 1;
            temp += 1;
        }
    }
}

void cSemicircle::draw(HDC hdc, COLORREF cl) const
{
    if (getSequence() == 1)
    {
        Pie(hdc, E.getX() - a, E.getY() - a, E.getX() + a, E.getY() + a, E.getX() + a, E.getY(), E.getX() - a, E.getY());
    }
    else if (getSequence() == 2)
    {
        Pie(hdc, E.getX() - a, E.getY() - a, E.getX() + a, E.getY() + a, E.getX(), E.getY() + a, E.getX(), E.getY() - a);
    }
    else if (getSequence() == 3)
    {
        Pie(hdc, E.getX() - a, E.getY() - a, E.getX() + a, E.getY() + a, E.getX() - a, E.getY(), E.getX() + a, E.getY());
    }
    else if (getSequence() == 4)
    {
        Pie(hdc, E.getX() - a, E.getY() - a, E.getX() + a, E.getY() + a, E.getX(), E.getY() - a, E.getX(), E.getY() + a);
    }
}
