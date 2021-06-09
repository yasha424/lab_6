#include "point.h"

Point::Point(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Point::intersection(Point p1, Point p2, Point p3){
    if (area(p1, p2, p3) == ( area(p1, p2, Point(x, y, z)) + area(p1, p3, Point(x, y, z)) + area(p2, p3, Point(x, y, z)))) {
        return true;
    }
    return false;
}

double Point::area(Point p1, Point p2, Point p3){
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double z1 = p2.z - p1.z;

    double x2 = p3.x - p1.x;
    double y2 = p3.y - p1.y;
    double z2 = p3.z - p1.z;

    Point vector1(x1, y1, z1);
    Point vector2(x2, y2, z2);

    double x = vector1.y * vector2.z - vector1.z * vector2.y;
    double y = vector1.z * vector2.x - vector1.x * vector2.z;
    double z = vector1.x * vector2.y - vector1.y * vector2.x;

    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) / 2;
}
