#include <iostream>
#include <string_view>
#include "../common.h"
#include <bits/stdc++.h>
#include <string>
#include <array>
#include "define.h" // for defining the input string

#define len(x) ((x)>99?3:((x)>9?2:1))

using namespace std;

void solve_part_1(bool print = true);
void solve_part_2(bool print = true);

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    constexpr StringLiteral() = default;

    // Constructor to create from existing character array
    template<size_t M>
    constexpr StringLiteral(const char (&str)[M], std::size_t offset) {
        std::copy_n(str + offset, N, value);
    }

    constexpr std::size_t size() const {
        return N;
    }

    // Add operator to concatenate characters
    constexpr StringLiteral<N + 1> operator+(char c) const {
        StringLiteral<N + 1> result;
        std::copy_n(value, N, result.value);
        result.value[N] = c;
        return result;
    }

    char value[N] = {0};

    // Allow conversion to string_view
    constexpr operator std::string_view() const {
        return std::string_view(value, N - 1);
    }
};

// Helper to check if a character is a digit
constexpr bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

// Helper to extract a number from a string starting at a given index
constexpr int parse_number(std::string_view str, std::size_t start) {
    int num = 0;
    while (start < str.size() && is_digit(str[start])) {
        num = num * 10 + (str[start] - '0');
        ++start;
    }
    return num;
}

// Match "mul([1-999],[1-999])" pattern
constexpr int matches_mul_pattern(std::string_view str, std::size_t start) {
    if (str.substr(start, 4) != "mul(") return false;
    std::size_t pos = start + 4; // Skip "mul("
    std::size_t end = pos;
    
    // Parse first number
    int num1 = parse_number(str, pos);
    end = end + len(num1);

    if (num1 < 1 || num1 > 999 || end >= str.size() || str[end] != ',') return false;
    pos = start + 4 + len(num1) + 1; // Skip ','
    
    // Parse second number
    int num2 = parse_number(str, pos);
    end = end + 1 + len(num2);
    
    if (num2 < 1 || num2 > 999 || end >= str.size() || str[end] != ')') return false;
    return true;
}

constexpr bool matches_do_pattern(std::string_view str, std::size_t start) {
    return (str.substr(start, 4) == "do()" || str.substr(start, 7) == "don't()");
}

constexpr bool get_do_dont_val(std::string_view str, std::size_t start) {
    if (str.substr(start, 4) == "do()") return true;
    if (str.substr(start, 7) == "don't()") return false;
    assert(str.size() == -1); // Failing if neither do() nor don't() is found
}

// Recursive compile-time solver
template <StringLiteral Str, int Part, bool Enabled = 1, int Start = 0, int Result = 0>
constexpr auto solve() {
    if constexpr (Start >= Str.size() - 1) {
        return Result; // Base case: End of string
    } else if constexpr (matches_mul_pattern(Str, Start)) {
        // Skip the matched pattern
        constexpr auto a = parse_number(Str, Start + 4); // Parse first number
        constexpr auto skip_length_1 = Start + 5 + len(a); // Skip "mul(" and ","

        constexpr auto b = parse_number(Str, skip_length_1); // Parse second number
        constexpr auto skip_length_2 = skip_length_1 + len(b) + 1; // Skip ")"
    
        constexpr int res = Enabled ? a * b : 0;
        return solve<Str, Part, Enabled, skip_length_2, Result + res>();
    } else if constexpr (Part == 2 && matches_do_pattern(Str, Start)) {
        constexpr auto do_val = get_do_dont_val(Str, Start);
        constexpr auto skip_length = do_val ? /*do()*/ 4 : /*don't()*/ 7;
        return solve<Str, Part, do_val, Start + skip_length, Result>();
    } else {
        // Append current character and continue
        return solve<Str, Part, Enabled, Start + 1, Result/*, TextWithoutPattern + Str.value[Start]*/>();
    }
}

const int input_length = 0;

int main() {
    // setup_input("day_2/input.txt");
    // solve_part_1();
    // Solve part 1 at compile time
    constexpr auto part_1 = solve<StringLiteral(input), 1>();
    std::cout << part_1 << std::endl;

    // setup_input("day_2/input.txt");
    // solve_part_2();
    // Solve part 2 at compile time
    constexpr auto part_2 = solve<StringLiteral(input), 2>();
    std::cout << part_2 << std::endl;
}

void solve_part_1(bool print) { // default value for print is true
    // Nothing to see here
}

void solve_part_2(bool print) { // default value for print is true
    // Nothing to see here
}