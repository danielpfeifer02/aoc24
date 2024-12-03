# Day 2

## Part 1
Again, pretty simple first part. Since the implementation would not be the problem I searched through the 
standard library to see if I find something helpful. Turns out there is a function `std::adjacent_difference`
which does exaclty what we need. After that a simple check using `std::all_of` does the trick. Complexity wise
we have `std::adjacent_difference` being in $O(n)$ and `std::all_of` being (in our case) in $O(n)$ as well, with
$n$ being the lenght of a sequence. Overall we get a complexity of $O(k)$, with $k$ being the sum of all sequences 
looked at.

## Part 2
Part two also does not add too much complexity regarding the idea. I kept trying to use standard library
functions within my implementation and ended up using `std::minmax_element` and `std::distance` to
get the problem area (since one observation is that in case of an unsafe sequence at least one of 
the extreme points of the difference sequence is involved in an unsave area). The approach is to check
if merging the min / max distance sequence entry with a neightbour (i.e. removing one element in the original
sequence) can make the unsafe sequence safe again. This approach avoids the need to try out every removal
of the original element since we can immediately infer where to look from the distance sequence and have at most
four checks (each neighbour for both min and max element in the distance sequence). Complexity wise,
`std::minmax_element` runs in $O(n)$ and we have, as already mentioned, an upper bound of four checks for
finding out if an unsafe sequence can be made safe and therefore the overall complexity stays $O(n)$.