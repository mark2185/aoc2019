#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <queue>
#include <map>
#include <numeric>

#include "painting_robot.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "argument \"input_file\" missing\n";
        return 1;
    }
    std::ifstream input_file {argv[1]};
    std::string input;
    std::getline(input_file, input);
    std::replace(std::begin(input), std::end(input), ',', ' ');

    std::stringstream ss {input};
    std::string elem;

    std::vector<long> input_tokens;
    while (ss >> elem) {
        input_tokens.emplace_back(std::stol(elem));
    }

    std::map<std::pair<int, int>, COLOR> hull;

    PaintingRobot robot {input_tokens};

    std::queue<int> input_data;
    // initial turn
    {
        input_data.push(1);

        const auto tile = robot.get_location();
        robot.paint(input_data);

        hull[tile] = robot.get_brush_color();
    }

    while (!robot.is_finished()) {
        int input_value = 0;
        if (auto visited = hull.find(robot.get_location());
                visited != hull.end()) {
            input_value = static_cast<int>(visited->second);
        }

        input_data.push(input_value);

        const auto tile = robot.get_location();
        robot.paint(input_data);

        hull[tile] = robot.get_brush_color();
    }

    int start = -150;
    int   end = +150;

    for (int y = start; y < end; ++y) {
        for (int x = start; x < end; ++x) {
            if (auto white = hull.find({x, y});
                    white != hull.end()) {
                std::cout << ((white->second == COLOR::WHITE) ? '*' : ' ');
            }
        }
        std::cout << '\n';
    }
    return 0;
}
