#include "bmphead.h"

BMPHead::BMPHead(){
  type = 19778;
  size = 54;
  reserved[0] = 0;
  reserved[1] = 0;
  headersize = 54;
  infosize = 40;
  width = 0;
  height = 0;
  biPlanes = 1;
  bits = 24;
  biCompression = 0;
  biSizeImage = 12742;
  biXPelsPerMeter = 2834;
  biYPelsPerMeter = 2834;
  biClrUsed = 0;
  biClrImportant = 0;
}

BMPHead::BMPHead(int height, int width){
  this->type = 19778;
  int padding = (4 - ((width * 3) % 4)) % 4;
  this->size = 54 + height * width * 3 + padding * height;
  this->reserved[0] = 0;
  this->reserved[1] = 0;
  this->headersize = 54;
  this->infosize = 40;
  this->width = width;
  this->height = height;
  this->biPlanes = 1;
  this->bits = 24;
  this->biCompression = 0;
  this->biSizeImage = 12742;
  this->biXPelsPerMeter = 2834;
  this->biYPelsPerMeter = 2834;
  this->biClrUsed = 0;
  this->biClrImportant = 0;
}

uint32_t BMPHead::getWidth(){
  return width;
}

uint32_t BMPHead::getHeight(){
  return height;
}

void BMPHead::setSize(int height, int width){
  this->width = width;
  this->height = height;
  int padding = (4 - ((width * 3) % 4)) % 4;
  this->size = 54 + height * width * 3 + padding * height;
}
