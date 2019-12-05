#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>

struct Point {
    int x = 0;
    int y = 0;
    int dst = 0;
    Point(int x, int y, int dst = 0) : x{x}, y{y}, dst{dst}  {}
    bool operator<(const Point& p) const {
        if (x == p.x) {
            return y < p.y;
        }
        else {
            return x < p.x;
        }
    }
};

std::set<Point> install_wire(const std::string& wire) {
    std::set<Point> wire_installation;
    std::stringstream ss {wire};
    std::string elem;

    Point current {0, 0};
    int distance = 0;
    while (ss >> elem) {
        char direction = elem[0];
        int step = std::stoi(elem.substr(1));
        for (int i = 0; i < step; ++i) {
            switch (direction) {
                case 'R':
                    current.x++;
                    break;
                case 'L':
                    current.x--;
                    break;
                case 'U':
                    current.y++;
                    break;
                case 'D':
                    current.y--;
                    break;
            }
            wire_installation.insert(Point(current.x, current.y, ++distance));
        }
    }

    return wire_installation;
}


int main() {
    std::string wires[2];
    for (int i = 0; i < 2; ++i) {
        std::getline(std::cin, wires[i]);
        std::replace(std::begin(wires[i]), std::end(wires[i]), ',', ' ');
    }

    std::set<Point> wire_installation_1 = install_wire(wires[0]);
    std::set<Point> wire_installation_2 = install_wire(wires[1]);

    std::vector<Point> intersections;
    std::set_intersection(
            std::begin(wire_installation_1), std::end(wire_installation_1),
            std::begin(wire_installation_2), std::end(wire_installation_2),
            std::back_inserter(intersections));

    int min_distance = 1<<30;
    for (const auto& cross : intersections) {
        min_distance = std::min(min_distance, wire_installation_1.find(cross)->dst + wire_installation_2.find(cross)->dst);
    }

    std::cout << min_distance << '\n';
    return 0;
}
