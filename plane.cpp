#include "plane.h"
Plane::Plane(double a, double b, double c,double d){
    this->A = a;

    this->B = b;

    this->C = c;

    this->D = d;
}

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

Plane::Plane(Triangle triangle){
    double a1 = triangle.p2.x - triangle.p1.x;

    double b1 = triangle.p2.y - triangle.p1.y;

    double c1 = triangle.p2.z - triangle.p1.z;

    double a2 = triangle.p3.x - triangle.p1.x;

    double b2 = triangle.p3.y - triangle.p1.y;

    double c2 = triangle.p3.z - triangle.p1.z;

    this->A = b1 * c2 - b2 * c1;

    this->B = a2 * c1 - a1 * c2;

    this->C = a1 * b2 - b1 * a2;

    this->D = (- A * triangle.p1.x - B * triangle.p1.y - C * triangle.p1.z);
}

Point Plane::getPointIntersection(Point X1,Point X2){
    double m = X2.x-X1.x;
    double p = X2.y-X1.y;
    double l = X2.z-X1.z;

    double num = D+A*X1.x+B*X1.y+C*X1.z;
    double den = A *m+ B *p+ C*l;

    double t = 0;

    if(num != 0 && den!=0){
        t = (-1)* (num/den);
    }
    Point pointIntersection(X1.x+ m*t,X1.y+ p*t,X1.z+ l*t);
    return pointIntersection;
}
