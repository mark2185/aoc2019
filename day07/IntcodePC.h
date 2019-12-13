#pragma once
#include <vector>
#include <sstream>
#include <array>
#include <map>
#include <functional>
#include <queue>

enum class State {
    RUNNING, PAUSED, STOPPED
};

class IntcodePC {
private:
    /// Program Counter
    int pc = 0;

    long relative_base = 0;
    long result = 0;

    State state = State::RUNNING;

    std::queue<int> input_data;

    std::vector<long> memory;

    using fn = std::function<void(IntcodePC&, std::array<int, 3>&)>;
    const std::map<int, fn> opcodes = {
        { 1, std::mem_fn(&IntcodePC::add)},
        { 2, std::mem_fn(&IntcodePC::mul)},
        { 3, std::mem_fn(&IntcodePC::read)},
        { 4, std::mem_fn(&IntcodePC::print)},
        { 5, std::mem_fn(&IntcodePC::jit)},
        { 6, std::mem_fn(&IntcodePC::jif)},
        { 7, std::mem_fn(&IntcodePC::lt)},
        { 8, std::mem_fn(&IntcodePC::eq)},
        { 9, std::mem_fn(&IntcodePC::offset_rb)},
        {99, std::mem_fn(&IntcodePC::halt)}
    };

    void add(const std::array<int, 3>& modes);
    void mul(const std::array<int, 3>& modes);
    void read(const std::array<int, 3>& modes);
    void print(const std::array<int, 3>& modes);
    void jit(const std::array<int, 3>& modes);
    void jif(const std::array<int, 3>& modes);
    void lt(const std::array<int, 3>& modes);
    void eq(const std::array<int, 3>& modes);
    void offset_rb(const std::array<int, 3>& modes);
    void halt(const std::array<int, 3>& modes);

    long get_arg(long value, int mode);

public:
    IntcodePC() = default;

    void run(std::queue<int>& input_data);
    void load_program(const std::vector<long>& program);
    long get_result() const;

    void reboot();
};
