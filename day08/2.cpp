#include <iostream>
#include <algorithm>

int main() {
    const int width  = 25;
    const int height =  6;

    const int layer_size = width * height;

    char first_layer[layer_size + 1] = {0};
    std::cin.get(first_layer, layer_size + 1);
    while (std::cin) {
        char buffer[layer_size + 1] = {0};
        std::cin.get(buffer, layer_size + 1);
        if (!buffer[0]) {
            break;
        }
        for (int i = 0; i < layer_size; ++i) {
            if (first_layer[i] == '2') {
                first_layer[i] = buffer[i];
            }
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << ((first_layer[i * width + j] == '1') ? '*' : ' ');
        }
        std::cout << '\n';
    }

    return 0;
}
