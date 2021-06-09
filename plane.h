#pragma once
#include <iostream>
#include "point.h"
using namespace std;

class Plane{
public:
    double A, B, C, D;
    Plane(Point, Point, Point);
};
