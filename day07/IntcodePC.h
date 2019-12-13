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
    int pc = 0;
    int relative_base = 0;
    State state = State::RUNNING;
    long result = 0;
    std::queue<int> input_data;

    std::vector<long> instructions;

    using fn = std::function<void(IntcodePC&, int&, std::array<int, 3>&, std::vector<long>&)>;
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

    void add(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void mul(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void read(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void print(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void jit(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void jif(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void lt(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void eq(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void offset_rb(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void halt(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);

    long get_arg(long value, int mode, const std::vector<long>& input_tokens);

public:
    IntcodePC() = default;
    IntcodePC(const std::vector<long>& instructions);
    void run(std::stringstream& input_data);
    void run(std::vector<long> instructions, std::queue<int>& input_data, bool use_states = false);
    long get_result() const;

    void reboot();
};
