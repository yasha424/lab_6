#pragma once
#include <iostream>
#include "point.h"

class Camera{
public:
    Point center;
    Point screen;
    int size;
    double gap;

    Camera(){}

    Camera(Point, Point, int, double);
};
