#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "../day07/IntcodePC.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "argument \"input_file\" missing\n";
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
    for (int i = 0; i < 1000; ++i) {
        input_tokens.emplace_back(0);
    }

    std::stringstream input_data;


    // part 1
    IntcodePC sensor_boost;
    input_data << 1;
    sensor_boost.run(input_tokens, input_data);
    // part 2
    sensor_boost.reboot();
    input_data << 2;
    sensor_boost.run(input_tokens, input_data);

    return 0;
}
