#include <iostream>
#include <numeric>
#include <iterator>

int main() {
    auto func = [](int x, int y) {
        int sum = 0;
        for (y = y/3 - 2; y > 0; y = y / 3 - 2) {
            sum += y;
        }
        return x + sum;
    };
    std::cout << std::accumulate(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), 0, func) << '\n';
}
