# Day 7

## Part 1
Pretty straight forward of iterating over all posibilities using binary integer representation for choosing the operant. Runtime is in $O(2^n)$.

## Part 2
Essentially the same problem but with three possibilities so $3^n$ instead of $2^n$ possibilities. Since computers work with bits there is no native way of have a base three representation so I just took the same approach as in part one but with two bits as "mask". This gives a runtime complexity of $O(4^n)$ or $O(2^{n+1})$.