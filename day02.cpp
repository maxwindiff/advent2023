#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"

#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

struct Cubes {
  int num;
  std::string color;
};
struct Game {
  int id;
  std::vector<std::vector<Cubes>> observations;
};

std::vector<Game> parse(std::istream &&in) {
  const std::regex game_re("Game (\\d+): ");
  const std::regex cubes_re("(\\d+) (\\w+)");

  std::vector<Game> ret;
  std::string line;
  while (std::getline(in, line)) {
    Game game;

    std::smatch match;
    if (!std::regex_search(line, match, game_re)) {
      continue;
    }
    game.id = std::stoi(match[1]);

    for (auto &obs : absl::StrSplit(line.substr(match.length()), "; ")) {
      std::vector<Cubes> results;
      for (auto &cubes : absl::StrSplit(obs, ", ")) {
        std::string tmp(cubes);
        if (!std::regex_search(tmp, match, cubes_re)) {
          continue;
        }
        results.push_back({
            .num = std::stoi(match[1]),
            .color = match[2],
        });
      }
      game.observations.push_back(results);
    }

    ret.push_back(game);
  }
  return ret;
}

int part1(const std::vector<Game> &games) {
  std::unordered_map<std::string, int> limits = {
      {"red", 12}, {"green", 13}, {"blue", 14}};

  int ret = 0;
  for (auto &game : games) {
    bool failed = false;
    for (auto &observation : game.observations) {
      for (auto &cubes : observation) {
        if (cubes.num > limits[cubes.color]) {
          failed = true;
          break;
        }
      }
    }
    if (!failed) {
      ret += game.id;
    }
  }
  return ret;
}

int part2(const std::vector<Game> &games) {
  int ret = 0;
  for (auto &game : games) {
    std::unordered_map<std::string, int> minimums;
    for (auto &observation : game.observations) {
      for (auto &cubes : observation) {
        if (cubes.num > minimums[cubes.color]) {
          minimums[cubes.color] = cubes.num;
        }
      }
    }
    ret += minimums["red"] * minimums["green"] * minimums["blue"];
  }
  return ret;
}

int main() {
  for (auto f : {"data/day02a.txt", "data/day02.txt"}) {
    absl::PrintF("=== %s ===\n", f);

    std::vector<Game> games(parse(std::ifstream(f)));
    absl::PrintF("part1 = %d\n", part1(games));
    absl::PrintF("part2 = %d\n", part2(games));
  }
  return 0;
}
