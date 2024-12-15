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
| 4   | $O(n)$             | $O(n)$               | mpi                            | [Day 4](day_4/writeup.md)      |
| 5   | a.c.: $O(n^2)$, w.c.: $O(n^3)$ (per line)    |   a.c.: $O(n\log(n))$, w.c.: $O(n^2\log(n))$ (per line)             | sorting, unordered_map         | [Day 5](day_5/writeup.md)      |
| 6   | a.c.: $O(n)$, w.c.: $O(n^2)$        | a.c.: $O(n^2)$, w.c.: $O(n^3)$      | simulation       | [Day 6](day_6/writeup.md)      |
| 7   | $O(2^n)$       | $O(4^n)$      | bitset iteration       | [Day 7](day_7/writeup.md)      |
| 8   | $O(n^2)$       | $O(n^3)$      | simulation       | [Day 8](day_8/writeup.md)      |
| 9   | $O(n)$       | $O(n)$      | simulation       | [Day 9](day_9/writeup.md)      |
| 10   | $O(n)$       | $O(n)$      | unordered_set, unordered_multiset       | [Day 10](day_10/writeup.md)      |
| 11   | TBD       | TBD      | unordered_set, unordered_multiset       | [Day 11](day_11/writeup.md)      |
| 12   | TBD       | TBD      | flood fill       | [Day 12](day_12/writeup.md)      |
| 13   | TBD       | TBD      | eigen, linear algebra       | [Day 13](day_13/writeup.md)      |
| 14   | $O(1)$       | $O(idk)$      | modulo       | [Day 14](day_14/writeup.md)      |
| ... | ...                | ...               | ...                            | ...                            |
