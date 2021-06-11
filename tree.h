#pragma once
#include "triangle.h"
#include "cube.h"
#include "plane.h"
#include <iostream>
#include <vector>

class Node{
public:
	Cube boundary;
	vector <Triangle> triangles;
	Node *nodes[8];

	Node(Cube, vector <Triangle>);
};

class Tree{
public:
	Node *root;
	int capacity = 48; // idk why

	Tree(Cube, vector<Triangle>);

	void make_tree(Node*&);

	static bool is_triangle_in(Cube, Triangle);

	bool is_ray_intersect(Point, Point, Cube, double&);

	void find_min_intersection(Point, Point, Triangle&, double&, Node*, double&);
};
