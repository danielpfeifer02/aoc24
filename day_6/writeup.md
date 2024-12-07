# Day 6

## Part 1
Pretty basic approach of just simulating the movement until the next position would be out of the grid. Since we can check if we are in a cycle the worst case number of steps is in $O(n)$ with $n$ being the area of the grid. Overall this gives worst case runtime of $O(n^2)$ because of `std::unordered_map::find`.

## Part 2
Again pretty simple approach of just simulating movement with the additional obstacle. Only "optimization" is that only positions are considered that can be reached without atting a new obstacle. Other positions obviously cannot introduce a circle if they are never reached. Circle checking happens using `unordered_map`. Since we add an obstacle per visited position and simulate again the worst case number of steps is in $O(n^2)$.