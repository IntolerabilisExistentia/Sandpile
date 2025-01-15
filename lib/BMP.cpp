#include "BMP.h"
#include "CustomVector.h"

uint32_t BMP::DetermineColor(uint32_t color) {
  if (color > 3) {
    return 4;
  }
  return color;
}

BMP::BMP(uint32_t width, uint32_t height, vector<vector<int>>& field) 
  : width_(width), height_(height), field_(field) {}

void BMP::MakeFile(const std::string& path) {
  std::ofstream bmp;
  bmp.open(path, std::ios::out | std::ios::binary);
  if (!bmp.is_open()) {
    throw std::invalid_argument("Failed to create the file.");
  }

  int row = width_ / 2 + width_ % 2;
  int padding = (4 - (row % 4)) % 4;

  const int COLORSSIZE = sizeof(palette_);
  const int HEADERSIZE = sizeof(header_);
  const int INFOSIZE = sizeof(info_);
  const int OFFSET = COLORSSIZE + HEADERSIZE + INFOSIZE;
  const int TOTAL = (row + padding) * height_;
  const int IMAGESIZE = COLORSSIZE + HEADERSIZE + INFOSIZE + TOTAL;

  // type
  header_[0] = 'B';
  header_[1] = 'M';
  // HEADERSIZE
  header_[2] = HEADERSIZE;
  header_[3] = HEADERSIZE >> 8;
  header_[4] = HEADERSIZE >> 16;
  header_[5] = HEADERSIZE >> 24;
  // reserve 0
  header_[6] = 0;
  header_[7] = 0;
  // reserve 1
  header_[8] = 0;
  header_[9] = 0;
  // offset
  header_[10] = OFFSET;
  header_[11] = OFFSET >> 8;
  header_[12] = OFFSET >> 16;
  header_[13] = OFFSET >> 24;
  // INFOSIZE
  info_[0] = INFOSIZE;
  info_[1] = INFOSIZE >> 8;
  info_[2] = INFOSIZE >> 16;
  info_[3] = INFOSIZE >> 24;
  // width
  info_[4] = width_;
  info_[5] = width_ >> 8;
  info_[6] = width_ >> 16;
  info_[7] = width_ >> 24;
  // height
  info_[8] = height_;
  info_[9] = height_ >> 8;
  info_[10] = height_ >> 16;
  info_[11] = height_ >> 24;
  // planes
  info_[12] = 1;
  info_[13] = 0;
  // bits per pixel
  info_[14] = 4;
  info_[15] = 0;
  // compression
  info_[16] = 0;
  info_[17] = 0;
  info_[18] = 0;
  info_[19] = 0;
  // image size
  info_[20] = IMAGESIZE;
  info_[21] = IMAGESIZE >> 8;
  info_[22] = IMAGESIZE >> 16;
  info_[23] = IMAGESIZE >> 24;
  // x pixels per meter
  info_[24] = 0;
  info_[25] = 0;
  info_[26] = 0;
  info_[27] = 0;
  // y pixels per meter
  info_[28] = 0;
  info_[29] = 0;
  info_[30] = 0;
  info_[31] = 0;
  // total colors
  info_[32] = 16;
  info_[33] = 0;
  info_[34] = 0;
  info_[35] = 0;
  // important colors
  info_[36] = 5;
  info_[37] = 0;
  info_[38] = 0;
  info_[39] = 0;

  bmp.write(reinterpret_cast<char *>(header_), HEADERSIZE);
  bmp.write(reinterpret_cast<char *>(info_), INFOSIZE);
  bmp.write(reinterpret_cast<char *>(palette_), COLORSSIZE);

  uint8_t *pixels = new uint8_t[TOTAL];
  uint8_t *pixel = pixels;

  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x += 2) {
      int current1 = field_[y][x];
      int current2 = 0;
      if (x + 1 < width_) {
        current2 = field_[y][x + 1];
      }
      uint32_t color1 = DetermineColor(current1);
      uint32_t color2 = DetermineColor(current2);
      *pixel = static_cast<uint8_t>((color1 << 4) | color2);
      ++pixel;
    }
    pixel += padding;
  }

  bmp.write(reinterpret_cast<char *>(pixels), TOTAL);

  delete[] pixels;
}