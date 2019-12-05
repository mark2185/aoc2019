#include <iostream>
#include <numeric>
#include <iterator>

int main() {
    std::cout << std::accumulate(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), 0, [](int x, int y) { return x + y / 3 - 2; }) << '\n';
}
