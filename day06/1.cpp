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

    std::vector<int> distances;
    std::transform(std::begin(solar_system), std::end(solar_system), std::back_inserter(distances), [&solar_system](const auto& S) { return get_distance(S.first, solar_system); });

    std::cout << std::accumulate(std::begin(distances), std::end(distances), 0) << '\n';

    return 0;
}
