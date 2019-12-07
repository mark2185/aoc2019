#include <cstdio>
#include <iostream>
#include <string>

bool has_doubles(const std::string& number) {
    return false;
}

bool is_rising(const std::string& number) {

}

int main() {
    int lower_bound, upper_bound;
    scanf("%d-%d", &lower_bound, &upper_bound);

    std::cout << lower_bound << '-' << upper_bound << '\n';

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
