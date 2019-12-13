#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <queue>
#include "IntcodePC.h"

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

    std::vector<IntcodePC> amplifiers;
    for (int i = 0; i < 5; ++i) {
        amplifiers.emplace_back(input_tokens);
    }

    std::vector<int> phases = {0, 1, 2, 3, 4};

    int max_signal = 0;
    std::queue<int> input_data;
    do {
        int input_value = 0;
        for (int i = 0; i < 5; ++i) {
            input_data.push(phases[i]);
            input_data.push(input_value);
            amplifiers[i].run(input_tokens, input_data, true);
            input_value = amplifiers[i].get_result();
        }
        if (amplifiers.back().get_result() > max_signal) {
            max_signal = amplifiers.back().get_result();
        }
        for_each(begin(amplifiers), end(amplifiers), [](auto& amp){ amp.reboot(); });
    } while (std::next_permutation(begin(phases), end(phases)));

    std::cout << max_signal << '\n';

    return 0;
}
