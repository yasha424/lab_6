#include <iostream>

#include <ctime>
#include <vector>

#include "reader.h"
#include "point.h"
#include "triangle.h"
#include "camera.h"
#include "image.h"
#include "plane.h"

using namespace std;

int main(){
    vector <Triangle> triangles = create_triangles("samples/cow.obj");
    int size = 40;
    double gap = 0.05;
    Camera camera(Point(-1, -1, 0), Point(0, 0, 0), size, gap);

    vector <vector<Pixel>> pixels;
    //
    // for (size_t i = 0; i < 87; i++) {
    //     vector <Pixel> pixels_1;
    //     for (size_t j = 0; j < 51; j++) {
    //         int r = rand()%255;
    //         int g = rand()%255;
    //         int b = rand()%255;
    //         Pixel pixel(r, g, b);
    //         pixels_1.push_back(pixel);
    //     }
    //     pixels.push_back(pixels_1);
    // }

    bool intersect = false;

    for (size_t i = 0; i < size * 2 + 1; i++) {
        vector <Pixel> pixels_1;
        for (size_t j = 0; j < size * 2 + 1; j++) {
            for (size_t k = 0; k < triangles.size(); k++) {
                Plane plane(triangles[k]);
                Point point = plane.getPointIntersection(Point(-1, -1, 0), Point(0 - (gap * size) + (gap * j), 0, 0  - (gap * size) + (gap * i)));
                if (point.intersection(triangles[k].p1, triangles[k].p2, triangles[k].p3)) {
                    intersect = true;
                    break;
                }
            }
            if (intersect) {
                Pixel pixel(255, 255, 255);
                pixels_1.push_back(pixel);
                cout << "x";
            } else {
                Pixel pixel(0, 0, 0);
                pixels_1.push_back(pixel);
                cout << ".";
            }
            intersect = false;
        }
        cout << endl;
        pixels.push_back(pixels_1);
    }

    Image image(81, 81, pixels);
    image.write("test.bmp");

    // Point p1(0, 0, 3);
    // Point p2(5, 0, 0);
    // Point p3(0, 5, 0);
    //
    // Point cum(0, 0, 3);
    // Point obj(-1, -1, 2);
    // Plane plane(p1, p2, p3);
    //
    // Point inter = plane.getPointIntersection(cum, obj);
    //
    // cout << inter.x << ", " << inter.y << ", " << inter.z << endl;
    //
    // cout << inter.intersection(p1, p2, p3) << endl;
    //
}
