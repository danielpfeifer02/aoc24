#include "../common.h"
#include <bits/stdc++.h>

using namespace std;
using val_t = uint64_t;

void solve(uint32_t rounds, bool print = true);

const int input_length = 0;

int main() {
    setup_input("day_11/input.txt");
    solve(25);

    setup_input("day_11/input.txt");
    solve(75);
}

uint32_t get_digit_length(val_t n) {
    uint32_t length = 0;
    while (n > 0) {
        n /= 10;
        length++;
    }
    return length;
}

pair<val_t, val_t> split(val_t n, uint32_t length) {
    val_t half = length / 2;
    val_t first = n / pow(10, half);
    val_t second = n % (val_t)pow(10, half);
    return {first, second};
}

void solve(uint32_t rounds, bool print) { // default value for print is true

    bool ping = true;
    unordered_map<val_t, val_t> nums_ping;
    unordered_map<val_t, val_t> nums_pong;

    val_t n;
    while (cin >> n) {
        nums_ping[n]++;
    }

    while (rounds > 0) {
        
        unordered_map<val_t, val_t>& current = ping ? nums_ping : nums_pong;
        unordered_map<val_t, val_t>& next = ping ? nums_pong : nums_ping;

        for (auto& num : current) {
            auto [key, count] = num;

            if (key == 0) {
                next[1] += count;
            } else {
                auto length = get_digit_length(key);
                if (length % 2 == 0) { // even
                    auto [first, second] = split(key, length);
                    next[first] += count;
                    next[second] += count;
                } else { // odd
                    next[key * 2024] += count;
                }
            }
        }

        current.clear();

        ping = !ping;
        rounds--;
    }

    val_t total = 0;

    auto& final = ping ? nums_ping : nums_pong;
    for (auto& num : final) {
        total += num.second;
    }

    if (print) {
        print_result(11, 0, total);
    }

}

void solve_part_2(bool print) { // default value for print is true

}