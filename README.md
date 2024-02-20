### The repository for practicing double hashing techniuqe. 

Double hashing is a computer programming technique used in conjunction with open addressing in hash tables to resolve hash collisions, by using a secondary hash of the key as an offset when a collision occurs.
#
The double hashing technique uses one hash value as an index into the table and then repeatedly steps forward an interval until the desired value is located, an empty location is reached, or the entire table has been searched; but this interval is set by a second, independent hash function. Unlike the alternative collision-resolution methods of linear probing and quadratic probing, the interval depends on the data, so that values mapping to the same location have different bucket sequences.

