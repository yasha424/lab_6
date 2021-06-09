#include "camera.h"

Camera::Camera(Point cum, Point scr, int size, double gap){
    this->center = cum;
    this->screen = scr;
    this->size = size;
    this->gap = gap;
}
