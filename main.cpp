#include <iostream>

#include <ctime>
#include <vector>

#include "reader.h"
#include "point.h"
#include "triangle.h"
#include "camera.h"
#include "image.h"
#include "plane.h"
#include "cube.h"
#include "tree.h"

using namespace std;

int main(){
    Point min_point, max_point;
    vector <Triangle> triangles = create_triangles("samples/airboat.obj", min_point, max_point);
    Tree *tree = new Tree(Cube(min_point, max_point), triangles);

    int size = 524;
    double gap = 0.002;

    vector <vector<Pixel>> pixels;

    double start = clock();

    double color;
    for (size_t i = 0; i < size * 2 + 1; i++) {
        vector <Pixel> pixels_1;
        for (size_t j = 0; j < size * 2 + 1; j++) {
            color = 0;
            double min = DBL_MAX;
            Triangle tr;
            tree->find_min_intersection(Point(12, 0, 12), Point(11, 0 - (gap * size) + (gap * i), 11 - (gap * size) + (gap * j)), tr, min, tree->root, color);
            if (min != DBL_MAX) {
                pixels_1.push_back(Pixel(255 * color, 122, 122));
            } else {
                pixels_1.push_back(Pixel(0, 0, 0));
            }
        }
        pixels.push_back(pixels_1);
    }

    double end = clock();
    cout << (end - start) / 1000000 << endl;

    Image image(size*2+1, size*2+1, pixels);
    image.write("test.bmp");
}
