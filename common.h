#include <iostream>

#define timeit(a, cnt) \
    do { \
        clock_t start = clock(); \
        for (int i = 0; i < cnt; i++) \
            a; \
        clock_t stop = clock(); \
        printf("Elapsed: %f seconds\n", (double)(stop - start) / CLOCKS_PER_SEC); \
    } while (0)

void setup_input(const std::string& input_filename) {
    static std::string current_file;
    static FILE* file = nullptr;

    // Close the current file if it's already open and a different file is requested
    if (file != nullptr && current_file != input_filename) {
        fclose(file);
        file = nullptr;
        current_file.clear();
    }

    // Open the file if it's not already open or needs to be reset
    if (file == nullptr) {
        file = freopen(input_filename.c_str(), "r", stdin);
        if (file == nullptr) {
            std::cerr << "Failed to open file: " << input_filename << std::endl;
            exit(1);
        }
        current_file = input_filename;
    } else {
        // Reset the stream to the beginning of the file
        rewind(file);
    }
}


template <typename T>
void print_result(int day, int part, T result) {
    std::cout << "d" << day << "p" << part << ": " << result << std::endl;
}