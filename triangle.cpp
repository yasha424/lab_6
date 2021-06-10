#include "triangle.h"

Triangle::Triangle(Point p1, Point p2, Point p3){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

void Triangle::maxCoordinate(float* _X, float* _Y, float* _Z) {
	if (p1.x < p2.x) {
		if (p2.x < p3.x) { *_X = p3.x;}
		else { *_X = p2.x; }
	}
	else {
		if (p1.x<p3.x){ *_X = p3.x; }
		else {* _X = p1.x; }
	}
	if (p1.y < p2.y) {
		if (p2.y < p3.y) {*_Y = p3.y; }
		else {* _Y = p2.y; }
	}
	else {
		if (p1.y < p3.y) {* _Y = p3.y; }
		else { *_Y = p1.y; }
	}
	if (p1.z < p2.z) {
		if (p2.z < p3.z) { *_Z = p3.z; }
		else { *_Z = p2.z; }
	}
	else {
		if (p1.z < p3.z) { *_Z = p3.z; }
		else { *_Z = p1.z; }
	}
}
