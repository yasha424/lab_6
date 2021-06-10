#include "tree.h"

Node::Node(Cube boundary, vector<Triangle> triangles){
    this->boundary = boundary;
    this->triangles = triangles;
    URF = ULF = URB = ULB = DRF = DLF = DRB = DLB = NULL;
}

Tree::Tree(Cube boundary, vector<Triangle> triangles){
    root = new Node(boundary, triangles);

}

void Tree::make_tree(Node *node){
    Point center((root->boundary.max.x + root->boundary.min.x) / 2,
                 (root->boundary.max.y + root->boundary.min.y) / 2,
                 (root->boundary.max.z + root->boundary.min.z) / 2);

    vector <Cube> boundaries;
    boundaries.push_back(Cube(root->boundary.min, center));
    boundaries.push_back(Cube(center, root->boundary.max));

    Point p1(center.x, root->boundary.min.y, root->boundary.min.z);
    Point p11(root->boundary.max.x, center.y, center.z);
    boundaries.push_back(Cube(p1, p11));

    Point p2(root->boundary.min.x, center.y, root->boundary.min.z);
    Point p22(center.x, root->boundary.max.y, center.z);
    boundaries.push_back(Cube(p2, p22));

    Point p3(root->boundary.min.x, root->boundary.min.y, center.z);
    Point p33(center.x, center.y, root->boundary.max.z);
    boundaries.push_back(Cube(p3, p33));

    Point p4(center.x, center.y, root->boundary.min.z);
    Point p44(root->boundary.max.x, root->boundary.max.y, center.z);
    boundaries.push_back(Cube(p4, p44));

    Point p5(center.x, root->boundary.min.y, center.z);
    Point p55(root->boundary.max.x, center.y, root->boundary.max.z);
    boundaries.push_back(Cube(p5, p55));

    Point p6(root->boundary.min.x, center.y, center.z);
    Point p66(center.x, root->boundary.max.y, root->boundary.max.z);
    boundaries.push_back(Cube(p6, p66));

    for (size_t i = 0; i < boundaries.size(); i++) {
        vector <Triangle> trs;
        for (size_t j = 0; j < root->triangles.size(); j++) {
            if (is_triangle_in(boundaries[i], root->triangles[j])) {
                trs.push_back(root->triangles[j]);
            }
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
