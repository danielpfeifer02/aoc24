#include "../common.h"
#include <bits/stdc++.h>

#include <mpi.h>

#define ROW_NUM 140
#define COL_NUM 140

// 141 ranks: Rank 0 (handler) and 140 ranks for 140 rows/cols
#define NUM_RANKS (ROW_NUM + 1)

using namespace std;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

const int input_length = 0;

int main() {
    setup_input("input.txt");
    solve_part_1();

    setup_input("input.txt");
    solve_part_2();
}

int search_pattern(string& str, string pattern) {

    // Get count of pattern in str
    int count = 0;
    size_t nPos = str.find(pattern, 0); // first occurrence
    while(nPos != string::npos) {
        count++;
        nPos = str.find(pattern, nPos + 1);
    }
    return count;
}

void solve_part_1(bool print) { // default value for print is true

    char c;
    string line;
    vector<char> grid;
    while(cin >> c) {
        grid.push_back(c);
    }
    
    assert(grid.size() == ROW_NUM * COL_NUM);

    char *c_grid = &grid[0];

    // Dummy argc, argv for MPI_Init
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Giving each rank one row and one col (using striding and own datatype)
    MPI_Datatype row_type, col_type;
    MPI_Type_contiguous(COL_NUM, MPI_CHAR, &row_type);
    MPI_Type_commit(&row_type);
    int count = ROW_NUM;
    int length = 1;
    int stride = COL_NUM;
    MPI_Type_vector(count, length, stride, MPI_CHAR, &col_type);
    MPI_Type_commit(&col_type);

    if (rank == 0) {

        for (int send_rank = 1; send_rank <= NUM_RANKS-1; send_rank++) {
            MPI_Send(&c_grid[(send_rank-1) * COL_NUM],  1, row_type, send_rank, 0, MPI_COMM_WORLD);
            MPI_Send(&c_grid[(send_rank-1)],            1, col_type, send_rank, 0, MPI_COMM_WORLD);        
        }

        int total_count = 0;
        for (int recv_rank = 1; recv_rank <= NUM_RANKS-1; recv_rank++) {
            int count;
            MPI_Recv(&count, 1, MPI_INT, recv_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_count += count;
        }

        print_result(4, 1, total_count);

    } else {

        char row[COL_NUM];
        MPI_Recv(row, 1, row_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        char col[ROW_NUM];
        MPI_Recv(col, ROW_NUM, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // TODO: get rid of weird c-string conversion
        string row_str(row, COL_NUM);
        string col_str(col, ROW_NUM);

        // Handle row and col
        int row_count_xmas = search_pattern(row_str, "XMAS");
        int row_count_samx = search_pattern(row_str, "SAMX");
        int col_count_xmas = search_pattern(col_str, "XMAS");
        int col_count_samx = search_pattern(col_str, "SAMX");

        // Each rank will also check both diagonals going down left and goingq down right
        // starting from first row and rank'th element in that row
        string diag_down_left = "";
        string diag_down_right = "";
        string diag_up_left = "";
        string diag_up_right = "";

        int j = rank - 1;
        int last_row_start = (ROW_NUM - 1) * COL_NUM + j;
        for (int i = 0; i < ROW_NUM; i++) {
            if (j - i >= 0) { // >= 0 check is sufficient since its a square and >= 0 means <= ROW_NUM
                diag_down_left += c_grid[i * COL_NUM + j - i];
                
                // We need to ignore the complete diagonal case to not count the same pattern twice
                if (j != ROW_NUM - 1)
                    diag_up_left += c_grid[last_row_start - i - (i * COL_NUM)];
            }
            if (j + i < COL_NUM) { // < COL_NUM check is sufficient since its a square and < COL_NUM means <= ROW_NUM
                diag_down_right += c_grid[i * COL_NUM + j + i];
                
                // We need to ignore the complete diagonal case to not count the same pattern twice
                if (j != 0) 
                    diag_up_right += c_grid[last_row_start + i - (i * COL_NUM)];
            }
        }

        int diag_down_left_count_xmas = search_pattern(diag_down_left, "XMAS");
        int diag_down_left_count_samx = search_pattern(diag_down_left, "SAMX");

        int diag_down_right_count_xmas = search_pattern(diag_down_right, "XMAS");
        int diag_down_right_count_samx = search_pattern(diag_down_right, "SAMX");

        int diag_up_left_count_xmas = search_pattern(diag_up_left, "XMAS");
        int diag_up_left_count_samx = search_pattern(diag_up_left, "SAMX");

        int diag_up_right_count_xmas = search_pattern(diag_up_right, "XMAS");
        int diag_up_right_count_samx = search_pattern(diag_up_right, "SAMX");


        int total_count =   row_count_xmas + 
                            row_count_samx + 
                            col_count_xmas + 
                            col_count_samx + 
                            diag_down_left_count_xmas + 
                            diag_down_left_count_samx + 
                            diag_down_right_count_xmas + 
                            diag_down_right_count_samx +
                            diag_up_left_count_xmas +
                            diag_up_left_count_samx +
                            diag_up_right_count_xmas +
                            diag_up_right_count_samx;

        MPI_Send(&total_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        
    }

    MPI_Type_free(&row_type);
    MPI_Type_free(&col_type);

    MPI_Finalize();
}

void solve_part_2(bool print) { // default value for print is true

}