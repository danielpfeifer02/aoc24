# Day 13

## Part 1
Since the problem is essentially a linear algebra problem of solving $A * x = b$ eigen seems to be an obvious choice.
Solving the equation using inversion directly is not ideal because of instabilities so I opted with the 
ColPivHouseholderQR decomposition solution as this one is both fast and has a good accuracy according to the eigen
documentation [1]. Since there are rounding errors occuring due to the nature of floating point numbers there needs to 
be an additional step of verifying any solution that the program thinks it has found as valid by trying in a small vacinity
if $A * x$ does really equal $b$.


## Part 2
Part one solution works for part two.



[1] https://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html