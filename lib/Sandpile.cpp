#include "Sandpile.h"
#include "BMP.h"


int ToInt(const vector<char>& str) {
  int length = str.size();
  int multiplier = 1;
  int result = 0;
  for (int i = length - 1; i >= 0; --i) {
    result += (str[i] - '0') * multiplier;
    multiplier *= 10;
  }
  return result;
}

Sandpile::Sandpile(std::string& tsv, int iter, int freq) : 
  tsv_(tsv), iterations_(iter), frequency_(freq) {}

void Sandpile::CreateField() {
  std::ifstream file(tsv_);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open the file."); 
  }
  int maxX = 0;
  int maxY = 0;
  std::ifstream map(tsv_);
  char lineBuffer[256];

  while (map.getline(lineBuffer, 256,  '\n')) {
    vector<char> charBuffer;
    vector<int> vec;
    for (char currrentChar : lineBuffer) {
      if (currrentChar == '\0') {
        vec.pushback(ToInt(charBuffer));
        charBuffer.clear();
        coords_.pushback(vec);
        if (vec[0] > maxX) {
          maxX = vec[0];
        }
        if (vec[1] > maxY) {
          maxY = vec[1];
        }
        vec.clear();
        break;
      }
      if (currrentChar != '\t') {
        charBuffer.pushback(currrentChar);
      } else {
        vec.pushback(ToInt(charBuffer));
        charBuffer.clear();
      }
    }
  }

  height_ = (maxY + 1);
  width_ = (maxX + 1);

  for (int i = 0; i < height_; ++i) {
    field_.pushback(vector<int>(width_));
  }

  for (int i = 0; i < coords_.size(); ++i) {
    field_[coords_[i][1]][coords_[i][0]] = coords_[i][2];
  }
}

vector<vector<int>> &Sandpile::GetField() {
  return field_;
}

std::string &Sandpile::GetTsv() {
  return tsv_;
}

void Sandpile::Collapse(std::string& path) {
  for (int i = 1; i <= iterations_; ++i) {
    Iteration();
    if(frequency_ != 0) {
      if (i % frequency_ == 0) {
        BMP bmp(width_, height_, field_);
        std::string name = path + std::to_string(i) + ".bmp";
        bmp.MakeFile(name);
      }
    } else {
      if (i == iterations_) {
        BMP bmp(width_, height_, field_);
        std::string name = path + std::to_string(i) + ".bmp";
        bmp.MakeFile(name);
      }
    }
  }
}

void Sandpile::Iteration() {
  height_ = field_.size();
  width_ = field_[0].size();

  vector<std::pair<int, int>> cells;

  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      if (field_[y][x] > 3) {
        if (y - 1 < 0) { // upper overflow
          field_.insert(vector<int>(width_));
          ++height_;
          ++y;
          for (int i = 0; i < cells.size(); ++i) {
            cells[i].first++;
          }
        }
        if (y + 1 == height_) { // lower overflow
          field_.pushback(vector<int>(width_));
          ++height_;
        }
        if (x - 1 < 0) { // left overflow
          for (int i = 0; i < height_; ++i) {
            field_[i].insert(0);
          }
          ++width_;
          ++x;
          for (int i = 0; i < cells.size(); ++i) {
            ++cells[i].second;
          }
        }
        if (x + 1 == width_) { // right overflow
          for (int i = 0; i < height_; ++i) {
            field_[i].pushback(0);
          }
          ++width_;
        }
        cells.pushback({y, x});
      }
    }
  }

  for (int i = 0; i < cells.size(); ++i) {
    std::pair<int, int> curr = cells[i];
    field_[curr.first][curr.second] -= 4;
    ++field_[curr.first - 1][curr.second];
    ++field_[curr.first + 1][curr.second];
    ++field_[curr.first][curr.second - 1];
    ++field_[curr.first][curr.second + 1];
  }

  cells.clear();
}

int Sandpile::GetWidth() {
  return width_;
}

int Sandpile::GetHeight() {
  return height_;
}