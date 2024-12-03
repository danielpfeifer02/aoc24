# Advent of Code 2024
This year, in order to prepare for an upcoming NG software engineering position, I want to brush up my C++ skills. 

The focus lies in using modern C++ best practices and getting used to implementing efficient and correct solutions to this year's AoC challenges.

Topics I would like to dive into at some point - without wanting to restrict myself to doing so - are:

1) Generic template (meta-)programming
2) SOTA library and standard usage like eigen or mpi
3) Cache-, copy-, compiletime- and syscall-optimized solutions
4) New c++20 and c++23 approaches like using concepts, coroutines or pattern matching
5) ...

Since the main goal will be to solve the challenges in fun ways and getting a deeper understanding of c++ (and because I will only start to work in february) I will not try to optimize for solving speed and there might even be some backlog occuring because of other private ventures.

However, I will try to create a write up for each solution explaining my approach and the idea behind it.

| Day | Runtime Part 1     | Runtime Part 2    | Approach keywords              | Write-Up                       |  
|-----|--------------------|-------------------|--------------------------------|--------------------------------|
| 1   | $O(n\log{n})$      | $O(n)$            | sort, unordered_multiset       | [Day 1](day_1/writeup.md)      |
| 2   | $O(n)$             | $O(n)$            | adjacent_difference            | [Day 2](day_2/writeup.md)      |
| 3   | $O(1)$ (ctp)       | $O(1)$ (ctp)      | compile-time programming       | [Day 3](day_3/writeup.md)      |
| ... | ...                | ...               | ...                            | ...                            |
