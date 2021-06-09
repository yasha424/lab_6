#pragma once
#include "bmphead.h"
#include "pixel.h"
#include <iostream>
#include <vector>
#include <string>

class Image{
public:
    BMPHead head;
    vector <vector <Pixel>> pixels;

    Image(){}

    Image(int, int, vector <vector <Pixel>>);

    void write(const char*);
};
