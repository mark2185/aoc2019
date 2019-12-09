#include <iostream>
#include <algorithm>

int main() {
    const int width  = 25;
    const int height =  6;

    const int layer_size = width * height;

    int min_zeros = 1 << 30;
    int ones, twos;
    while (std::cin) {
        char buffer[layer_size] = {0};
        std::cin.get(buffer, layer_size + 1);
        if (!buffer[0]) {
            break;
        }
        if (int zeros = std::count(std::begin(buffer), std::end(buffer), '0');
                zeros < min_zeros) {
            min_zeros = zeros;
            ones  = std::count(std::begin(buffer), std::end(buffer), '1');
            twos  = std::count(std::begin(buffer), std::end(buffer), '2');
        }
    }
    std::cout << ones * twos << '\n';

    return 0;
}
