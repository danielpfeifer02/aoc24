# Day 9

## Part 1
Basic idea is just to go back to front and keep state on the current file looked at (from the back) and how much left of the file still needs to be inserted into free places. then iterating from the front to the back until both pointers (iterating pointer from front and state from back) meet.
Since we are not expanding the filesystem (and even if we did since a file / free space is at most 9 entries its just a constant factor) the runtime complexity is $O(n)$. 

## Part 2
For the second part i needed a lot of time to figure out that the problem actually wants me to not find the best fit for a file but the first fit. Otherwise pretty straight forward using a list that keeps in mind the parts that are free as well as their length. One actually would never need to fully iterate over the lenght of a file and just use multiplication rules to calculate the final score in one go but my brain was too tired for math so I just did a loop which had not much of an impact since the lengths are all small.
