#include <cstdint>
#include <fstream>
#include "CustomVector.h"


class Sandpile {
public:

  Sandpile(std::string& tsv, int iter, int freq);

  ~Sandpile() = default;

  void CreateField();

  void Collapse(std::string& path);

  void Iteration();

  int GetWidth();

  int GetHeight();

  vector<vector<int>>& GetField();

  std::string& GetTsv();

private:
  std::string tsv_;
  uint32_t width_;
  uint32_t height_;
  uint32_t iterations_;
  uint32_t frequency_;
  vector<vector<int>> coords_;
  vector<vector<int>> field_;
};