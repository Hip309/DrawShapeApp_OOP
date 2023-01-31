#include "pch.h"
#include "cTriangle.h"

cPoint cTriangle::verTriDefault[] = { cPoint(500,500), cPoint(200,700), cPoint(700,700) };

void cTriangle::setVertices(cPoint* P)
{
	if (P == NULL)
	{
		vertices = new cPoint[3];
		memcpy(vertices, verDefault, sizeof(cPoint) * 3);
	}
	else
	{
		vertices = new cPoint[3];
		memcpy(vertices, P, sizeof(cPoint) * 3);
	}
}

