#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <array>

struct arg_modes {
    int arg1_mode {0};
    int arg2_mode {0};
    int arg3_mode {0};
    arg_modes(int m1, int m2, int m3) : arg1_mode{m1}, arg2_mode{m2}, arg3_mode{m3} {}

    int& operator[](int index) {
        switch(index) {
            case 0:
                return arg1_mode;
            case 1:
                return arg2_mode;
            case 2:
                return arg3_mode;
            default:
                return arg1_mode;
        }
    }
};

void add(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void mul(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void mov(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void print(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void jit(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void jif(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void lt(int& pc, arg_modes& modes, std::vector<int>& input_tokens);
void eq(int& pc, arg_modes& modes, std::vector<int>& input_tokens);

const std::map<int, void (*)(int&, arg_modes&, std::vector<int>&)> opcodes = {
    {1, add},
    {2, mul},
    {3, mov},
    {4, print},
    {5, jit},
    {6, jif},
    {7, lt},
    {8, eq}
};

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

    std::vector<int> input_tokens;
    while (ss >> elem) {
        input_tokens.emplace_back(std::stoi(elem));
    }

    for (int pc = 0; (input_tokens[pc] % 100) != 99;) {
        const int arg1_mode = (input_tokens[pc] %  1000) / 100;
        const int arg2_mode = (input_tokens[pc] % 10000) / 1000;
        const int arg3_mode = input_tokens[pc] / 10000;

        arg_modes modes{arg1_mode, arg2_mode, arg3_mode};

        opcodes.at(input_tokens[pc] % 100)(pc, modes, input_tokens);
    }

    return 0;
}

std::array<int, 3> get_args(int& pc, arg_modes& modes, std::vector<int>& input_tokens, int num) {
    std::array<int, 3> ret = {0, 0, 0};
    for (int i = 0; i < num; ++i) {
        ret[i] = modes[i] ? input_tokens[++pc] : input_tokens[input_tokens[++pc]];
    }
    return ret;
}

void add(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    modes[2] = 1;
    const auto [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 3);

    input_tokens[arg3] = arg1 + arg2;
    ++pc;
}

void mul(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    modes[2] = 1;
    const auto [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 3);

    input_tokens[arg3] = arg1 * arg2;
    ++pc;
}

void mov(int& pc, arg_modes&, std::vector<int>& input_tokens) {
    int val;
    std::cin >> val;

    input_tokens[input_tokens[++pc]] = val;
    ++pc;
}

void print(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    auto [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 1);
    std::cout << arg1 << '\n';
    ++pc;
}

void jit(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    const auto [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 2);

    ++pc;

    if (arg1) {
        pc = arg2;
    }
}

void jif(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    const auto [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 2);

    ++pc;
    if (!arg1) {
        pc = arg2;
    }
}

void lt(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    modes[2] = 1;
    const auto [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 3);

    input_tokens[arg3] = (arg1 < arg2) ? 1 : 0;
    ++pc;
}

void eq(int& pc, arg_modes& modes, std::vector<int>& input_tokens) {
    modes[2] = 1;
    const auto& [arg1, arg2, arg3] = get_args(pc, modes, input_tokens, 3);

    input_tokens[arg3] = (arg1 == arg2) ? 1 : 0;
    ++pc;
}
