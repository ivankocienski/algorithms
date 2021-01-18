# Complexity

Algorithms have cost both in run-time and memory usage. Understanding that cost can inform engineers about how the computer is going to perform under a given condition. This performance must then be monitored to determine if the system is achieving the intended goals. When/if the system stops achieving those goals the process needs to be re-run: see what is taking up the time and determine if a different choice can be made and a more suitable algorithm used.

Complexity analysis (at least awareness of it) is how this methodology is executed. Engineering is always a trade off of a number of factors. If a solution is developed quickly using a naive approach because of time/cost then 

## Big O

Every algorithm executed has a sequence of steps the CPU must walk through. Some algorithms are solved in one step; like looking up a value in a table. This has a complexity of O(1). More complicated algorithms will take an amount of time that is proportional to the input size. In analysis the size of the input is typically designated by the character 'N'. So an algorithm that takes as many steps as its input data size is O(N). For example; counting the number of occurrences of a value in an array.

## Big Omega &omega;

## Big Theta &theta;
