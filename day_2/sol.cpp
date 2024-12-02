#include "../common.h"
#include <bits/stdc++.h>

using namespace std;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 1000;

int main() {
    setup_input("day_2/input.txt");
    solve_part_1();

    setup_input("day_2/input.txt");
    solve_part_2();
}

using elem_t = int;

const auto is_safe = [](vector<elem_t> &vec) { return   all_of(vec.begin(), vec.end(), [](elem_t e) { return (e >= 1 && e <= 3); }) || 
                                                        all_of(vec.begin(), vec.end(), [](elem_t e) { return (e >= -3 && e <= -1); });};

void solve_part_1(bool print) { // default value for print is true

    uint16_t safe_ctr = 0;
    string line;
    
    vector<elem_t> line_vec;
    line_vec.reserve(20);

    for (int i = 0; i < input_length; i++) {
        getline(cin, line);
        istringstream is(line);
        elem_t n;

        while( is >> n ) {
            line_vec.push_back(n);
        }

        adjacent_difference(line_vec.begin(), line_vec.end(), line_vec.begin());
        line_vec[0] = line_vec[1]; // First element will stay first element so we need to set it to a value that does not affect the result

        if (is_safe(line_vec)) {
            safe_ctr++;
        }

        line_vec.clear();
    }

    if (print) {
        print_result(2, 1, safe_ctr);
    }
}

void solve_part_2(bool print) { // default value for print is true
    
    uint16_t safe_ctr = 0;
    string line;
    
    vector<elem_t> line_vec, line_vec_2, line_vec_3;
    line_vec.reserve(20);
    line_vec_2.reserve(20);
    line_vec_3.reserve(20);

    for (int i = 0; i < input_length; i++) {
        getline(cin, line);
        istringstream is(line);
        elem_t n;

        while( is >> n ) {
            line_vec.push_back(n);
        }

        adjacent_difference(line_vec.begin(), line_vec.end(), line_vec.begin());
        line_vec.erase(line_vec.begin()); // since the first element after adjacent_difference is the same as the first element before

        if (is_safe(line_vec)) {
            safe_ctr++;
        } else {

            auto max_min_elem = minmax_element(line_vec.begin(), line_vec.end());
            auto max_min_index = {distance(line_vec.begin(), max_min_elem.first), distance(line_vec.begin(), max_min_elem.second)};

            for (auto cur_index : max_min_index) {
                line_vec_2 = line_vec;
                line_vec_3 = line_vec;
                if (cur_index == 0) {
                    line_vec_3[cur_index + 1] = line_vec_3[cur_index + 1] + line_vec_3[cur_index];
                } else if ((long unsigned int)cur_index == line_vec_2.size() - 1) {
                    line_vec_2[cur_index - 1] = line_vec_2[cur_index - 1] + line_vec_2[cur_index];
                } else {
                    line_vec_2[cur_index - 1] = line_vec_2[cur_index - 1] + line_vec_2[cur_index];
                    line_vec_3[cur_index + 1] = line_vec_3[cur_index + 1] + line_vec_3[cur_index];
                }
                line_vec_2.erase(line_vec_2.begin() + cur_index);
                line_vec_3.erase(line_vec_3.begin() + cur_index);
                

                if (is_safe(line_vec_2) || is_safe(line_vec_3)) {
                    safe_ctr++;
                    break;
                }
            }
        }

        line_vec.clear();
        // line_vec_2.clear();
        // line_vec_3.clear();
    }

    if (print)
        print_result(2, 1, safe_ctr);
    
}