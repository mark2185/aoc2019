#pragma once
#include <vector>
#include <sstream>
#include <array>
#include <map>
#include <functional>

class IntcodePC {
private:
    int pc = 0;
    int relative_base = 0;
    long result = 0;
    std::stringstream input_data;

    void add(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void mul(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void mov(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void print(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void jit(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void jif(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void lt(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void eq(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);
    void offset_rb(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens);


    std::array<int, 3> get_args(int& pc, std::array<int, 3>& modes, std::vector<long>& input_tokens, int num);

    long get_arg(long value, int mode, const std::vector<long>& input_tokens);

    using fn = std::function<void(IntcodePC&, int&, std::array<int, 3>&, std::vector<long>&)>;
    const std::map<int, fn> opcodes = {
        {1, std::mem_fn(&IntcodePC::add)},
        {2, std::mem_fn(&IntcodePC::mul)},
        {3, std::mem_fn(&IntcodePC::mov)},
        {4, std::mem_fn(&IntcodePC::print)},
        {5, std::mem_fn(&IntcodePC::jit)},
        {6, std::mem_fn(&IntcodePC::jif)},
        {7, std::mem_fn(&IntcodePC::lt)},
        {8, std::mem_fn(&IntcodePC::eq)},
        {9, std::mem_fn(&IntcodePC::offset_rb)}
    };

public:
    void run(std::vector<long> instructions, std::stringstream& input_data);
    void reboot();
};
