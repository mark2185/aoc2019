#include "IntcodePC.h"
#include <iostream>

void IntcodePC::reboot() {
    pc = 0;
    relative_base = 0;
    result = 0;
}

IntcodePC::IntcodePC(const std::vector<long>& instructions) : instructions{instructions} {
}

/*
void IntcodePC::run(std::queue<int>& input_stream) {
    input_data = input_stream;
    while (state == State::RUNNING) {
        const int arg1_mode = (instructions[pc] %   1000) / 100;
        const int arg2_mode = (instructions[pc] %  10000) / 1000;
        const int arg3_mode = (instructions[pc] % 100000) / 10000;

        std::array<int, 3> modes{arg1_mode, arg2_mode, arg3_mode};

        opcodes.at(instructions[pc] % 100)(*this, pc, modes, instructions);
    }
}
*/

void IntcodePC::run(std::vector<long> instructions, std::queue<int>& input_data, bool use_states) {
    this->input_data.swap(input_data);
    if (state == State::PAUSED) {
        state = State::RUNNING;
    }
    while (state == State::RUNNING) {
        const int arg1_mode = (instructions[pc] %   1000) / 100;
        const int arg2_mode = (instructions[pc] %  10000) / 1000;
        const int arg3_mode = (instructions[pc] % 100000) / 10000;

        std::array<int, 3> modes{arg1_mode, arg2_mode, arg3_mode};

        opcodes.at(instructions[pc] % 100)(*this, pc, modes, instructions);
    }
}

long IntcodePC::get_arg(long value, int mode, const std::vector<long>& input_tokens) {
    long ret_val;
    switch (mode) {
        case 0:
            ret_val = input_tokens[value];
            break;
        case 1:
            ret_val = value;
            break;
        case 2:
            ret_val = input_tokens[relative_base + value];
            break;
        default:
            std::cout << "Mode not supported!\n";
            throw;
    }
    return ret_val;
}

void IntcodePC::add(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);
    long arg2 = get_arg(input_tokens[++pc], modes[1], input_tokens);
    long arg3 = (modes[2]) ? input_tokens[++pc] + relative_base : input_tokens[++pc];

    input_tokens[arg3] = arg1 + arg2;
    ++pc;
}

void IntcodePC::mul(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);
    long arg2 = get_arg(input_tokens[++pc], modes[1], input_tokens);
    long arg3 = (modes[2]) ? input_tokens[++pc] + relative_base : input_tokens[++pc];

    input_tokens[arg3] = arg1 * arg2;
    ++pc;
}

void IntcodePC::read(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    int val = input_data.front();
    input_data.pop();

    long destination = (modes[0]) ? input_tokens[++pc] + relative_base : input_tokens[++pc];

    input_tokens[destination] = val;
    ++pc;
}

void IntcodePC::print(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long source = get_arg(input_tokens[++pc], modes[0], input_tokens);

    result = source;
    std::cout << result << '\n';
    ++pc;

    state = State::PAUSED;
}

void IntcodePC::jit(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);
    long arg2 = get_arg(input_tokens[++pc], modes[1], input_tokens);

    ++pc;

    if (arg1) {
        pc = arg2;
    }
}

void IntcodePC::jif(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);
    long arg2 = get_arg(input_tokens[++pc], modes[1], input_tokens);

    ++pc;

    if (!arg1) {
        pc = arg2;
    }
}

void IntcodePC::lt(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);
    long arg2 = get_arg(input_tokens[++pc], modes[1], input_tokens);
    long arg3 = (modes[2]) ? input_tokens[++pc] + relative_base : input_tokens[++pc];

    input_tokens[arg3] = (arg1 < arg2) ? 1 : 0;
    ++pc;
}

void IntcodePC::eq(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);
    long arg2 = get_arg(input_tokens[++pc], modes[1], input_tokens);
    long arg3 = (modes[2]) ? input_tokens[++pc] + relative_base : input_tokens[++pc];

    input_tokens[arg3] = (arg1 == arg2) ? 1 : 0;
    ++pc;
}

void IntcodePC::offset_rb(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens) {
    long arg1 = get_arg(input_tokens[++pc], modes[0], input_tokens);

    relative_base += arg1;
    ++pc;
}

long IntcodePC::get_result() const {
    return result;
}

void IntcodePC::halt(int&, std::array<int, 3>&, std::vector<long>&) {
    state = State::STOPPED;
}
