#include <iostream>
#include <vector>
#include <fstream>

#define timeit(a, cnt) \
    do { \
        clock_t start = clock(); \
        for (int i = 0; i < cnt; i++) \
            a; \
        clock_t stop = clock(); \
        printf("Elapsed: %f seconds\n", (double)(stop - start) / CLOCKS_PER_SEC); \
    } while (0)

void setup_input(const std::string& input_filename) {
    static std::streambuf* cin_backup = std::cin.rdbuf(); // Backup cin buffer
    static std::ifstream file(input_filename);
    if (!file) {
        std::cerr << "Failed to open file: " << input_filename << std::endl;
        exit(1);
    }
    file.clear(); // Clear any errors
    file.seekg(0); // Go to beginning of file
    std::cin.rdbuf(file.rdbuf()); // Redirect cin to file
}

void restore_input() {
    std::cin.rdbuf(std::cin.rdbuf(nullptr)); // Restore original cin buffer
}

template <typename T>
void print_result(int day, int part, T result) {
    std::cout << "d" << day << "p" << part << ": " << result << std::endl;
}

template <typename T>
void print_vector(std::vector<T>& vec) {
    for (auto& e : vec) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}