#pragma once
#include <iostream>

#pragma pack(push, 1)
class BMPHead{
  uint16_t type;
  uint32_t size;
  uint16_t reserved[2];
  uint32_t headersize;
  uint32_t infosize;
  uint32_t width;
  uint32_t height;
  uint16_t biPlanes;
  uint16_t bits;
  uint32_t biCompression;
  uint32_t biSizeImage;
  uint32_t biXPelsPerMeter;
  uint32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;

public:
  BMPHead();

  BMPHead(int, int);

  uint32_t getWidth();

  uint32_t getHeight();

  void setSize(int, int);
};
#pragma pack(pop)
