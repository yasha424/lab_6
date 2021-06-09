#include "Tree.h"

 void Tree::insertTriangle(Triangle tr) {
    Tree* top_left_front = children[0];
    Tree* bottom_right_back = children[6];
	float trX, trY, trZ;

	tr.maxCoordinate(&trX, &trY, &trZ);
     if (top_left_front == nullptr or bottom_right_back == nullptr) {
         if (top_left_front == nullptr and bottom_right_back == nullptr) {
             Tree* temp1 = new Tree(tr);
             children[0] = temp1;
        }
         else if (top_left_front == nullptr) {
             if (trX < top_left_front->_X) {
                 Tree* temp1 = new Tree(tr);
                 Tree* temp2 = children[0];
                 children[0] = temp1;
                 children[6] = temp2;
             }
         }
         else {
             Tree* temp1 = new Tree(tr);
             children[6] = temp1;
         }
    }
     else {
         children[0]->triangle.maxCoordinate(&top_left_front->_X, &top_left_front->_Y, &top_left_front->_Z);
         children[6]->triangle.maxCoordinate(&bottom_right_back->_X, &bottom_right_back->_Y, &bottom_right_back->_Z);
         float midx = (top_left_front->_X + bottom_right_back->_X) / 2;
         float midy = (top_left_front->_Y + bottom_right_back->_Y) / 2;
         float midz = (top_left_front->_Z + bottom_right_back->_Z) / 2;
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
         if (children[pos] == nullptr) {
             Tree* temp1 = new Tree(tr);
             children[pos] = temp1;
         }
         else {
             children[pos]->insertTriangle(tr);
         }
     }

}
