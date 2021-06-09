#include <iostream>

#include "reader.h"
#include "point.h"
#include "triangle.h"

using namespace std;

int main(){
    vector <Triangle> triangles = create_triangles("samples/cow.obj");

    for (size_t i = 0; i < triangles.size(); i++) {
        cout << triangles[i].p1.x << ", " << triangles[i].p1.y << ", " << triangles[i].p1.z << endl;
    }
}
