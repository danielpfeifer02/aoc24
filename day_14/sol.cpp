#include "../common.h"
#include <bits/stdc++.h>

using namespace std;
using val_t = int32_t;

#define WIDTH 101
#define HEIGHT 103
#define CENTER_WIDTH 50
#define CENTER_HEIGHT 51

#define INTERESSTING_THRESHOLD 42

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 0;

class PairHash {
public:
    size_t operator()(const pair<val_t, val_t>& p) const {
        return hash<val_t>()(p.first) ^ hash<val_t>()(p.second);
    }
};

class TupleHash {
public:
    size_t operator()(const tuple<val_t, val_t, val_t, val_t>& t) const {
        return hash<val_t>()(get<0>(t)) ^ hash<val_t>()(get<1>(t)) ^ hash<val_t>()(get<2>(t)) ^ hash<val_t>()(get<3>(t));
    }
};

int main() {
    setup_input("day_14/input.txt");
    solve_part_1();

    setup_input("day_14/input.txt");
    solve_part_2();
}

val_t mod(val_t a, val_t b) {
    return (a % b + b) % b;
}

pair<val_t, val_t> wait(uint32_t seconds, pair<val_t, val_t> pos, pair<val_t, val_t> vel) {

    val_t modulo_x = WIDTH;
    val_t modulo_y = HEIGHT;
    pair<val_t, val_t> tmp = {pos.first + seconds * mod(vel.first, modulo_x), pos.second + seconds * mod(vel.second, modulo_y)};

    tmp.first = mod(tmp.first, modulo_x);
    tmp.second = mod(tmp.second, modulo_y);

    return tmp;
}

void solve_part_1(bool print) { // default value for print is true

    string line;
    uint32_t seconds = 100;

    array<val_t, 4> quadrants = {0, 0, 0, 0}; // UL, UR, LL, LR

    while(getline(cin, line)) {
        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);

        auto new_pos = wait(seconds, {px, py}, {vx, vy});

        bool upper = new_pos.second < CENTER_HEIGHT;
        bool lower = new_pos.second > CENTER_HEIGHT;
        bool left = new_pos.first < CENTER_WIDTH;
        bool right = new_pos.first > CENTER_WIDTH;

        if (upper && left) {
            quadrants[0]++;
        } else if (upper && right) {
            quadrants[1]++;
        } else if (lower && left) {
            quadrants[2]++;
        } else if (lower && right) {
            quadrants[3]++;
        }
    }

    if (print) {
        auto prod = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
        print_result(14, 1, prod);
    }


}

bool interessting_connected_component(unordered_set<pair<val_t, val_t>, PairHash>/* no reference - we want copy */ coords, const pair<val_t, val_t>& start, unordered_set<pair<val_t, val_t>, PairHash>& visited) {

    if (visited.find(start) != visited.end()) {
        return false;
    }
    
    queue<pair<val_t, val_t>> q;
    q.push(start);
    auto count = 0;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (coords.find(current) == coords.end()) {
            continue;
        }

        coords.erase(current);
        count++;
        visited.insert(current);

        for (int i=-1; i<=1; i++) {
            for (int j=-1; j<=1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                pair<val_t, val_t> next = {current.first + i, current.second + j};
                q.push(next);
            }
        }
    }

    return count > INTERESSTING_THRESHOLD;

}

void print_grid(unordered_set<pair<val_t, val_t>, PairHash>& coords) {
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (coords.find({j, i}) != coords.end()) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

void solve_part_2(bool print) { // default value for print is true

    string line;

    unordered_set<tuple<val_t, val_t, val_t, val_t>, TupleHash> coords_with_vel;

    while(getline(cin, line)) {
        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);

        coords_with_vel.insert({px, py, vx, vy});
    }

    uint64_t seconds_elapsed = 0;

    while(1) {
        unordered_set<pair<val_t, val_t>, PairHash> visited;
        bool interessting = false;

        unordered_set<pair<val_t, val_t>, PairHash> coords;
        for (auto& coord_with_vel : coords_with_vel) {
            auto pos = make_pair(get<0>(coord_with_vel), get<1>(coord_with_vel));
            auto vel = make_pair(get<2>(coord_with_vel), get<3>(coord_with_vel));
            coords.insert(wait(seconds_elapsed, pos, vel));
        }

        for (auto& coord : coords) {
            if (interessting_connected_component(coords, coord, visited)) {
                interessting = true;
                break;
            }
        }

        if (interessting) {
            cout << "Seconds elapsed: " << seconds_elapsed << endl;
            print_grid(coords);
        }

        seconds_elapsed++;

    }
}