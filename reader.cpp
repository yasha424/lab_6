#include "reader.h"

vector <Triangle> create_triangles(string path){
    ifstream in(path);
    vector <Triangle> triangles;
    if (in) {
        string tmp;
        vector <Point> points;
        while (getline(in, tmp)) {
            if (tmp[0] == 'v') {
                Point point = parse_point(tmp);
                points.push_back(point);
            }

            if (tmp[0] == 'f') {
                Triangle triangle = parse_triangle(tmp, points);
                triangles.push_back(triangle);
            }
        }
    }
    return triangles;
}

Point parse_point(string point_line){
    Point p;

    int start = point_line.find(" ");
    point_line.erase(0, start + 1);
    int index = point_line.find(" ");
    p.x = stod(point_line.substr(0, index));

    point_line.erase(0, index + 1);
    index = point_line.find(" ");
    p.y = stod(point_line.substr(0, index));

    point_line.erase(0, index + 1);
    index = point_line.find(" ");
    p.z = stod(point_line.substr(0, index));

    return p;
}

Triangle parse_triangle(string triangle_line, vector <Point> &points){
    Triangle t;

    int start = triangle_line.find(" ");
    triangle_line.erase(0, start + 1);
    int index = triangle_line.find("/");
    if (index != string::npos) {
        t.p1 = points[stoi(triangle_line.substr(0, index)) - 1];
    } else {
        index = triangle_line.find(" ");
        t.p1 = points[stoi(triangle_line.substr(0, index)) - 1];
    }
    index = triangle_line.find(" ");
    triangle_line.erase(0, index + 1);
    index = triangle_line.find("/");
    if (index != string::npos) {
        t.p2 = points[stoi(triangle_line.substr(0, index)) - 1];
    } else {
        index = triangle_line.find(" ");
        t.p2 = points[stoi(triangle_line.substr(0, index)) - 1];
    }
    index = triangle_line.find(" ");
    triangle_line.erase(0, index + 1);
    index = triangle_line.find("/");
    if (index != string::npos) {
        t.p3 = points[stoi(triangle_line.substr(0, index)) - 1];
    } else {
        index = triangle_line.find(" ");
        t.p3 = points[stoi(triangle_line.substr(0, index)) - 1];
    }

    return t;
}
