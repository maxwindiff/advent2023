#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"

#include <fstream>
#include <regex>
#include <string>
#include <vector>

struct Sym {
  int r, c;
  char val;
};
struct Num {
  int r, c, len, val;

  bool IsAdj(const Sym &sym) const {
    return (sym.r >= r - 1) && (sym.r <= r + 1) && (sym.c >= c - 1) &&
           (sym.c <= c + len); // (c + len - 1) + 1
  }
};
struct Board {
  std::vector<Num> nums;
  std::vector<Sym> syms;
};

Board parse(std::istream &&in) {
  const std::regex num_re("(\\d)+");

  Board board;
  std::string line;
  int row = 0;
  while (std::getline(in, line)) {
    for (std::sregex_iterator i =
             std::sregex_iterator(line.begin(), line.end(), num_re);
         i != std::sregex_iterator(); ++i) {
      board.nums.push_back({.r = row,
                            .c = static_cast<int>(i->position()),
                            .len = static_cast<int>(i->length()),
                            .val = std::stoi(i->str())});
    }

    for (int c = 0; c < line.size(); ++c) {
      if (line[c] != '.' && (line[c] < '0' || line[c] > '9')) {
        board.syms.push_back({.r = row, .c = c, .val = line[c]});
      }
    }
    ++row;
  }
  return board;
}

int part1(const Board &board) {
  int ret = 0;
  for (const Num &num : board.nums) {
    bool found = false;
    for (const Sym &sym : board.syms) {
      if (num.IsAdj(sym)) {
        found = true;
        break;
      }
    }
    if (found) {
      ret += num.val;
    }
  }
  return ret;
}

int part2(const Board &board) {
  int ret = 0;
  for (const Sym &sym : board.syms) {
    if (sym.val != '*') {
      continue;
    }

    int count = 0;
    int ratio = 1;
    for (const Num &num : board.nums) {
      if (num.IsAdj(sym)) {
        if (++count > 2) {
          break;
        }
        ratio *= num.val;
      }
    }
    if (count == 2) {
      ret += ratio;
    }
  }
  return ret;
}

int main() {
  for (auto f : {"data/day03a.txt", "data/day03.txt"}) {
    absl::PrintF("=== %s ===\n", f);
    auto board = parse(std::fstream(f));

    absl::PrintF("part1 = %d\n", part1(board));
    absl::PrintF("part2 = %d\n", part2(board));
  }
  return 0;
}
