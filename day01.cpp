#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int part1(std::istream&& in) {
  int ret = 0;
  std::string line;
  while (std::getline(in, line)) {
    size_t p1 = line.find_first_of("0123456789");
    size_t p2 = line.find_last_of("0123456789");
    if (p1 == std::string::npos || p2 == std::string::npos) continue;
    ret += (line[p1] - '0') * 10 + (line[p2] - '0');
  }
  return ret;
}

int part2(std::istream&& in) {
  std::unordered_map<std::string, int> nums = {
    {"zero", 0}, {"0", 0},
    {"one", 1}, {"1", 1},
    {"two", 2}, {"2", 2},
    {"three", 3}, {"3", 3},
    {"four", 4}, {"4", 4},
    {"five", 5}, {"5", 5},
    {"six", 6}, {"6", 6},
    {"seven", 7}, {"7", 7},
    {"eight", 8}, {"8", 8},
    {"nine", 9}, {"9", 9},
  };

  int ret = 0;
  std::string line;
  while (std::getline(in, line)) {
    size_t p1 = line.size(), p2 = 0;
    int n1, n2;
    for (const auto& [str, num] : nums) {
      size_t pos = line.find(str);
      if (pos != std::string::npos && pos < p1) {
        p1 = pos;
        n1 = num;
      }
      pos = line.rfind(str);
      if (pos != std::string::npos && pos >= p2) {
        p2 = pos;
        n2 = num;
      }
    }
    ret += n1 * 10 + n2;
  }
  return ret;
}

int main() {
  for (auto f : {"data/day01a.txt", "data/day01b.txt", "data/day01.txt"}) {
    std::cout << "=== " << f << " ===\n";
    std::cout << "part1 = " << part1(std::ifstream(f)) << "\n";
    std::cout << "part2 = " << part2(std::ifstream(f)) << "\n";
  }
  return 0;
}
