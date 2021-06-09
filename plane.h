#pragma once
#include <iostream>
#include "point.h"
using namespace std;

class Plane{
    double A, B, C, D;
public:
    Plane(Point, Point, Point);
    Plane(double, double, double,double);
    Point getPointIntersection(Point X1,Point X2);
};
