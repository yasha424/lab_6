#pragma once
#include "point.h"
#include <iostream>

class Cube{
public:
    Point min;
    Point max;

    Cube(){}

    Cube(Point, Point);
};
