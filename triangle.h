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
    Triangle(){}

    Triangle(Point, Point, Point);
};
