#pragma once
#include "triangle.h"
#include "cube.h"
#include <iostream>
#include <vector>

class Node{
public:
	Cube boundary;
	vector <Triangle> triangles;
	Node *URF, *ULF, *URB, *ULB, *DRF, *DLF, *DRB, *DLB; // up-right-front, up-left-front, etc.

	Node(Cube, vector <Triangle>);
};

class Tree{
public:
	Node *root;
	int capacity = 48; // idk why

	Tree(Cube, vector<Triangle>);

	void make_tree(Node*);

	static bool is_triangle_in(Cube, Triangle);
};
