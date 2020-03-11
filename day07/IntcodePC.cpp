#include "IntcodePC.h"
#include <iostream>

void IntcodePC::reboot() {
    pc = 0;
    relative_base = 0;
    result = 0;
    state = State::READY;
    memory.clear();
}

void IntcodePC::load_program(const std::vector<long>& program) {
    memory = program;
    memory.insert(memory.end(), 1000, 0);
}

void IntcodePC::run(std::queue<int>& input_data) {
    this->input_data.swap(input_data);
    if (state == State::PAUSED || state == State::READY) {
        state = State::RUNNING;
    }
    if (state == State::RUNNING && memory.empty()) {
        std::cerr << "No program to run!\n";
        throw;
    }
    while (state == State::RUNNING) {
        const int arg1_mode = (memory[pc] %   1000) / 100;
        const int arg2_mode = (memory[pc] %  10000) / 1000;
        const int arg3_mode = (memory[pc] % 100000) / 10000;

        std::array<int, 3> modes{arg1_mode, arg2_mode, arg3_mode};

        opcodes.at(memory[pc] % 100)(*this, modes);
    }
}

long IntcodePC::get_arg(long value, int mode) const {
    long ret_val;
    switch (mode) {
        case 0:
            ret_val = memory[value];
            break;
        case 1:
            ret_val = value;
            break;
        case 2:
            ret_val = memory[relative_base + value];
            break;
        default:
            std::cout << "Mode not supported!\n";
            throw;
    }
    return ret_val;
}

void IntcodePC::add(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);
    long arg2 = get_arg(memory[++pc], modes[1]);
    long arg3 = (modes[2]) ? memory[++pc] + relative_base : memory[++pc];

    memory[arg3] = arg1 + arg2;
    ++pc;
}

void IntcodePC::mul(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);
    long arg2 = get_arg(memory[++pc], modes[1]);
    long arg3 = (modes[2]) ? memory[++pc] + relative_base : memory[++pc];

    memory[arg3] = arg1 * arg2;
    ++pc;
}

void IntcodePC::read(const std::array<int, 3>& modes) {
    int val;

    if (!input_data.empty()) {
        val = input_data.front();
        input_data.pop();
    }
    else {
        std::cout << "Data container empty, please input\n";
        std::cin >> val;
    }

    long destination = (modes[0]) ? memory[++pc] + relative_base : memory[++pc];

    memory[destination] = val;
    ++pc;
}

void IntcodePC::print(const std::array<int, 3>& modes) {
    long source = get_arg(memory[++pc], modes[0]);

    result = source;
    std::cout << result << '\n';
    ++pc;

    state = State::PAUSED;
}

void IntcodePC::jit(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);
    long arg2 = get_arg(memory[++pc], modes[1]);

    ++pc;

    if (arg1) {
        pc = arg2;
    }
}

void IntcodePC::jif(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);
    long arg2 = get_arg(memory[++pc], modes[1]);

    ++pc;

    if (!arg1) {
        pc = arg2;
    }
}

void IntcodePC::lt(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);
    long arg2 = get_arg(memory[++pc], modes[1]);
    long arg3 = (modes[2]) ? memory[++pc] + relative_base : memory[++pc];

    memory[arg3] = (arg1 < arg2) ? 1 : 0;
    ++pc;
}

void IntcodePC::eq(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);
    long arg2 = get_arg(memory[++pc], modes[1]);
    long arg3 = (modes[2]) ? memory[++pc] + relative_base : memory[++pc];

    memory[arg3] = (arg1 == arg2) ? 1 : 0;
    ++pc;
}

void IntcodePC::offset_rb(const std::array<int, 3>& modes) {
    long arg1 = get_arg(memory[++pc], modes[0]);

    relative_base += arg1;
    ++pc;
}

void IntcodePC::halt(const std::array<int, 3>&) {
    state = State::STOPPED;
}

long IntcodePC::get_result() const {
    return result;
}

bool IntcodePC::is_finished() const {
    return state == State::STOPPED;
}
