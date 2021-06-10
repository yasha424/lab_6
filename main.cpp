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
    Point min_point, max_point;
    vector <Triangle> triangles = create_triangles("samples/cow.obj", min_point, max_point);
    int size = 256;
    double gap = 0.001;
    Camera camera(Point(0, 0, 0), Point(1, 1, 0), size, gap);

    cout << min_point.x << ", " << min_point.y << ", " << min_point.z << endl;
    cout << max_point.x << ", " << max_point.y << ", " << max_point.z << endl;

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
    double color;
    for (size_t i = 0; i < size * 2 + 1; i++) {
        vector <Pixel> pixels_1;
        for (size_t j = 0; j < size * 2 + 1; j++) {
            color =0;
            double d = 0;
            for (size_t k = 0; k < triangles.size(); k++) {
                Plane plane(triangles[k]);
                Point pixel(0 - (gap * size) + (gap * j), -1, 0 - (gap * size) + (gap * i));
                Point point = plane.getPointIntersection(Point(-1, -4, 0), pixel);
                Point vectorIntersection(-point.x+pixel.x,-point.y+pixel.y,-point.z+pixel.z);
                if (point.intersection(triangles[k].p1, triangles[k].p2, triangles[k].p3)&&(d<vectorIntersection.getModul())) {
                        intersect = true;
                        d= vectorIntersection.getModul();
                        color = plane.getCos(point, pixel);
                }
            }
            if (intersect) {
                Pixel pixel(255*color, 255*color, 255*color);
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

    Image image(size*2+1, size*2+1, pixels);
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
