#pragma once
#include "point.h"
#include "triangle.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector <Triangle> create_triangles(string);

Point parse_point(string);

Triangle parse_triangle(string, vector <Point> &points);
