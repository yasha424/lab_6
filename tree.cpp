#include "tree.h"

Node::Node(Cube boundary, vector<Triangle> triangles){
    this->boundary = boundary;
    this->triangles = triangles;
    for (size_t i = 0; i < 8; i++) {
        nodes[i] = NULL;
    }
}

Tree::Tree(Cube boundary, vector<Triangle> triangles){
    root = new Node(boundary, triangles);
    make_tree(root);
}

void Tree::make_tree(Node *&node){
    Point center((node->boundary.max.x + node->boundary.min.x) / 2,
                 (node->boundary.max.y + node->boundary.min.y) / 2,
                 (node->boundary.max.z + node->boundary.min.z) / 2);

    vector <Cube> boundaries;
    boundaries.push_back(Cube(node->boundary.min, center));
    boundaries.push_back(Cube(center, node->boundary.max));

    Point p1(center.x, node->boundary.min.y, node->boundary.min.z);
    Point p11(node->boundary.max.x, center.y, center.z);
    boundaries.push_back(Cube(p1, p11));

    Point p2(node->boundary.min.x, center.y, node->boundary.min.z);
    Point p22(center.x, node->boundary.max.y, center.z);
    boundaries.push_back(Cube(p2, p22));

    Point p3(node->boundary.min.x, node->boundary.min.y, center.z);
    Point p33(center.x, center.y, node->boundary.max.z);
    boundaries.push_back(Cube(p3, p33));

    Point p4(center.x, center.y, node->boundary.min.z);
    Point p44(node->boundary.max.x, node->boundary.max.y, center.z);
    boundaries.push_back(Cube(p4, p44));

    Point p5(center.x, node->boundary.min.y, center.z);
    Point p55(node->boundary.max.x, center.y, node->boundary.max.z);
    boundaries.push_back(Cube(p5, p55));

    Point p6(node->boundary.min.x, center.y, center.z);
    Point p66(center.x, node->boundary.max.y, node->boundary.max.z);
    boundaries.push_back(Cube(p6, p66));

    for (size_t i = 0; i < boundaries.size(); i++) {
        vector <Triangle> trs;
        for (size_t j = 0; j < node->triangles.size(); j++) {
            if (is_triangle_in(boundaries[i], node->triangles[j])) {
                trs.push_back(node->triangles[j]);
            }
        }
        node->nodes[i] = new Node(boundaries[i], trs);
    }

    for (size_t i = 0; i < 8; i++) {
        if (node->nodes[i]->triangles.size() > capacity && (node->nodes[i]->boundary.max.x - node->nodes[i]->boundary.min.x > 0.00001)) {
            make_tree(node->nodes[i]);
        }
    }
}

bool Tree::is_triangle_in(Cube boundary, Triangle triangle){
    Point center((boundary.min.x + boundary.max.x) / 2, // cube center
                 (boundary.min.y + boundary.max.y) / 2,
                 (boundary.min.z + boundary.max.z) / 2);

    Point trp0(triangle.p1.x - center.x, // централизированный треугольник относительно куба, смещенного в центр
               triangle.p1.y - center.y,
               triangle.p1.z - center.z);

    Point trp1(triangle.p2.x - center.x,
               triangle.p2.y - center.y,
               triangle.p2.z - center.z);

    Point trp2(triangle.p3.x - center.x,
               triangle.p3.y - center.y,
               triangle.p3.z - center.z);

    double e0 = (boundary.max.x - boundary.min.x) / 2;
    double e1 = (boundary.max.y - boundary.min.y) / 2;
    double e2 = (boundary.max.z - boundary.min.z) / 2;

    Point f0(triangle.p2.x - triangle.p1.x, // вектора сторон треугольника
             triangle.p2.y - triangle.p1.y,
             triangle.p2.z - triangle.p1.z);

    Point f1(triangle.p3.x - triangle.p2.x,
             triangle.p3.y - triangle.p2.y,
             triangle.p3.z - triangle.p2.z);

    Point f2(triangle.p3.x - triangle.p1.x,
             triangle.p3.y - triangle.p1.y,
             triangle.p3.z - triangle.p1.z);

    Point a00(0, -f0.z, f0.y);

    double p0 = trp0.x * a00.x + trp0.y * a00.y + trp0.z * a00.z;
    double p1 = trp1.x * a00.x + trp1.y * a00.y + trp1.z * a00.z;
    double p2 = trp2.x * a00.x + trp2.y * a00.y + trp2.z * a00.z;
    double r = e1 * abs(a00.y) + e2 * abs(a00.z);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a01(0, -f1.z, f1.y);
    p0 = trp0.x * a01.x + trp0.y * a01.y + trp0.z * a01.z;
    p1 = trp1.x * a01.x + trp1.y * a01.y + trp1.z * a01.z;
    p2 = trp2.x * a01.x + trp2.y * a01.y + trp2.z * a01.z;
    r = e1 * abs(a01.y) + e2 * abs(a01.z);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a02(0, -f2.z, f2.y);
    p0 = trp0.x * a02.x + trp0.y * a02.y + trp0.z * a02.z;
    p1 = trp1.x * a02.x + trp1.y * a02.y + trp1.z * a02.z;
    p2 = trp2.x * a02.x + trp2.y * a02.y + trp2.z * a02.z;
    r = e1 * abs(a02.y) + e2 * abs(a02.z);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a10(f0.z, 0, -f0.x);
    p0 = trp0.x * a10.x + trp0.y * a10.y + trp0.z * a10.z;
    p1 = trp1.x * a10.x + trp1.y * a10.y + trp1.z * a10.z;
    p2 = trp2.x * a10.x + trp2.y * a10.y + trp2.z * a10.z;
    r = e0 * abs(a10.x) + e2 * abs(a10.z);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a11(f1.z, 0, -f1.x);
    p0 = trp0.x * a11.x + trp0.y * a11.y + trp0.z * a11.z;
    p1 = trp1.x * a11.x + trp1.y * a11.y + trp1.z * a11.z;
    p2 = trp2.x * a11.x + trp2.y * a11.y + trp2.z * a11.z;
    r = e0 * abs(a11.x) + e2 * abs(a11.z);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a12(f2.z, 0, -f2.x);
    p0 = trp0.x * a12.x + trp0.y * a12.y + trp0.z * a12.z;
    p1 = trp1.x * a12.x + trp1.y * a12.y + trp1.z * a12.z;
    p2 = trp2.x * a12.x + trp2.y * a12.y + trp2.z * a12.z;
    r = e0 * abs(a12.x) + e2 * abs(a12.z);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a20(-f0.y, f0.x, 0);
    p0 = trp0.x * a20.x + trp0.y * a20.y + trp0.z * a20.z;
    p1 = trp1.x * a20.x + trp1.y * a20.y + trp1.z * a20.z;
    p2 = trp2.x * a20.x + trp2.y * a20.y + trp2.z * a20.z;
    r = e0 * abs(a20.x) + e1 * abs(a20.y);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a21(-f1.y, f1.x, 0);
    p0 = trp0.x * a21.x + trp0.y * a21.y + trp0.z * a21.z;
    p1 = trp1.x * a21.x + trp1.y * a21.y + trp1.z * a21.z;
    p2 = trp2.x * a21.x + trp2.y * a21.y + trp2.z * a21.z;
    r = e0 * abs(a21.x) + e1 * abs(a21.y);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    Point a22(-f2.y, f2.x, 0);
    p0 = trp0.x * a22.x + trp0.y * a22.y + trp0.z * a22.z;
    p1 = trp1.x * a22.x + trp1.y * a22.y + trp1.z * a22.z;
    p2 = trp2.x * a22.x + trp2.y * a22.y + trp2.z * a22.z;
    r = e0 * abs(a22.x) + e1 * abs(a22.y);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r) {
        return false;
    }

    if (max(trp0.x, max(trp1.x, trp2.x)) < -e0 || min(trp0.x, min(trp1.x, trp2.x)) > e0) {
        return false;
    }

    if (max(trp0.y, max(trp1.y, trp2.y)) < -e0 || min(trp0.y, min(trp1.y, trp2.y)) > e0) {
        return false;
    }

    if (max(trp0.z, max(trp1.z, trp2.z)) < -e0 || min(trp0.z, min(trp1.z, trp2.z)) > e0) {
        return false;
    }

    return true;
}

bool Tree::is_ray_intersect(Point p1, Point p2, Cube cube, double &dist){
    Point p;
    p.x = p2.x - p1.x;
    p.y = p2.y - p1.y;
    p.z = p2.z - p1.z;
    double length = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    p.x /= length;
    p.y /= length;
    p.z /= length;

    p.x = 1 / p.x;
    p.y = 1 / p.y;
    p.z = 1 / p.z;

    float t1 = (cube.min.x - p1.x) * p.x;
    float t2 = (cube.max.x - p1.x) * p.x;
    float t3 = (cube.min.y - p1.y) * p.y;
    float t4 = (cube.max.y - p1.y) * p.y;
    float t5 = (cube.min.z - p1.z) * p.z;
    float t6 = (cube.max.z - p1.z) * p.z;

    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));


    if (tmax < 0) {
        dist = tmax;
        return false;
    }

    if (tmin > tmax) {
        dist = tmax;
        return false;
    }

    dist = tmin;

    return true;
}

void Tree::find_min_intersection(Point camera, Point screen, Triangle &tr, double &min, Node *node, double &color){
    double dist;
    if (is_ray_intersect(camera, screen, node->boundary, dist) && node->triangles.size() != 0) {
        for (size_t i = 0; i < 8; i++) {
            if (node->nodes[i] != NULL && node->nodes[i]->triangles.size() != 0) {
                if (is_ray_intersect(camera, screen, node->nodes[i]->boundary, dist) && node->nodes[i]->triangles.size() > capacity) {
                    find_min_intersection(camera, screen, tr, min, node->nodes[i], color);
                } else if (is_ray_intersect(camera, screen, node->nodes[i]->boundary, dist)) {
                    for (size_t j = 0; j < node->nodes[i]->triangles.size(); j++) {
                        Plane plane(node->nodes[i]->triangles[j]);
                        Point p = plane.getPointIntersection(camera, screen);
                        if (p.intersection(node->nodes[i]->triangles[j].p1, node->nodes[i]->triangles[j].p2, node->nodes[i]->triangles[j].p3)) {
                            double dist = Point::distance(camera, p);
                            if (min > dist) {
                                color = plane.getCos(p, Point(0, 0, 5));
                                min = dist;
                                tr = node->nodes[i]->triangles[j];
                            }
                        }
                    }
                }
            }
        }
    }
}
