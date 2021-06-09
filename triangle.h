#pragma once
#include <iostream>
#include "point.h"
struct colorRGB {
	float red, green, blue;
};

class Triangle{
public:
    Point p1, p2, p3;
    colorRGB color;
    Triangle(){};
    void maxCoordinate(float* _X, float* _Y, float* _Z);
    Triangle(Point, Point, Point);
};
