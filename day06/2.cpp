#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>

int get_distance(const std::string& s, const std::map<std::string, std::string>& solar_system) {
    if (auto val = solar_system.find(s)->second;
             val.empty()) {
        return 0;
    } else {
        return 1 + get_distance(val, solar_system);
    }
}

std::vector<std::string> get_path(const std::string& star, const std::map<std::string, std::string>& solar_system) {
    std::vector<std::string> ret;
    if (auto val = solar_system.find(star)->second;
             !val.empty()) {
        auto path = get_path(val, solar_system);
        std::copy(std::begin(path), std::end(path), std::back_inserter(ret));
        ret.push_back(val);
    }
    return ret;
}

int main() {
    std::string line;
    std::map<std::string, std::string> solar_system;
    while (std::getline(std::cin, line)) {
        std::replace(std::begin(line), std::end(line), ')', ' ');
        std::stringstream ss {line};

        std::string star, satellite;
        ss >> star >> satellite;
        solar_system[star];
        solar_system[satellite] = star;
    }

    const auto me    = solar_system.find("YOU")->second;
    const auto santa = solar_system.find("SAN")->second;

    const auto my_path     = get_path(me, solar_system);
    const auto santas_path = get_path(santa, solar_system);

    const auto [my_branch, santas_branch] = std::mismatch(std::begin(my_path), std::end(my_path), std::begin(santas_path));

    const auto my_distance_from_crossroads     = std::distance(my_branch,     std::end(my_path)) + 1;
    const auto santas_distance_from_crossroads = std::distance(santas_branch, std::end(santas_path)) + 1;

    std::cout << my_distance_from_crossroads + santas_distance_from_crossroads << '\n';

    return 0;
}
