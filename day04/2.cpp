#include <cstdio>
#include <string>
#include <algorithm>
#include <set>

bool has_only_doubles(const std::string& number) {
    int count = 1;
    std::set<char> digs;
    for (int i = 0; i < 5; ++i) {
        if (number[i] == number[i+1]) {
            count++;
            digs.insert(number[i]);
            if (count > 2) {
                digs.erase(digs.find(number[i]));
            }
        }
        else {
            count = 1;
        }
    }
    return digs.size() != 0;
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
        if (has_only_doubles(string_number) && is_rising(string_number)) {
            total++;
        }
    }

    printf("%d\n", total);
    return 0;
}
