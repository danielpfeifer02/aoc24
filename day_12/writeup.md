# Day 12

## Part 1
I used a simple flood fill type of appraoch to iterate over all the parts of an area. For each "tile" storing how many
edges to other areas it has (a number between 0 and 4) gives us the sides and by just having a count on the tiles per 
area we can easily calculate the price for the fence.

## Part 2
The approach is similar to part one except that now we also save the side of the edge along with the tile coordinates.
Then we can, by looking up in the set of other tiles, merge all sides and thus ignoring additional counts of one side.
