#include "../common.h"
#include <bits/stdc++.h>

#define WIDTH 130
#define HEIGHT 130

using namespace std;

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDEFINED
};

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);
int run(int part = 1);
Direction turn_right(Direction dir);
pair<pair<int, int>, Direction> move_to_next_state(pair<int, int>& pos, Direction dir);

class PairHash {
public:
    template <typename T, typename U>
    size_t operator()(const pair<T, U>& x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

class NestedPairHash {
public:
    size_t operator()(const std::pair<std::pair<int, int>, Direction>& x) const {
        const auto& [pos, dir] = x;
        auto hash1 = PairHash()(pos);  // Hash the inner pair
        auto hash2 = std::hash<Direction>()(dir); // Hash the Direction
        return hash1 ^ (hash2 << 1); // Combine hashes
    }
};

const int input_length = 0;

array<array<char, WIDTH>, HEIGHT> grid;
unordered_map<pair<int,int>, bool, PairHash> visited;
pair<int, int> start_pos;
Direction facing = Direction::UNDEFINED;

int main() {
    setup_input("day_6/input.txt");
    solve_part_1();

    setup_input("day_6/input.txt");
    solve_part_2();
}

void solve_part_1(bool print) { // default value for print is true

    for (int w = 0; w < WIDTH; w++) {
        for (int h = 0; h < HEIGHT; h++) {
            cin >> grid[w][h];
            if (grid[w][h] == '^') {
                start_pos = {w, h};
                facing = Direction::UP;
            }
        }
    }

    assert(facing != Direction::UNDEFINED);

    auto ret = run();   

    if (print) {
        print_result(6, 1, ret);
    }

}

void solve_part_2(bool print) { // default value for print is true

    assert (!visited.empty());

    auto ctr = 0;

    for (auto &visit_pos : visited) {

        if (visit_pos.first == start_pos) {
            continue;
        }

        facing = Direction::UP;
        grid[visit_pos.first.first][visit_pos.first.second] = '#';
    
        auto ret = run(2);

        if (ret == -1)
            ctr++;
        
        grid[visit_pos.first.first][visit_pos.first.second] = '.';
    }

    if (print) {
        print_result(6, 2, ctr);
    }


}

int run(int part) {


    unordered_map<pair<int,int>, bool, PairHash> visited_local;
    unordered_map<pair<pair<int,int>, Direction>, bool, NestedPairHash> visited_detailed_local;

    pair<int, int> pos = start_pos;
    visited[start_pos] = true;
    visited_local[start_pos] = true;
    visited_detailed_local[{pos, facing}] = true;

    while (true) {
        pair<pair<int, int>, Direction> next = move_to_next_state(pos, facing);

        if (next.second == Direction::UNDEFINED) {
            break;
        }

        pos = next.first;
        facing = next.second;

        // To find a circular path we need the detailed map since
        // the facing direction matters.
        if (visited_detailed_local.find({pos, facing}) != visited_detailed_local.end()) {
            return part == 1 ? visited.size() : -1;
        }

        // We save all the visited positions for part two since
        // that is some easy pruning where we can remove some positions
        // for the additional obstacle before we start the search.
        if (part == 1) 
            visited[pos] = true;

        visited_detailed_local[{pos, facing}] = true;
    }

    return visited.size();
}

Direction turn_right(Direction dir) {
    switch (dir) {
        case Direction::UP:
            return Direction::RIGHT;
        case Direction::DOWN:
            return Direction::LEFT;
        case Direction::LEFT:
            return Direction::UP;
        case Direction::RIGHT:
            return Direction::DOWN;
        default:
            throw invalid_argument("Invalid direction");
    }
}

pair<pair<int, int>, Direction> move_to_next_state(pair<int, int>& pos, Direction dir) {
    pair<int, int> tmp_next;
    switch (dir) {
        case Direction::UP:
            tmp_next = {pos.first - 1, pos.second};
            break;
        case Direction::DOWN:
            tmp_next = {pos.first + 1, pos.second};
            break;
        case Direction::LEFT:
            tmp_next = {pos.first, pos.second - 1};
            break;
        case Direction::RIGHT:
            tmp_next = {pos.first, pos.second + 1};
            break;
        default:
            throw invalid_argument("Invalid direction");
    }

    if (tmp_next.first < 0 || tmp_next.first >= HEIGHT || tmp_next.second < 0 || tmp_next.second >= WIDTH)
        return {{-1, -1}, Direction::UNDEFINED};
    else if (grid[tmp_next.first][tmp_next.second] == '#') {
        return {pos, turn_right(dir)};
    } else {
        return {tmp_next, dir};
    }
}