# Day 3

## Part 1
Today was fun. Since, again, the problem itself was pretty straight forward I decided to spice it up a little
bit and try to solve it using compile time programming. After quite a few compile time errors [it's my first 
compile time program so it's fine :)] and some fiddling around with compiler settings (turns out the default
values for `-ftemplate-depth` and `-fconstexpr-depth` were too small) it worked like expected. Now we got the
sacret runtime complexity of $O(1)$.

## Part 2
Not much difference to part 1. Only added a separate match check for en- and disabling the multiplication stuff.
