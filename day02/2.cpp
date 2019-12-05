#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

int calculate(int noun, int verb, std::vector<int> input_tokens) {
    input_tokens[1] = noun;
    input_tokens[2] = verb;

    for (int pc = 0; input_tokens[pc] != 99; pc += 4) {
        int command = input_tokens[pc];
        int x = input_tokens[pc + 1];
        int y = input_tokens[pc + 2];
        int dest = input_tokens[pc + 3];
        switch (command) {
            case 1:
                input_tokens[dest] = input_tokens[x] + input_tokens[y];
                break;
            case 2:
                input_tokens[dest] = input_tokens[x] * input_tokens[y];
                break;
        }
    }
    return input_tokens[0];
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::replace(begin(input), end(input), ',', ' ');

    std::stringstream ss {input};
    std::string elem;

    std::vector<int> input_tokens;
    while (ss >> elem) {
        input_tokens.emplace_back(std::stoi(elem));
    }

    const int expected_output {19690720};

    for (int noun = 0; noun < 99; ++noun) {
        for (int verb = 0; verb < 99; ++verb) {
            if (calculate(noun, verb, input_tokens) == expected_output) {
                std::cout << 100 * noun + verb << '\n';
                return 0;
            }
        }
    }
    return 0;
}

