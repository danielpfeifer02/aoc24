#include "../common.h"
#include <bits/stdc++.h>

using namespace std;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 0;

using val_t = int;

vector<vector<val_t>> right_lines;
vector<vector<val_t>> wrong_lines;
unordered_map<val_t, set<val_t>> memory;

class Sorter {
public:
    bool operator()(const val_t& a, const val_t& b) {
        auto a_before_b = memory[a].find(b) != memory[a].end();
        auto b_before_a = memory[b].find(a) != memory[b].end();
        return a_before_b ? true : b_before_a ? false : a < b; // Last check should not matter
    }
};

int main() {
    setup_input("day_5/input.txt");
    solve_part_1();

    setup_input("day_5/input.txt");
    solve_part_2();
}

void solve_part_1(bool print) { // default value for print is true

    string line;
    val_t sum = 0;

    getline(cin, line);
    while (line.find("|") != string::npos) {
        val_t left, right;
        stringstream ss(line);
        ss >> left;
        ss.ignore(1);
        ss >> right;
        memory[left].insert(right);
        getline(cin, line);
    }

    while (getline(cin, line)) {
        stringstream ss(line);
        vector<val_t> entries, tmp;
        val_t val;
        while (ss >> val) {
            entries.push_back(val);
            tmp.push_back(val);
            ss.ignore(1);
        }
        
        bool allowed = true;
        while (tmp.size() > 0) {
            val_t right = tmp.back();
            tmp.pop_back();
            if (tmp.size() == 0) {
                break;
            }
            for (val_t left : tmp) {
                if (memory[right].find(left) != memory[right].end()) {
                    allowed = false;
                    break;
                }
            }
            if (!allowed) {
                break;
            }
        }

        if (allowed) {
            right_lines.push_back(entries);
            sum += entries[entries.size()/2];
        } else {
            wrong_lines.push_back(entries);
        }
        
    }

    if (print) {
        print_result(5, 1, sum);
    }
}

void solve_part_2(bool print) { // default value for print is true

    assert (wrong_lines.size() != 0); // Part 1 needs to be run first

    val_t sum = 0;

    for (auto& line : wrong_lines) {
        sort(line.begin(), line.end(), Sorter());
        sum += line[line.size()/2];
    }

    if (print) {
        print_result(5, 2, sum);
    }

}