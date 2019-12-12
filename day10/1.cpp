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
};

int look_for_asteroids(const Asteroid& tower, const std::vector<Asteroid>& asteroids) {
    std::set<float> angles;
    for_each(begin(asteroids), end(asteroids), [&](const auto& A) {
            const auto diff = A - tower;
            angles.insert(atan2(diff.y, diff.x));
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

    std::vector<int> visible_asteroids;
    std::transform(begin(asteroids), end(asteroids), back_inserter(visible_asteroids), [&asteroids](const auto& tower) { return look_for_asteroids(tower, asteroids);});

    std::cout << *std::max_element(begin(visible_asteroids), end(visible_asteroids)) << '\n';
    return 0;
}
