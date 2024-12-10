#include "../common.h"
#include <bits/stdc++.h>

#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptors.hpp>

using namespace std;
using val_t = uint8_t;

#define ROWS 50
#define COLS 50

enum class Verdict {
    INSIDE,
    OUTSIDE,
    ALREADY_COUNTED
};

array<array<val_t, COLS>, ROWS> print_sol;
array<array<bool, COLS>, ROWS> already_visited;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);
void read_input();
pair<int32_t, int32_t> dist(pair<int,int> a, pair<int,int> b);
Verdict unique_inside_grid(int x, int y) {
    auto ret = x >= 0 && x < ROWS && y >= 0 && y < COLS;
    if (ret == true) {
        if (already_visited[x][y] ) {
            return Verdict::ALREADY_COUNTED;
        }
        already_visited[x][y] = true;
        print_sol[x][y] = '#';
    }
    return ret ? Verdict::INSIDE : Verdict::OUTSIDE;
}

const int input_length = 0;
unordered_map<val_t, vector<pair<int,int>>> positions;

int main() {
    setup_input("day_8/input.txt");
    read_input();

    solve_part_1();

    solve_part_2();

}

void solve_part_1(bool print) { // default value for print is true

    already_visited = {false};

    uint32_t total = 0;

    for (const auto& key : positions | boost::adaptors::map_keys) {

        auto &coords = positions[key];
        auto size = coords.size();

        for (size_t i = 0; i < size; i++) {
            for (size_t j = i + 1; j < size; j++) {
                pair<int32_t,int32_t> d = dist(coords[i], coords[j]);

                // d is the distance from j to i so coords[j] + d is coords[i]
                assert (coords[j].first + d.first == coords[i].first);
                assert (coords[j].second + d.second == coords[i].second);

                auto res_i = unique_inside_grid(coords[i].first + d.first, coords[i].second + d.second);
                auto res_j = unique_inside_grid(coords[j].first - d.first, coords[j].second - d.second);
                // cout << (res_i == Verdict::INSIDE ? "INSIDE" : res_i == Verdict::OUTSIDE ? "OUTSIDE" : "ALREADY COUNTED") << endl;
                // cout << (res_j == Verdict::INSIDE ? "INSIDE" : res_j == Verdict::OUTSIDE ? "OUTSIDE" : "ALREADY COUNTED") << endl;
                total += (res_i == Verdict::INSIDE) + (res_j == Verdict::INSIDE);
            }
        }
    }

    print_result(8, 1, total);
}

void solve_part_2(bool print) { // default value for print is true

    already_visited = {false};

    uint32_t total = 0;

    for (const auto& key : positions | boost::adaptors::map_keys) {

        auto &coords = positions[key];
        auto size = coords.size();

        for (size_t i = 0; i < size; i++) {
            for (size_t j = i + 1; j < size; j++) {
                pair<int32_t,int32_t> d = dist(coords[i], coords[j]);

                // d is the distance from j to i so coords[j] + d is coords[i]
                assert (coords[j].first + d.first == coords[i].first);
                assert (coords[j].second + d.second == coords[i].second);

                auto tmp_i = coords[i];
                auto tmp_j = coords[j];

                Verdict ver;
                while ((ver = unique_inside_grid(tmp_i.first, tmp_i.second)) != Verdict::OUTSIDE) {
                    tmp_i.first += d.first;
                    tmp_i.second += d.second;
                    total += (ver == Verdict::INSIDE);
                }

                while ((ver = unique_inside_grid(tmp_j.first, tmp_j.second)) != Verdict::OUTSIDE) {
                    tmp_j.first -= d.first;
                    tmp_j.second -= d.second;
                    total += (ver == Verdict::INSIDE);
                }
                
            }
        }
    }

    print_result(8, 2, total);

}

void read_input() {
    string line;
    val_t c;
    int line_ctr = 0;
    int character_ctr = 0;
    while (getline(cin, line)) {
        character_ctr = 0;
        istringstream ss(line);
        while (ss >> c) {
            if (c != '.')
                positions[c].emplace_back(line_ctr, character_ctr);
            print_sol[line_ctr][character_ctr] = c;
            character_ctr++;
        }
        line_ctr++;
    }
}

pair<int32_t, int32_t> dist(pair<int,int> a, pair<int,int> b) {
    return {(a.first - b.first), (a.second - b.second)};
}