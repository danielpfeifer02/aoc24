# Day 11

## Part 1
Today's problem is one where blindly implementing the task without much though will probably break your back in part two.
Normally these kind of AoC problems turn out to have some kind of cycle or similar that significantly cuts the computation.
Since I was unable to spot any cycles directly I had to try something else. While thinking about the cycles I got a feeling 
that I did handle the same number multiple times (e.g. when starting with 1->2024->20 24->2 0 2 4->... there are already 
duplicates) so the initial thought would be to use the `unordered_multiset` data structure again as we did already in previous
tasks. As it turns out it saves duplicates of elements in the bucket multiple times so this is not ideal. We make our own
multiset version with `unordered_map` mapping to a counter value. That way we just calculate the transformation of the stone
with engraving $x$ once and add the count of $x$ in the initial map to a new map. We iterate over these two maps in a ping-pong-buffer
style until we get the desired amount of iterations. This turns out to be fast enough for both parts.


## Part 2
Turns out brite forcing would have broken my back. But due to initial thoughts part two basically works with the same code from part one.