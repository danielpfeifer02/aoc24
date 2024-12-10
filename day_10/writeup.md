# Day 10

## Part 1
The approach is a very simple recursive funciton that checks all four surrounding positions if they contain the correct next height. If so the recursive call happens, if not the function exits. If the final height is found a dummy value (doesn't matter which one as long as it stays the same for the same final position) is inserted in an `unordered_set`. In the end the set size for a certain starting position gives its score.
Runtime complexity for the step function is in $O(1)$ per starting position regarding the input grid size.
Obviously the step function does not care about the size of the grid and is only dependent on $m$, which is the length of
a path (so in our case 10 - from 0 to 9). So the step funciton is in $O(m)$. 

## Part 2
Turns out not fully understanding the problem description led me to accidentally solve part two while trying to solve part one. Basically just change `unordered_set` to `unordered_multiset` (meaning arriving at the same destination from the same starting point with different paths is counted as different results). 
