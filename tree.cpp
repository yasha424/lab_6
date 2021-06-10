#include "tree.h"
#include "cude.h"
 void Tree::insertTriangle(vector <Triangle> tr, Cube cube) {
    Tree* top_left_front = children[0];
    Tree* bottom_right_back = children[6];
	//float trX, trY, trZ;

	//tr.maxCoordinate(&trX, &trY, &trZ);
     if (top_left_front == nullptr or bottom_right_back == nullptr) {
         if (top_left_front == nullptr and bottom_right_back == nullptr) {
             Tree* temp1 = new Tree( tr,  cube);
             children[0] = temp1;
        }
         else if (top_left_front == nullptr) {
             if (cube.max.x < top_left_front->area.max.x) {
                 Tree* temp1 = new Tree(tr,  cube);
                 Tree* temp2 = children[0];
                 children[0] = temp1;
                 children[6] = temp2;
             }
         }
         else {
             Tree* temp1 = new Tree( tr,  cube);
             children[6] = temp1;
         }
    }
     else {
         children[0]->area.max;
         children[6]->area.max;
         float midx = (top_left_front->area.max.x + bottom_right_back->area.max.x) / 2;
         float midy = (top_left_front->area.max.y + bottom_right_back->area.max.y) / 2;
         float midz = (top_left_front->area.max.z + bottom_right_back->area.max.z) / 2;
         int pos = -1;
         if (cube.max.x <= midx) {
             if (cube.max.y <= midy) {
                 if (cube.max.z <= midz)
                     pos = 0;
                 else
                     pos = 4;
             }
             else {
                 if (cube.max.z <= midz)
                     pos = 3;
                 else
                     pos = 7;
             }
         }
         else {
             if (cube.max.y <= midy) {
                 if (cube.max.z <= midz)
                     pos = 1;
                 else
                     pos = 5;
             }
             else {
                 if (cube.max.z <= midz)
                     pos = 2;
                 else
                     pos = 6;
             }
         }
         if (children[pos] == nullptr) {
             Tree* temp1 = new Tree(tr, cube);
             children[pos] = temp1;
         }
         else {
             children[pos]->insertTriangle(tr,cube);
         }
     }

}
