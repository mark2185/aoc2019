#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>

struct Moon {
    int x;
    int v_x = 0;

    int y;
    int v_y = 0;

    int z;
    int v_z = 0;
    Moon(int x, int y, int z) : x{x}, y{y}, z{z} {}

    int get_kinetic_energy() const {
        return std::abs(v_x) + std::abs(v_y) + std::abs(v_z);
    }

    int get_potential_energy() const {
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    int calculate_energy() const {
        return get_kinetic_energy() * get_potential_energy();
    }
};

void attract(Moon& m1, Moon& m2) {
    if (m1.x < m2.x) {
        m1.v_x++;
        m2.v_x--;
    }
    if (m1.y < m2.y) {
        m1.v_y++;
        m2.v_y--;
    }
    if (m1.z < m2.z) {
        m1.v_z++;
        m2.v_z--;
    }
}

void apply_gravity(std::vector<Moon>& moons) {
    for (auto& m1 : moons) {
        for (auto& m2 : moons) {
            attract(m1, m2);
        }
    }
}

void apply_velocity(std::vector<Moon>& moons) {
    for (auto& m : moons) {
        m.x += m.v_x;
        m.y += m.v_y;
        m.z += m.v_z;
    }
}

long int calculate_energy(const std::vector<Moon>& moons) {
    return std::accumulate(begin(moons), end(moons), 0,
        [](int acc, const Moon& m) {
            return acc + m.calculate_energy();
        });
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "argument \"input_file\" missing\n";
        return 1;
    }
    std::ifstream input_file {argv[1]};

    std::vector<Moon> moons;
    for (int i = 0; i < 4; ++i) {
        std::string input;
        std::getline(input_file, input);

        int x, y, z;
        sscanf(input.c_str(), "<x=%d, y=%d, z=%d>", &x, &y, &z);
        moons.emplace_back(x, y, z);
    }

    for (int step = 0; step < 1000; ++step) {
        apply_gravity(moons);
        apply_velocity(moons);
    }

    std::cout << calculate_energy(moons) << '\n';

    return 0;
}
