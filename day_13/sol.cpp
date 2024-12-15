#include "../common.h"
#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
using val_t = uint64_t;

void solve(uint64_t goal_add = 0, bool print = true);

const int input_length = 0;

int main() {
    setup_input("day_13/input.txt");
    solve();

    setup_input("day_13/input.txt");
    solve(10000000000000);
}

pair<uint64_t, uint64_t> a_b_pushes(pair<uint64_t, uint64_t> a, 
                                    pair<uint64_t, uint64_t> b,
                                    pair<uint64_t, uint64_t> goal,
                                    pair<uint64_t, uint64_t> price) {

    uint64_t a_pushes = 0;
    uint64_t b_pushes = 0;

    Eigen::Matrix2d matrix;
    matrix << a.first, b.first,
              a.second, b.second;

    Eigen::Vector2d goal_vec;
    goal_vec << goal.first, goal.second;

    if (matrix.determinant() == 0) {
        return {0, 0};
    }

    Eigen::ColPivHouseholderQR<Eigen::MatrixXd> qr(matrix);
    Eigen::Vector2d pushes_vec = qr.solve(goal_vec);

    a_pushes = pushes_vec(0);
    b_pushes = pushes_vec(1);

    int k = 5;
    for (int i=-k; i<k+1; i++) {
        for (int j=-k; j<k+1; j++) {
            if (a_pushes * a.first + b_pushes * b.first == goal.first &&
                a_pushes * a.second + b_pushes * b.second == goal.second) {
                return {a_pushes, b_pushes};
            }
            a_pushes = pushes_vec(0) + i;
            b_pushes = pushes_vec(1) + j;
        }
    }

    return {0, 0};

}

void solve(uint64_t goal_add, bool print) { // default value for print is true

    uint64_t ax, ay, bx, by, gx, gy;
    
    pair<uint64_t, uint64_t> price = {3, 1};
    uint64_t total = 0;

    string line1, line2, line3, lineEmpty;
    for (int i=0; i<320; i++) {

        getline(cin, line1);
        getline(cin, line2);
        getline(cin, line3);
        getline(cin, lineEmpty);
        
        sscanf(line1.c_str(), "Button A: X+%ld, Y+%ld", &ax, &ay);
        sscanf(line2.c_str(), "Button B: X+%ld, Y+%ld", &bx, &by);
        sscanf(line3.c_str(), "Prize: X=%ld, Y=%ld", &gx, &gy);

        gx += goal_add;
        gy += goal_add;

        auto pushes = a_b_pushes({ax, ay}, {bx, by}, {gx, gy}, price);

        total += price.first * pushes.first + price.second * pushes.second;
           
    }

    if (print) {
        print_result(13, 0, total);
    }

}