# Day 5

## Part 1
Very straight forward approach of using a hashmap to store all relations that need to be satisfied and then checking for all elements in a given line (from back to front) if any element y is in front of an element x despite x needing to be in front of y. This solutions is, on average, in $O(n^2)$ but can be in $O(n^3)$ (since worst case of `std::unordered_map::find` is $O(n)$) for each line ($n$ being the line length) - not pretty but well enough for our use-case.

## Part 2
Simply wrote a comparison function so that `std::sort` can be used to sort the line. Since we essentially get comparison values given this is easy. If two elements are not comparable we can order them arbitrarily.