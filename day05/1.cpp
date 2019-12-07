#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>

struct arg_modes {
    int arg1_mode {0};
    int arg2_mode {0};
    int arg3_mode {0};
    arg_modes(int m1, int m2, int m3) : arg1_mode{m1}, arg2_mode{m2}, arg3_mode{m3} {}
};

void add(int& pc, const arg_modes& modes, std::vector<int>& input_tokens);
void mul(int& pc, const arg_modes& modes, std::vector<int>& input_tokens);
void mov(int& pc, const arg_modes& modes, std::vector<int>& input_tokens);
void print(int& pc, const arg_modes& modes, std::vector<int>& input_tokens);

const std::map<int, void (*)(int&, const arg_modes&, std::vector<int>&)> opcodes = {
    {1, add},
    {2, mul},
    {3, mov},
    {4, print}
};

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

    for (int pc = 0; (input_tokens[pc] % 100) != 99; ++pc) {
        const int arg1_mode = (input_tokens[pc] %  1000) / 100;
        const int arg2_mode = (input_tokens[pc] % 10000) / 1000;
        const int arg3_mode = input_tokens[pc] / 10000;

        const arg_modes modes{arg1_mode, arg2_mode, arg3_mode};

        opcodes.at(input_tokens[pc] % 100)(pc, modes, input_tokens);
    }

    return 0;
}

void add(int& pc, const arg_modes& modes, std::vector<int>& input_tokens) {
    const int arg1 = modes.arg1_mode ? input_tokens[++pc] : input_tokens[input_tokens[++pc]];
    const int arg2 = modes.arg2_mode ? input_tokens[++pc] : input_tokens[input_tokens[++pc]];
    const int arg3 = input_tokens[++pc];

    input_tokens[arg3] = arg1 + arg2;
}

void mul(int& pc, const arg_modes& modes, std::vector<int>& input_tokens) {
    const int arg1 = modes.arg1_mode ? input_tokens[++pc] : input_tokens[input_tokens[++pc]];
    const int arg2 = modes.arg2_mode ? input_tokens[++pc] : input_tokens[input_tokens[++pc]];
    const int arg3 = input_tokens[++pc];

    input_tokens[arg3] = arg1 * arg2;
}

void mov(int& pc, const arg_modes&, std::vector<int>& input_tokens) {
    const int val = 1;

    input_tokens[input_tokens[++pc]] = val;
}

void print(int& pc, const arg_modes& modes, std::vector<int>& input_tokens) {
    int arg1 = modes.arg1_mode ? input_tokens[++pc] : input_tokens[input_tokens[++pc]];
    std::cout << arg1 << '\n';
}
