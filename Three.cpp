#include "Tree.h"

inline void Tree::insertTriangle(Triangle tr) {
	Tree* temp =  Root;
    Tree* top_left_front = temp->children[0];
    Tree* bottom_right_back = temp->children[6];
	float trX, trY, trZ;
	tr.maxCoordinate(&trX, &trY, &trZ);
    if (Root == NULL) {
        Tree* temp1 = new Tree(tr);
        temp1->Prev = nullptr;
        Root = temp1;
    }
    else if (top_left_front == nullptr or bottom_right_back == nullptr) {
        //...................
    }
	float midx = (top_left_front->_X + bottom_right_back->_X) / 2;
	float midy = (top_left_front->_Y + bottom_right_back->_Y) / 2;
	float midz = (top_left_front->_Z + bottom_right_back->_Z) /2;
    int pos = -1;
    if (trX <= midx) {
        if (trY <= midy) {
            if (trZ <= midz)
                pos = 0;
            else
                pos = 4;
        }
        else {
            if (trZ <= midz)
                pos = 3;
            else
                pos = 7;
        }
    }
    else {
        if (trY <= midy) {
            if (trZ <= midz)
                pos = 1;
            else
                pos = 5;
        }
        else {
            if (trZ <= midz)
                pos = 2;
            else
                pos = 6;
        }
    }
    if (temp->children[pos] == nullptr) {
        Tree* temp1=new Tree(tr);
        temp->children[pos] = temp1;
        temp1->Prev = temp;
    }
    else  {
        temp->children[pos]->insertTriangle(tr);
    }

}
