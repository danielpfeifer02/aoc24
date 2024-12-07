#include "../common.h"
#include <bits/stdc++.h>

using namespace std;
using val_t = uint64_t;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 0;

int countDigits(int number) {
    if (number == 0) return 1; // Special case for 0
    return static_cast<int>(std::log10(std::abs(number))) + 1;
}

int main() {
    setup_input("day_7/input.txt");
    solve_part_1();

    setup_input("day_7/input.txt");
    solve_part_2();
}

void solve_part_1(bool print) { // default value for print is true

    val_t result;
    string line;
    val_t sum = 0;

    while (getline(cin, line)) {

        stringstream ss(line);

        ss >> result;
        ss.ignore(2); // Ignore ": "

        vector<val_t> v;
        val_t tmp;
        while (ss >> tmp) {
            v.push_back(tmp);
        }

        auto min = reduce(v.begin(), v.end(), 0, [](val_t a, val_t b) { return a+b; });
        auto max = reduce(v.begin(), v.end(), 1, [](val_t a, val_t b) { return a*b; });

        if (result == max || result == min) {
            sum += result;
        } else {
            assert(v.size() < 64);
            for (auto i = 0; i < 1ull<<v.size(); i++) {
                val_t tmp = v[0];
                for (auto j = 1; j < v.size(); j++) {
                    if (i & (1ull<<(v.size() - j - 1))) {
                        tmp += v[j];
                    } else {
                        tmp *= v[j];
                    }
                }
                 if (tmp == result) {
                    sum += result;
                    break;
                }
            }
           
        }
    }

    if (print) {
        print_result(7, 1, sum);
    }
}

void solve_part_2(bool print) { // default value for print is true
    
    val_t result;
    string line;
    val_t sum = 0;

    while_enter:
    while (getline(cin, line)) {

        stringstream ss(line);

        ss >> result;
        ss.ignore(2); // Ignore ": "

        vector<val_t> v;
        val_t tmp;
        while (ss >> tmp) {
            v.push_back(tmp);
        }

        auto min = reduce(v.begin(), v.end(), 0, [](val_t a, val_t b) { return a+b; });
        auto max = reduce(v.begin(), v.end(), 1, [](val_t a, val_t b) { return a*b; });

        if (result == max || result == min) {
            sum += result;
        } else {
            assert(v.size() < 64);

            for (auto i = 0; i < 1ull<<(v.size()*2); i+=2) {

                val_t tmp = v[0];
                for (auto j = 1; j < v.size(); j++) {
                    auto mask = (i >> ((v.size()-j) * 2))&0b11;

                    if (mask == 1) {
                        tmp += v[j];
                    } else if (mask == 2) {
                        tmp *= v[j];
                    } else if (mask == 3 || mask == 0) {
                        auto digits = countDigits(v[j]);
                        for (int o = 0; o < digits; o++) {
                            tmp *= 10;
                        }
                        tmp += v[j];
                    }
                }
                 if (tmp == result) {
                    sum += result;
                    goto while_enter;
                }
            }

        }
    }

    if (print) {
        print_result(7, 2, sum);
    }
}