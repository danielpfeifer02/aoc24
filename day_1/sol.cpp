#include "../common.h"
#include <bits/stdc++.h>

using namespace std;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 1000;

int main() {
    setup_input("day_1/input.txt");
    solve_part_1();

    timeit({
    setup_input("day_1/input.txt");
    solve_part_2(false);
    }, 10000);
}

void solve_part_1(bool print) { // default print is true

    array<int32_t, input_length> left, right;

    for (int i = 0; i < input_length; i++) {
        cin >> left[i] >> right[i];
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int32_t sum = 0;
    for (int i = 0; i < input_length; i++) {
        sum += abs(left[i] - right[i]);
    }

    if (print)
        print_result<int32_t>(1, 1, sum);

}

void solve_part_2_map(bool print) { // default print is true

    unordered_map<int32_t, int32_t> right;
    array<int32_t, input_length> left;

    for (int i = 0; i < input_length; i++) {
        auto tmp_right = 0;
        cin >> left[i] >> tmp_right;
        right[tmp_right] += 1;
    }

    int32_t score = 0;

    for (int i=0; i < input_length; i++) {
        score += left[i] * right[left[i]];
    }

    if (print)
        print_result<int32_t>(1, 2, score);

}

void solve_part_2_set(bool print) { // default print is true

    unordered_multiset<int32_t> right;
    array<int32_t, input_length> left;

    for (int i = 0; i < input_length; i++) {
        auto tmp_right = 0;
        cin >> left[i] >> tmp_right;
        right.insert(tmp_right);
    }

    int32_t score = 0;

    for (int i=0; i < input_length; i++) {
        score += left[i] * right.count(left[i]);
    }

    if (print)
        print_result<int32_t>(1, 2, score);

}

void solve_part_2(bool print) { // default print is true

    // solve_part_2_map(print);
    solve_part_2_set(print);
    
}