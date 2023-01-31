#include "pch.h"
#include "cRectangle.h"

void cRectangle::setVertices(double xUL, double yUL, double width, double height)
{
    vertices[0] = cPoint(xUL, yUL);
    vertices[1] = cPoint(xUL + width, yUL);
    vertices[2] = cPoint(xUL + width, yUL + height);
    vertices[3] = cPoint(xUL, yUL + height);
}
