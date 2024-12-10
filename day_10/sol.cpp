#include "../common.h"
#include <bits/stdc++.h>

using namespace std;
using val_t = uint8_t;

class PairHash {
public:
    int operator()(const pair<uint32_t, uint32_t>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

void solve(bool print = true);

const int input_length = 0;
const int ROWLEN = 52;

template <template <typename...> class T>
void step(uint32_t row, uint32_t col, vector<vector<val_t>>& input, 
          T<pair<uint32_t, uint32_t>, PairHash>& output, uint32_t height) {

    if (row >= input.size() || col >= ROWLEN || input[row][col] != height) {
        return;
    }

    if (height == 9) {
        output.insert(make_pair(row, col));
        return;
    } else {
        step<T>(row - 1, col, input, output, height + 1);
        step<T>(row + 1, col, input, output, height + 1);
        step<T>(row, col - 1, input, output, height + 1);
        step<T>(row, col + 1, input, output, height + 1);
    }
}

int main() {
    setup_input("day_10/input.txt");
    solve();
}

void solve(bool print) { // default value for print is true

    vector<vector<val_t>> input;
    vector<pair<uint32_t, uint32_t>> starting_points;
    val_t val;
    uint32_t row_ctr = 0, col_ctr = 0;
    
    vector<val_t> current_group;
    while (cin >> val) {
        if (val == '0') {
            starting_points.push_back(make_pair(row_ctr, col_ctr));
        }

        current_group.push_back(val-'0');
        col_ctr++;
        if (col_ctr == ROWLEN) {
            col_ctr = 0;
            row_ctr++;
            input.push_back(current_group);
            current_group.clear();
        }
    }

    unordered_set<pair<uint32_t, uint32_t>, PairHash> out_part_1;
    uint32_t total_part_1 = 0;
    unordered_multiset<pair<uint32_t, uint32_t>, PairHash> out_part_2;
    uint32_t total_part_2 = 0;
    for (auto &e : starting_points) {
        out_part_1.clear();
        out_part_2.clear();
        
        step<unordered_set>(e.first, e.second, input, out_part_1, 0);
        step<unordered_multiset>(e.first, e.second, input, out_part_2, 0);

        total_part_1 += out_part_1.size();
        total_part_2 += out_part_2.size();
    }

    if (print) {
        print_result(10, 1, total_part_1);
        print_result(10, 2, total_part_2);
    }
}