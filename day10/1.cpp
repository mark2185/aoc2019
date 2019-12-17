#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

struct Asteroid {
    int x;
    int y;

    Asteroid(int x, int y) : x{x}, y{y} {}

    Asteroid operator-(const Asteroid& rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    bool operator==(const Asteroid& rhs) const {
        return (x == rhs.x) && (y == rhs.y);
    }

    bool operator!=(const Asteroid& rhs) const {
        return !(*this == rhs);
    }
};

int look_for_asteroids(const Asteroid& tower, const std::vector<Asteroid>& asteroids) {
    std::set<float> angles;
    for_each(begin(asteroids), end(asteroids), [&](const auto& A) {
            if (A != tower) {
                const auto diff = A - tower;
                angles.insert(atan2(diff.y, diff.x));
            }
        });
    return angles.size();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "argument \"input_file\" missing\n";
        return 1;
    }

    std::ifstream input_file {argv[1]};
    std::string line;

    std::vector<Asteroid> asteroids;
    for (int y = 0; input_file; ++y) {
        std::getline(input_file, line);
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '#') {
                asteroids.emplace_back(x, y);
            }
        }
    }

    //TODO: memoization
    Asteroid tower_location = *std::max_element(begin(asteroids), end(asteroids),
            [&asteroids](const auto& tower_a, const auto& tower_b) {
                return look_for_asteroids(tower_a, asteroids) < look_for_asteroids(tower_b, asteroids);
            });

    std::cout << look_for_asteroids(tower_location, asteroids) << '\n';
    return 0;
}
