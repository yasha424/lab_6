#pragma once
#include <iostream>
#include "point.h"
#include "pixel.h"

class Triangle{
public:
    Point p1, p2, p3;
    Pixel color;

    Triangle(){};

	Triangle(Point, Point, Point);

    void maxCoordinate(float* _X, float* _Y, float* _Z);
};
