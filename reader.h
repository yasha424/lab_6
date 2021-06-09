#pragma once
#include "point.h"
#include "triangle.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <float.h>
using namespace std;

vector <Triangle> create_triangles(string, Point &min_point, Point &max_point);

Point parse_point(string);

Triangle parse_triangle(string, vector <Point> &points);
