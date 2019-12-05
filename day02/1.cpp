#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::replace(std::begin(input), std::end(input), ',', ' ');

    std::stringstream ss {input};
    std::string elem;

    std::vector<int> input_tokens;
    while (ss >> elem) {
        input_tokens.emplace_back(std::stoi(elem));
    }
    input_tokens[1] = 12;
    input_tokens[2] = 2;
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
    std::cout << input_tokens[0] << '\n';

    return 0;
}
