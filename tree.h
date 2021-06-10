#pragma once
#include "point.h"
#include "triangle.h"
#include "cube.h"
#include <string>
#include <vector>

using namespace std;

class Tree
{

public: 
	Tree* children[8];
	Cube area;
	vector <Triangle> triangles;
	int k = 0;
	Tree(vector <Triangle> tr, Cube c) {
		area = c;
		triangles = tr;
		for (int i = 0; i < 8; i++) {
			children[i] = nullptr;
		}
	}
	Tree() {};
	void insertTriangle(vector <Triangle> tr, Cube cube);
};
/*
0 TLF(top_left_front)
1 TRF(top_right_front)
2 BRF(bottom_right_front)
3 BLF(bottm_left_front)
4 TLB(top_left_back)
5 TRB(top_right_back)
6 BRB(bottom_right_back)
7 BLB(bottom_left_back)
*/
