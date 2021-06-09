#include "plane.h"

Plane::Plane(Point p1, Point p2, Point p3)
{
    double a1 = p2.x - p1.x;

    double b1 = p2.y - p1.y;

    double c1 = p2.z - p1.z;

    double a2 = p3.x - p1.x;

    double b2 = p3.y - p1.y;

    double c2 = p3.z - p1.z;

    this->A = b1 * c2 - b2 * c1;

    this->B = a2 * c1 - a1 * c2;

    this->C = a1 * b2 - b1 * a2;

    this->D = (- A * p1.x - B * p1.y - C * p1.z);


}
