#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Point{
public:
    double x, y, z;

    Point(){}

    Point(double, double, double);

    bool intersection(Point, Point, Point);

    double area(Point, Point, Point);

    double getModul();

    static double distance(Point, Point);
};
