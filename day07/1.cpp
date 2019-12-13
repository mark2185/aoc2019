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

    std::vector<IntcodePC> amplifiers(5);
    std::vector<int> phases = {0, 1, 2, 3, 4};

    long max_signal = 0;
    std::queue<int> input_data;
    do {
        int input_value = 0;
        for (int i = 0; i < 5; ++i) {
            input_data.push(phases[i]);
            input_data.push(input_value);

            amplifiers[i].load_program(input_tokens);
            amplifiers[i].run(input_data);

            input_value = amplifiers[i].get_result();
        }
        max_signal = std::max(max_signal, amplifiers.back().get_result());
        for_each(begin(amplifiers), end(amplifiers),
            [](auto& amp) {
                amp.reboot();
            });
    } while (std::next_permutation(begin(phases), end(phases)));

    std::cout << max_signal << '\n';

    return 0;
}
