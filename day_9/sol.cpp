#include "../common.h"
#include <bits/stdc++.h>

using namespace std;
using val_t = uint8_t;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 0;

int main() {
    setup_input("day_9/input.txt");
    solve_part_1();

    setup_input("day_9/input.txt");
    solve_part_2();
}

void solve_part_1(bool print) { // default value for print is true

    vector<val_t> input;
    val_t val;

    while (cin >> val) {
        input.push_back(val-'0');
    }

    if ((input.size()+1)%2) {
        input.pop_back();
    }

    uint64_t number_of_files = (input.size()+1)/2;

    uint64_t current_file_id_back = number_of_files-1;
    uint64_t left_size_back = input[input.size()-1];
    input.pop_back();

    uint64_t current_file_id_front = 0;
    uint64_t left_size_front = input[0];

    uint64_t res = 0;

    val_t next;

    int ctr = 0;

    for (size_t i = 0; i < input.size(); i++) {

        next = input[i];
        
        if (i%2==0) {
            left_size_front = next;   
            
            while(left_size_front > 0) {
                res += current_file_id_front * ctr++;
                left_size_front--;
            }
            current_file_id_front++;
        } else {
            while (next > 0) {
                if (left_size_back == 0) {
                    input.pop_back();
                    left_size_back = input[input.size()-1];
                    input.pop_back();
                    current_file_id_back--;
                }
                res += current_file_id_back * ctr++;
                next--;
                left_size_back--;
            }
        }
    }
    for (size_t i = 0; i < left_size_back; i++) {
        res += current_file_id_back * ctr++;
    }

    if (print)
        print_result(9, 1, res);

}

template< typename T >
typename std::vector<T>::iterator 
   insert_sorted( std::vector<T> & vec, T const& item )
{
    return vec.insert
        ( 
            std::upper_bound( vec.begin(), vec.end(), item ),
            item 
        );
}

void solve_part_2(bool print) { // default value for print is true

    vector<val_t> input;
    vector<pair<uint64_t, uint64_t>> free_spaces; // sorted by size and then by pos pair<pos, size>
    val_t val;

    while (cin >> val) {
        input.push_back(val-'0');
    }

    if ((input.size()+1)%2) {
        input.pop_back();
    }

    uint64_t number_of_files = (input.size()+1)/2;

    uint64_t start_pos = 0;
    for (uint64_t i = 1; i < input.size(); i+=2) {
        start_pos += input[i-1];
        if (input[i] > 0)
            insert_sorted<pair<uint64_t,uint64_t>>(free_spaces, make_pair(start_pos, input[i]));
        start_pos += input[i];
    }
    start_pos += input[input.size()-1]; // Needed for correct calc of pos later on

    vector<pair<uint64_t, pair<uint64_t,uint64_t>>> file_id_and_start_pos_size;
    uint64_t current_file_id_back = number_of_files-1;

    for (uint64_t i = input.size()-1; i > 0; i-=2) { // Going through all files in reverse order. Last entry has to be considering a file 
        
        uint64_t size = input[i];
        start_pos -= input[i];
        
        // TODO: lower bound unnecessary?
        auto best_fit = lower_bound(free_spaces.begin(), free_spaces.end(), make_pair(0, size), [](const pair<uint64_t, uint64_t>& a, const pair<uint64_t, uint64_t>& b) {
            if (a.first == b.first) {
                return a.second < b.second;
            }
            return a.first < b.first;
        });

        auto index = distance(free_spaces.begin(), best_fit);

        while (index < free_spaces.size() && free_spaces[index].second < size) { // Find the first that is to the left
            index++;
        }
        if (index < free_spaces.size() && free_spaces[index].first > start_pos) {
            index = free_spaces.size();
        }
        best_fit = free_spaces.begin() + index;

        if (index < free_spaces.size() && free_spaces[index].first < start_pos) {
            file_id_and_start_pos_size.push_back(make_pair(current_file_id_back--, make_pair(free_spaces[index].first, size)));
            
            auto best_fit_copy = make_pair(free_spaces[index].first, free_spaces[index].second);
            best_fit_copy.first += size;
            best_fit_copy.second -= size;

            free_spaces.erase(best_fit);
            if (best_fit_copy.second > 0) {
                insert_sorted<pair<uint64_t,uint64_t>>(free_spaces, best_fit_copy);
            }
        } else {
            file_id_and_start_pos_size.push_back(make_pair(current_file_id_back--, make_pair(start_pos, size)));
        }
        start_pos -= input[i-1];
    }
    
    uint64_t res = 0;
    for (auto &e : file_id_and_start_pos_size) {
        auto size = e.second.second;
        for (uint64_t i = 0; i < size; i++) {
            res += e.first * (e.second.first+i);
        }
    }

    if (print)
        print_result(9, 2, res);



}

void solve_part_2_best_fit(bool print) { // default value for print is true

    vector<val_t> input;
    vector<pair<uint64_t, uint64_t>> free_spaces; // sorted by size and then by pos pair<size, pos>
    val_t val;

    while (cin >> val) {
        input.push_back(val-'0');
    }

    if ((input.size()+1)%2) {
        input.pop_back();
    }

    uint64_t number_of_files = (input.size()+1)/2;

    uint64_t start_pos = 0;
    for (uint64_t i = 1; i < input.size(); i+=2) {
        start_pos += input[i-1];
        if (input[i] > 0)
            insert_sorted<pair<uint64_t,uint64_t>>(free_spaces, make_pair(input[i], start_pos));
        start_pos += input[i];
    }
    start_pos += input[input.size()-1]; // Needed for correct calc of pos later on

    vector<pair<uint64_t, pair<uint64_t,uint64_t>>> file_id_and_start_pos_size;
    uint64_t current_file_id_back = number_of_files-1;

    for (uint64_t i = input.size()-1; i > 0; i-=2) { // Going through all files in reverse order. Last entry has to be considering a file 
        
        uint64_t size = input[i];
        start_pos -= input[i];
        
        auto best_fit = lower_bound(free_spaces.begin(), free_spaces.end(), make_pair(size, 0), [](const pair<uint64_t, uint64_t>& a, const pair<uint64_t, uint64_t>& b) {
            if (a.first == b.first) {
                return a.second < b.second;
            }
            return a.first < b.first;
        });

        auto index = distance(free_spaces.begin(), best_fit);

        while (index < free_spaces.size() && free_spaces[index].second > start_pos) { // Find the first that is to the left
            index++;
        }

        if (index < free_spaces.size() && free_spaces[index].second < start_pos) {
            file_id_and_start_pos_size.push_back(make_pair(current_file_id_back--, make_pair(free_spaces[index].second, size)));
            
            auto best_fit_copy = make_pair(free_spaces[index].first, free_spaces[index].second);
            best_fit_copy.first -= size;
            best_fit_copy.second += size;

            free_spaces.erase(best_fit);
            if (best_fit_copy.second > 0) {
                insert_sorted<pair<uint64_t,uint64_t>>(free_spaces, best_fit_copy);
            }
        } else {
            file_id_and_start_pos_size.push_back(make_pair(current_file_id_back--, make_pair(start_pos, size)));
        }
        start_pos -= input[i-1];
    }
    
    uint64_t res = 0;
    for (auto &e : file_id_and_start_pos_size) {
        auto size = e.second.second;
        for (uint64_t i = 0; i < size; i++) {
            res += e.first * (e.second.first+i);
        }
    }

    if (print)
        print_result(9, 2, res);

}
