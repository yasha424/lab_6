#pragma once
#include <iostream>
#include "point.h"
#include "triangle.h"
using namespace std;

class Plane{
    double A, B, C, D;
public:
    Plane(Point, Point, Point);
    Plane(Triangle);
    Plane(double, double, double,double);
    Point getPointIntersection(Point X1,Point X2);
    double getCos(Point,Point);
};
