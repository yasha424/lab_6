#pragma once
class Point
{
public:
	float x, y, z;

};
struct colorRGB {
	float red, green, blue;
};
class Triangle {
public:
	Point p1, p2, p3;
	Triangle(Point p1, Point p2, Point p3) { this->p1 = p1; this->p2 = p2; this->p3 = p3; }
	~Triangle();
};
