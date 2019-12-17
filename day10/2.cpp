#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>
#include <cstdio>

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

int distance(const Asteroid& A, const Asteroid& B) {
    const auto diff = A - B;
    return std::abs(diff.x) + std::abs(diff.y);
}

std::ostream& operator<<(std::ostream& str, const Asteroid& A) {
    str << '(' << A.x << ", " << A.y << ')';
    return str;
}

int look_for_asteroids(const Asteroid& tower, const std::vector<Asteroid>& asteroids) {
    std::set<float> angles;
    for_each(begin(asteroids), end(asteroids), [&](const auto& A) {
            if (A != tower) {
                const auto diff = tower - A;
                angles.insert(atan2(diff.y, diff.x));
            }
        });
    return angles.size();
}

double wrap(double value, double lower_bound, double upper_bound) {
    while (value < lower_bound) {
        value += 2 * M_PI;
    }
    while (value > upper_bound) {
        value -= 2 * M_PI;
    }
    return value;
}

std::map<double, std::vector<Asteroid>> get_visible_asteroids(const Asteroid& tower, const std::vector<Asteroid> asteroid_map) {
    std::map<double, std::vector<Asteroid>> ret;
    for (const auto& asteroid : asteroid_map) {
        if (asteroid != tower) {
            const auto diff  = tower - asteroid;
            const auto angle = wrap(std::atan2(diff.y, diff.x) - 1 * M_PI/2, 0, 2 * M_PI) * 180/M_PI;
            //std::cout << "Adding angle " << angle << " for " << asteroid << '\n';
            ret[angle].push_back(asteroid);
        }
    }
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "argument \"input_file\" missing\n";
        return 1;
    }

    std::ifstream input_file {argv[1]};
    std::string line;

    std::vector<Asteroid> asteroids;
    for (int y = 0; std::getline(input_file, line); ++y) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '#') {
                asteroids.emplace_back(x, y);
            }
        }
    }

    //TODO: memoization
    Asteroid tower = *std::max_element(begin(asteroids), end(asteroids),
            [&asteroids](const auto& tower_a, const auto& tower_b) {
                return look_for_asteroids(tower_a, asteroids) < look_for_asteroids(tower_b, asteroids);
            });

    std::cout << "Part 1 = " << look_for_asteroids(tower, asteroids) << '\n';

    auto targets = get_visible_asteroids(tower, asteroids);

    auto distance_from_tower = [&tower](const Asteroid& A, const Asteroid& B) {
        return distance(tower, A) > distance(tower, B);
    };

    for (auto [angle, asteroids_on_path] : targets) {
        std::sort(begin(asteroids_on_path), end(asteroids_on_path), distance_from_tower);
    }

    const int nth_asteroid = 200;
    int counter = 0;
    while (counter < nth_asteroid) {
        for (auto it = targets.begin(); it != targets.end(); ++it) {
            if (auto asteroid_list = it->second;
                    !asteroid_list.empty()) {
                if (++counter == nth_asteroid) {
                    auto tmp = asteroid_list.back();
                    std::cout << tmp.x * 100 + tmp.y << '\n';
                    break;
                }
                asteroid_list.pop_back();
            }
        }
    }

    return 0;
}
