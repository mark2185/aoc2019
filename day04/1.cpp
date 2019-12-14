#include <cstdio>
#include <string>
#include <algorithm>

bool has_doubles(const std::string& number) {
    return std::adjacent_find(std::begin(number), std::end(number)) != std::end(number);
}

bool is_rising(const std::string& number) {
    auto copy = number;
    std::sort(std::begin(copy), std::end(copy));
    return number == copy;
}

int main() {
    int lower_bound, upper_bound;
    scanf("%d-%d", &lower_bound, &upper_bound);

    int total = 0;
    for (int number = lower_bound; number <= upper_bound; ++number) {
        std::string string_number {std::to_string(number)};
        if (has_doubles(string_number) && is_rising(string_number)) {
            total++;
        }
    }

    printf("%d\n", total);
    return 0;
}
