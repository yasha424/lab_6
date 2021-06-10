#pragma once
#include "Point.h"
#include "Triangle.h"
#include <string>
#include <vector>

using namespace std;

class Tree
{

public: 
	Triangle triangle;
	Tree* children[8];
	float _X, _Y, _Z;
	
	int k = 0;
	Tree(Triangle triangle) {
		this->triangle = triangle;
		for (int i = 0; i < 8; i++) {
			children[i] = nullptr;
		}
	}
	Tree() {}
	void insertTriangle(Triangle tr);
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
