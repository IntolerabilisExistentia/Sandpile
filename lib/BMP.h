#pragma once
#include <fstream>
#include <cstdint>
#include "CustomVector.h"

class BMP {
public:

  BMP(uint32_t width, uint32_t height, vector<vector<int>>& field);

  ~BMP() = default;

  void MakeFile(const std::string& path);

  uint32_t DetermineColor(uint32_t color);

private:
  uint32_t width_;
  uint32_t height_;
  vector<vector<int>> field_;
  uint8_t header_[14];
  uint8_t info_[40];
  uint32_t palette_[16] = {
    0x00ffffff,
    0x004caf50,
    0x00ffc107,
    0x009c27b0,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000
  };
};