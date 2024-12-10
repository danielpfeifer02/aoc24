# Day 8

## Part 1
Pretty straight forward just itearting over any two pair of the same type (i.e. character) (so $n \choose 2$ possibilities for $n$ being the number of one type) and then going their distance to each other out on either of the two (which turns out to satisfy the constraint of having a distance twice as far to one than to the other).
Since we are dependent on the pairs of towers of the same type the runtime is in $O(n^2)$.

## Part 2
For part two just continue along the line of the two (which can be seen as a mathematical vector addition or in c++ terms using a `pair`). Important is to also consider the towers themselfs to bei a solution since they are obviously along the diagonal.
Here, since we not only depend on the pairs of towers of the same type but also go along the line they are spaning we have a runtime in $O(n^3)$.
