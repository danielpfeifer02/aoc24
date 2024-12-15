#include "../common.h"
#include <bits/stdc++.h>

using namespace std;
using val_t = uint8_t;

enum class Direction_Mask {
    NONE = 0b0000,
    UP = 0b0001,
    RIGHT = 0b0010,
    DOWN = 0b0100,
    LEFT = 0b1000
};

class PairHash {
public:
    int operator()(const pair<uint32_t, uint32_t>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

class TupleHash {
public:
    int operator()(const tuple<uint32_t, uint32_t, Direction_Mask>& t) const {
        auto [x, y, mask] = t;
        return hash<int>()(x) ^ hash<int>()(y) ^ hash<int>()(int(mask));
    }
};

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 0;

int main() {
    setup_input("day_12/input.txt");
    solve_part_1();
}

bool save_area_compare(vector<vector<val_t>>& grid, pair<uint32_t, uint32_t> pos, val_t should_be) {
    if (pos.first >= grid.size() || pos.second >= grid[0].size()) { // overflow considers negative values
        return false;
    }

    if (grid[pos.first][pos.second] == should_be) {
        return true;
    }

    return false;
}

vector<tuple<val_t, uint32_t, uint32_t, Direction_Mask>> get_area(vector<vector<val_t>>& grid, pair<uint32_t, uint32_t> pos, unordered_set<pair<uint32_t, uint32_t>, PairHash>& positions_to_look_at) {
    vector<tuple<val_t, uint32_t, uint32_t, Direction_Mask>> area;
    auto cur_val = grid[pos.first][pos.second];

    unordered_set<pair<uint32_t, uint32_t>, PairHash> already;

    queue<pair<uint32_t, uint32_t>> q;

    q.push(pos);

    while (q.size() > 0) {

        auto cur = q.front();
        q.pop();
        positions_to_look_at.erase(cur);

        auto left = make_pair(cur.first, cur.second - 1);
        auto right = make_pair(cur.first, cur.second + 1);
        auto up = make_pair(cur.first - 1, cur.second);
        auto down = make_pair(cur.first + 1, cur.second);
        uint32_t edges = 0;

        Direction_Mask tmp_mask = Direction_Mask::NONE;

        vector<pair<pair<uint32_t,uint32_t>, Direction_Mask>> pair_list = {  make_pair(left, Direction_Mask::LEFT), 
                            make_pair(right, Direction_Mask::RIGHT), 
                            make_pair(up, Direction_Mask::UP), 
                            make_pair(down, Direction_Mask::DOWN)};

        for (auto& pd : pair_list) {
            auto p = pd.first;
            Direction_Mask mask = pd.second;
            if (already.find(p) != already.end()) {
                continue;
            }

            if (save_area_compare(grid, p, cur_val)) {
                q.push(p);
                already.insert(p);
            } else {
                edges++;
                tmp_mask = Direction_Mask(int(tmp_mask) | int(mask));
            }
        }

        area.push_back({edges, cur.first, cur.second, tmp_mask});
        already.insert(cur);

    }

    return area;
}

uint32_t get_sides_from_area(vector<tuple<val_t, uint32_t, uint32_t, Direction_Mask>>& area) {

    uint32_t sides = 0;
    
    unordered_set<tuple<uint32_t, uint32_t, Direction_Mask>, TupleHash> sides_set;
    for (auto& val : area) {
        auto x = get<1>(val);
        auto y = get<2>(val);
        auto mask = int(get<3>(val));

        if (mask & int(Direction_Mask::UP)) {
            sides_set.insert({x, y, Direction_Mask::UP});
        }
        if (mask & int(Direction_Mask::RIGHT)) {
            sides_set.insert({x, y, Direction_Mask::RIGHT});
        }
        if (mask & int(Direction_Mask::DOWN)) {
            sides_set.insert({x, y, Direction_Mask::DOWN});
        }
        if (mask & int(Direction_Mask::LEFT)) {
            sides_set.insert({x, y, Direction_Mask::LEFT});
        }
    }

    while (sides_set.size() > 0) {

        auto [x, y, mask] = *sides_set.begin(); 
        sides_set.erase(sides_set.begin());

        if (mask == Direction_Mask::LEFT || mask == Direction_Mask::RIGHT) { // Go up/down when checking for side

            uint32_t tmp_x = x;
            while(true) {
                tmp_x--;
                auto up = make_tuple(tmp_x, y, mask);
                if (sides_set.find(up) != sides_set.end()) {
                    sides_set.erase(up);
                } else {
                    break;
                }
            }
            tmp_x = x;
            while(true) {
                tmp_x++;
                auto down = make_tuple(tmp_x, y, mask);
                if (sides_set.find(down) != sides_set.end()) {
                    sides_set.erase(down);
                } else {
                    break;
                }
            }
            sides++;

        }
        
        if (mask == Direction_Mask::UP || mask == Direction_Mask::DOWN) { // Go left/right when checking for side

            auto tmp_y = y;
            while(true) {
                tmp_y--;
                auto left = make_tuple(x, tmp_y, mask);
                if (sides_set.find(left) != sides_set.end()) {
                    sides_set.erase(left);
                } else {
                    break;
                }
            }
            tmp_y = y;
            while(true) {
                tmp_y++;
                auto right = make_tuple(x, tmp_y, mask);
                if (sides_set.find(right) != sides_set.end()) {
                    sides_set.erase(right);
                } else {
                    break;
                }
            }
            sides++;

        }
    }

    return sides;
}

void solve_part_1(bool print) { // default value for print is true

    string line;
    vector<vector<val_t>> grid;
    uint32_t row_ctr = 0, col_ctr = 0;
    unordered_set<pair<uint32_t, uint32_t>, PairHash> positions_to_look_at;

     // An area is just vector with the number of edges each point in it has. 
     // The point coords themselfs are not stored since they are not needed.
    vector<vector<tuple<val_t, uint32_t, uint32_t, Direction_Mask>>> areas;
    while (getline(cin, line)) {
        vector<val_t> row;
        col_ctr = 0;
        for (auto& c : line) {
            row.push_back(c);
            positions_to_look_at.insert({row_ctr, col_ctr});
            col_ctr++;
        }
        row_ctr++;
        grid.push_back(row);
    }

    while (positions_to_look_at.size() > 0) {
        auto it = positions_to_look_at.begin();
        pair<uint32_t, uint32_t> pos = *it;
        positions_to_look_at.erase(it);

        auto area = get_area(grid, pos, positions_to_look_at);
        areas.push_back(area);
    }

    uint32_t total_fences = 0;
    uint32_t total_sides = 0;
    for (auto& area : areas) {
        auto area_size = area.size();
        uint32_t fences = 0;
        for (auto& val : area) {
            fences += get<0>(val);
        }
        total_fences += fences * area_size;

        auto sides = get_sides_from_area(area);
        total_sides += sides * area_size;
    }

    if (print) {
        print_result(12, 1, total_fences);
        print_result(12, 2, total_sides);
    }
}