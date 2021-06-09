#include "image.h"
using namespace std;

Image::Image(int height, int width, vector <vector <Pixel>> pixels){
    this->head.setSize(height, width);
    this->pixels = pixels;
}

void Image::write(const char *path){
    FILE *out = fopen(path, "w");

    fwrite(&head, sizeof(BMPHead), 1, out);

    int padding = (4 - head.getWidth() * sizeof(Pixel) % 4) % 4;

    for (size_t i = 0; i < head.getHeight(); i++) {
        for (size_t j = 0; j < head.getWidth(); j++) {
            fwrite(&pixels[i][j], sizeof(Pixel), 1, out);
        }

        for (size_t k = 0; k < padding; k++) {
            fputc(0x00, out);
        }

    }
}
